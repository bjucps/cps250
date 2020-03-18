#!/usr/bin/env python3
"""GUI Example 2: Fun with the "pack" layout manager.

Also demonstrates the use of listboxes and scrollbars.
"""
import random

from tkinter import *
from tkinter.ttk import *

FOOD_ACTIONS = [
    'boiled', 'stewed', 'baked', 'toasted', 'roasted',
    'salted', 'steamed', 'smoked', 'charred']

FOOD_NAMES = [
    'potato', 'pizza', 'hotdog', 'cabbage', 'tomato',
    'beans', 'cornbread', 'broccoli', 'spinach', 'bacon']

DRINK_ACTIONS = [
    'boiling', 'freezing', 'stirred', 'shaken', 'mulled',
    'iced', 'chilled']

DRINK_NAMES = [
    'water', 'coffee', 'tea', 'Kool-Aid', 'punch',
    'effervescent esophogeal lubricant', 'lemonade']


def random_food():
    return "{0} {1}".format(random.choice(FOOD_ACTIONS),
                            random.choice(FOOD_NAMES))

def random_drink():
    return "{0} {1}".format(random.choice(DRINK_ACTIONS),
                            random.choice(DRINK_NAMES))


class MyWindow(LabelFrame):
    """A fairly simple window (subclassing TTk's LabelFrame widget).

    Laid out like this:

        ---------
        |       |
        |Listbox|
        |       |
        ---------
        |A B   C|
        ---------

    Where "Listbox" is a listbox and A, B, and C
    are buttons.  Designed to resize smoothly.
    """
    def __init__(self, parent=None):
        super().__init__(parent, text="The Menu")
        
        # Create and pack the non-expanding bottom panel first 
        panel = Frame(self)
        self._btn_food = Button(panel, text="Add Food", command=self._food)
        self._btn_drink = Button(panel, text="Add Drink", command=self._drink)
        self._btn_quit = Button(panel, text="Quit", command=exit)
        
        # The buttons do not expand/fill, but they need padding 
        self._btn_quit.pack(side=RIGHT, padx=5, pady=5) 
        self._btn_food.pack(side=LEFT, padx=5, pady=5) 
        self._btn_drink.pack(side=LEFT, padx=5, pady=5) 

        # The panel goes at the bottom of our frame,
        # taking all the space available in the X direction
        # but NOT requesting more space as the window grows
        panel.pack(side=BOTTOM, fill=X) 
        
        # Create the list box and attach a scrollbar
        # (we cross-wire them so that updates to one affects the other)
        self._list = Listbox(self)
        scrolly = Scrollbar(self, orient=VERTICAL, command=self._list.yview)
        self._list['yscrollcommand'] = scrolly.set
        
        # Now pack in the scrollbar/list box to take all available space
        # (and ask for more as the window grows)
        scrolly.pack(side=RIGHT, fill=Y)
        self._list.pack(side=TOP, expand=YES, fill=BOTH)

    def _food(self):
        """Handler for the "Food" button."""
        self._list.insert(END, random_food())
    
    def _drink(self):
        """Handler for the "Drink" button."""
        self._list.insert(END, random_drink())

def main():
    root = Tk()
    win = MyWindow(root)
    
    # Pack our menu frame into the main window (with internal/external
    # padding to make it look nicer)
    win.pack(expand=YES, fill=BOTH, ipadx=5, ipady=5, padx=5, pady=5)
    
    root.mainloop()

if __name__ == "__main__":
    main()

