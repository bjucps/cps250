#!/usr/bin/env python3
import random
import re
import sys

NOUNS = """\
prince princess pea mattress bed fireplace kitchen dining
sitting quilt axe anvil alibi banana gorilla umbrella
penguin frog gingersnap pizza candybar hamburger
""".split()

VERBS = """\
run jump yell scream whisper crawl scoot roll skip
tear cut mend rip slide whine say deny lift drop
dunk evade remind obsess demure rebel recline
""".split()

ADJS = """\
bright dim sharp dull white black red blue yellow green
tall short clever stupid fat thin wise foolish early late
good bad indifferent irresistable repugnant revolting
delectable indigestible woody chalky dusty wet dry frumpy
""".split()

ADVS = """\
quickly slowly madly badly terribly awfully dreadfully
wonderfully bigly
""".split()


WORD_MAP = {
    "noun": NOUNS,
    "verb": VERBS,
    "adj": ADJS,
    "adv": ADVS,
}


def madlib_word(match) -> str:
    category = match.group(1)
    try:
        return random.choice(WORD_MAP[category])
    except KeyError:
        return f"<unk:{category}>"



if __name__ == "__main__":
    raw_story = sys.stdin.read()

    cooked_story = re.sub("_([a-z]+)_", madlib_word, raw_story)

    print(cooked_story)
