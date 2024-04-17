#!/usr/bin/env python3
import math
import random

from expiringdict import ExpiringDict
from flask import Flask, send_from_directory, request, session, redirect, url_for
import os.path
path = os.path.abspath(__file__)
dir_path = os.path.dirname(path)

VEGETATION = [
    ("bush.gif", 103, 89),
    ("flower.gif", 34, 34),
    ("grass.gif", 51, 53),
    #("hare.gif", 33, 34),
    #("rock.gif", 24, 38),
     ("tree.gif", 83, 87),
]
DUKE = ("duke.gif", 24, 38)
DUKECUE = ("dukecue.gif", 56, 56)
DECOYCUE = ("decoycue.gif", 56, 56)
EXPLOSION = ("explosion.gif", 71, 100)
TOMBSTONE = ("tombstone.gif", 59, 83)
FIRE = ("fire.gif", 30, 60)


WIDTH = 1000
HEIGHT = 500

SND_CHIME = "35631__reinsamba__crystal_glass.mp3"
SND_BOOM = "explosion.wav"
SND_GIGGLE = "235166__reitanna__giggle3.wav"


class Game:
    def __init__(self, width: int, height: int, num_dukes: int):
        self.width = width
        self.height = height
        self.turns = 0
        self.damage = 0
        self.num_dukes = num_dukes
        self.dukes_left = num_dukes
        self.cheating = False
        self.sound = SND_CHIME

        veg = []
        clickables = []
        for i in range(num_dukes):
            clickables.append(self._random_entity(Duke))
            clickables.append(self._random_entity(Decoy))
            for i in range(5):
                veg.append(self._random_entity(Entity))
        self._entities = veg + clickables

    def _random_entity(self, entity_class: type):
        x = random.randint(round(0.1 * self.width), round(0.9 * self.width))
        y = random.randint(round(0.1 * self.height), round(0.9 * self.height))
        avatar = random.choice(VEGETATION)
        return entity_class(self, x, y, avatar)

    def toggle_cheating(self):
        self.cheating = not self.cheating

    def game_is_over(self) -> bool:
        return self.dukes_left == 0

    def add_damage(self, amount: int):
        self.damage += amount

    def find_duke(self, clicked=True):
        self.dukes_left -= 1
        if clicked:
            self.turns -= 1 # get a turn back for finding a Duke
            self.sound = SND_GIGGLE

    def bad_click(self):
        self.turns += 5 # penalize for clicking a non-hidden-Duke

    def boom(self, x: int, y: int):
        self.sound = SND_BOOM
        for e in self._entities:
            dist = math.hypot(e.x - x, e.y - y)
            if dist <= 150:
                e.kill()

    def click(self, ident: str):
        if self.game_is_over():
            return

        ident = int(ident)
        for e in self._entities:
            if id(e) == ident:
                e.click()

    def update(self):
        if self.game_is_over():
            return

        self.turns += 1
        for e in self._entities:
            e.update()

    def __str__(self):
        entities = "\n".join(str(e) for e in self._entities)
        if self.cheating:
            extras = []
            for e in self._entities:
                cue_avatar = None
                if isinstance(e, Decoy):
                    cue_avatar = DECOYCUE
                elif isinstance(e, Duke):
                    cue_avatar = DUKECUE

                if cue_avatar:
                    cue = Entity(self, e.x, e.y + e.height, cue_avatar)
                    cue.width = e.width
                    extras.append(cue)
                entities += '\n' + '\n'.join(str(e) for e in extras)

        game_over_msg = ""
        if self.game_is_over():
            if self.damage < 1000:
                damage_rating = "LOW"
            elif self.damage < 2000:
                damage_rating = "MODERATE"
            elif self.damage < 3000:
                damage_rating = "SEVERE"
            else:
                damage_rating = "EXTREME"

            game_over_msg = f"""\
<rect x="0" y="{.15*self.height}" width="{self.width}" height="{.5*self.height}" fill="#cccccccc" />
<text x="{.28*self.width}" y="{.3*self.height}" font-family="sans-serif" font-size="72" stroke="white" fill="yellow">
    GAME OVER
</text>
<text x="{.31*self.width}" y="{.4*self.height}" font-family="sans-serif" font-size="24" stroke="white" fill="blue">
    You took {self.turns} turns to find {self.num_dukes} Dukes.
</text>
<text x="{.3*self.width}" y="{.5*self.height}" font-family="sans-serif" font-size="24" stroke="white" fill="red">
    Your environmental impact score: {damage_rating}
</text>
"""
        sound = self.sound
        self.sound = SND_CHIME

        return f"""\
<!DOCTYPE html>
<html xmlns='http://www.w3.org/1999/xhtml'>

<head>
    <title>Duke Hunt</title>
    <style>
        a {{
            color: yellow;
        }}

        body {{
            background-color: black;
            margin: 0;
            color: yellow;
        }}
    </style>

</head>

<body>
    <center>
        <img src='img/dukehuntsmall.png' /> <br/>
        <table width='100%'>
            <tr>
                <td valign='bottom' align='right'><a href='?action=view'>Update World</a> </td>
                <td align='center' style='color:yellow'>
                    Turns: {self.turns} | Undiscovered Dukes: {self.dukes_left}
                </td>
                <td valign='bottom' align='left'><a href='{url_for("index")}'>New Game</a></td>
            </tr>
        </table>
        <svg xmlns='http://www.w3.org/2000/svg' xmlns:xlink='http://www.w3.org/1999/xlink' version='1.1' width='{self.width}px' height='{self.height}px'>
            <rect x='0' y='0' width='{self.width}' height='{self.height}' fill='lightgreen' />
            {entities}
            {game_over_msg}
        </svg>
        <br />
        <a href="play?action=cheat" style='color: #222222'>Cheat Mode</a>
        <br />
    </center>
    <audio src='sounds/{sound}' autoplay='true' />
</body>

</html>
"""


class Entity:
    def __init__(self, game: Game, x: int, y: int, avatar: tuple):
        self._game = game
        self.x = x
        self.y = y
        self._set_avatar(avatar)

    def _set_avatar(self, avatar: tuple):
        img, width, height = avatar
        self.img = img
        self.width = width
        self.height = height

    def update(self):
        pass

    def click(self):
        self._game.bad_click()

    def kill(self):
        self._set_avatar(FIRE)
        self._game.add_damage(100)

    def __str__(self):
        return f"""\
<a xlink:href="play?action=click&amp;id={id(self)}">
    <image x="{self.x}" y="{self.y}" xlink:href="img/{self.img}" width="{self.width}" height="{self.height}" />
</a>
"""


class Duke(Entity):
    def __init__(self, game: Game, x: int, y: int, avatar: tuple):
        super().__init__(game, x, y, avatar)
        self.angle = math.radians(random.randint(0, 360))
        self.speed = random.randint(5, 15)
        self.found = False

    def click(self):
        if not self.found:
            self._set_avatar(DUKE)
            self._game.find_duke()
            self.found = True

    def update(self):
        dx = math.cos(self.angle) * self.speed
        dy = -math.sin(self.angle) * self.speed
        self.x += dx
        self.y += dy

    def kill(self):
        if self.found:
            return
        self.found = True
        self.speed = 0
        self._set_avatar(TOMBSTONE)
        self._game.add_damage(500)
        self._game.find_duke(clicked=False)



class Decoy(Duke):
    def __init__(self, game: Game, x: int, y: int, avatar: tuple):
        super().__init__(game, x, y, avatar)
        self._sploded = False

    def click(self):
        self._game.bad_click()
        self.kill()

    def update(self):
        if self._sploded:
            return
        super().update()
        self.angle = math.fmod((self.angle + math.pi), math.pi * 2)

    def kill(self):
        if self._sploded:
            return
        self._sploded = True
        self._set_avatar(EXPLOSION)
        self._game.boom(self.x, self.y)


app = Flask(__name__)
app.secret_key = os.environ.get("SECRET_KEY", "not-really-that-secret-is-it")

@app.route('/<path:filename>')
def send_static(filename):
    if filename.endswith('.py'):
        return "You may not have that file."

    return send_from_directory(dir_path, filename)


@app.route('/')
def index():
    """Home page."""
    return TITLE_HTML

# We support up to 100 games concurrently; games will stay alive for 10 minutes, max
active_games = ExpiringDict(100, 10 * 60)


@app.route('/play')
def play():
    """Gameplay page request handler."""
    action = request.args["action"]
    if action == "Start Game":
        # TODO: catch errors
        num_dukes = int(request.args["numdukes"])
        new_game = Game(WIDTH, HEIGHT, num_dukes)
        active_games[str(id(new_game))] = new_game
        session["game_id"] = str(id(new_game))
        running_game = new_game
    elif "game_id" in session and session["game_id"] in active_games:
        running_game = active_games[session["game_id"]]
    else:
        return redirect(url_for('index'))

    if action == "view":
        running_game.update()
    elif action == "click":
        running_game.click(request.args["id"])
        #running_game.update()
    elif action == "cheat":
        running_game.toggle_cheating()

    return str(running_game)

TITLE_HTML = """\
<?xml version="1.0" encoding="UTF-8"?>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN"    "http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd">
<html>

<head>
    <title>Duke Hunt</title>
    <style type='text/css'>
        body {
            background: black;
            border: 100;
            color: white;
        }
    </style>
</head>

<body>
    <center>

        <img src='img/dukehunt.gif' />
        <br />
        <h3>How to Play</h3>
        <p>
            Click <b>Update World</b> to advance one turn. Vegetation does not move. Dukes (and decoys!) do move.
            Click on an on-screen entity to lose 5 turns <i>and</i> reveal it (if it is a duke), detonate it (if it is a
            decoy), or simply lose 5 turns (vegetation).
        </p>
        <hr />
        <h3>Credits:</h3>
        <ul>
            <li>2dogSound_tadaa1_3s_2013jan31_CC-BY-30-US.wav by rdholder shared under the Creative Commons Attribution license.</li>
            <li>freesound.org &mdash; other sound effects</li>
        </ul>
        <br />

        <form action='play'>
            Number of Dukes <img src='img/duke.gif' />: <input type='text' name='numdukes' value='3' />
            <input type='submit' name='action' value='Start Game' />
        </form>

    </center>
    <audio src='sounds/EASTERN_SITAR_BRIGHT_1.mp3' autoplay='true' />
</body>

</html>
"""

GAME_HTML = """\

"""

# Boilerplate bootstrapping logic for running as a standalone program
if __name__ == "__main__":
    app.run(host="0.0.0.0", port=3000, debug=True)
