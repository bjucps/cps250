#!/usr/bin/env python3
"""GUI Example 0: A single button."""

# Import Tkinter & TTk
from tkinter import *
from tkinter.ttk import *

def main():
    # Create root/top-level window object
    root = Tk()

    # Create a button as a child of that window
    button = Button(root,
        text="Hit me to quit!",
        command=root.quit)

    # "Pack" the button into the visible space provided by the window
    button.pack()

    # Handle user input/events until the window is closed
    root.mainloop()

if __name__ == "__main__":
    main()

