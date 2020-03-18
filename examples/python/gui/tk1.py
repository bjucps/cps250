#!/usr/bin/env python3
"""GUI Example 1: Text boxes, buttons, and message boxes"""

# Import Tkinter & TTk
from tkinter import *
from tkinter.ttk import *

# Also import the standard message box functions
from tkinter import messagebox

def main():
    # Create root/top-level window object
    root = Tk()

    # Create widgets as children of that object
    name_lbl = Label(root, text="Name:")
    name_txt = Entry(root)
    ok_btn = Button(root, text="OK")

    # Event handler function 
    def handler():
        # Show a nice message containing user input
        msg = "Hello, {0}!".format(name_txt.get())
        messagebox.showinfo(title="Greetings!", message=msg)

        # Re-focus the input box
        name_txt.focus_set()

    # Install handler (can do this after button creation)
    ok_btn["command"] = handler

    # "Pack" the widgets to make them visible
    name_lbl.pack(side=LEFT)
    name_txt.pack(side=LEFT)
    ok_btn.pack(side=RIGHT)

    # Start out with the keyboard focus on the Entry widget
    name_txt.focus()

    # Enter the event loop
    root.mainloop()

if __name__ == "__main__":
    main()

