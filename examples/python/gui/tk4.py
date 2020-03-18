#!/usr/bin/env python3
"""GUI Example 4: Event binding."""
from tkinter import *
from tkinter.ttk import *

class EventDemo(Frame):
    def __init__(self, parent):
        super().__init__(parent)

        # Create interlinked Text widget and vertical-scrollbar
        self._text = Text(self)
        scrolly = Scrollbar(self, orient=VERTICAL, command=self._text.yview)
        self._text["yscrollcommand"] = scrolly.set

        # Configure colored text tags
        self._text.tag_configure("red", foreground="red")
        self._text.tag_configure("green", foreground="green")
        self._text.tag_configure("blue", foreground="blue")

        # Create input panel
        panel = Frame(self)
        self._input = Entry(panel)
        self._input.insert(0, "type some stuff...")
        self._red_button = Button(panel, text="Red")
        self._green_button = Button(panel, text="Green")
        self._blue_button = Button(panel, text="Blue")

        # "Tag" the button widget objects with "extra" data we'll use later
        self._red_button._tag = "red"
        self._green_button._tag = "green"
        self._blue_button._tag = "blue"

        # Wire up buttons
        self._red_button.bind("<1>", self._button_handler)
        self._green_button.bind("<1>", self._button_handler)
        self._blue_button.bind("<1>", self._button_handler)

        # Wire up random other events on the Text widget itself
        self._text.bind("<Enter>", lambda _: self._text.insert(END, "Enter the cursor!\n"))
        self._text.bind("<Leave>", lambda _: self._text.insert(END, "DON'T GO!!!11! <sob...>\n"))
        self._text.bind("<Double-3>", lambda _: self._text.insert(END, "What's with the double-right-clicking?!\n"))
        
        # Bind this keystroke application-wide (no matter who has focus)
        self.bind_all("<Alt-a>", lambda _: self._text.insert(END, "You just pressed Alt-A but I WILL NOT RESPOND!!  Oh, wait...\n"))


        # Pack it all in
        self._blue_button.pack(side=RIGHT)
        self._green_button.pack(side=RIGHT)
        self._red_button.pack(side=RIGHT)
        self._input.pack(side=LEFT)
        panel.pack(side=BOTTOM, fill=X)
        self._text.pack(expand=YES, fill=BOTH)

    def _button_handler(self, event):
        """Handle red/green/blue button presses."""
        # Insert text from the Entry box into the Text box (at the END)
        # (Tag it according to the "extra" data we attached to the buttons)
        self._text.insert(END, self._input.get() + '\n', (event.widget._tag,))



def main():
    root = Tk()
    
    demo = EventDemo(root)
    demo.pack(expand=YES, fill=BOTH)

    root.mainloop()

if __name__ == "__main__":
    main()
