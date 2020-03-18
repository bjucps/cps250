#!/usr/bin/env python3
"""TTk Theme Selector.

Demonstrates TTk's theming abilities and shows a few widgets...
"""

# Import Tkinter & TTk
from tkinter import *
from tkinter.ttk import *

def main():
    root = Tk()

    # Get the style engine for our root window
    style = Style(root)

    # Create a combo-box/drop-down-box containing a list of all available themes
    dd_themes = Combobox(root, state="readonly", values=style.theme_names())

    # Bind a handler to its "selection changed" event; in it, switch to the selected theme
    dd_themes.bind("<<ComboboxSelected>>", lambda _: style.theme_use(dd_themes.get()))

    # Pack the drop-down into the window along with some demo widgets
    dd_themes.pack(padx=5, pady=5)
    Button(root, text="A Button").pack(padx=5, pady=5)
    Entry(root, text="An Entry").pack(padx=5, pady=5)
    Checkbutton(root, text="A Checkbutton").pack(padx=5, pady=5)
    Radiobutton(root, text="A Radiobutton").pack(padx=5, pady=5)

    root.mainloop()

if __name__ == "__main__":
    main()

