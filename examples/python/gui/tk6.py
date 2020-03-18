#!/usr/bin/env python3
"""GUI Example 6: Demonstrate Tk timer events.

Also demonstrates use of the "Scale" and "Checkbutton" widgets.
"""
from tkinter import *
from tkinter.ttk import *

class TimerDemo(Tk):
    def __init__(self):
        super().__init__()
        self.title("Timer Demo")
        Style(self).theme_use("clam")

        # Create widgets
        panel = Frame(self)
        ckbox = Checkbutton(panel, text="Follow")
        scale = Scale(panel, orient=HORIZONTAL, from_=10, to=2000)
        self._text = Text(self)
        scrolly = Scrollbar(self, orient=VERTICAL, command=self._text.yview)
        self._text['yscrollcommand'] = scrolly.set

        # Pack them in
        ckbox.pack(side=RIGHT)
        scale.pack(expand=YES, fill=X)
        panel.pack(side=BOTTOM, fill=X)
        scrolly.pack(side=RIGHT, fill=Y)
        self._text.pack(expand=YES, fill=BOTH)

        # Track the current timer interval with a Tk "variable"
        self._interval = IntVar(value=1000)
        scale["variable"] = self._interval
        scale["command"] = self._interval_changed

        # Should we scroll the Text widget to the bottom after each addition?
        self._follow = BooleanVar(value=True)
        ckbox["variable"] = self._follow

        # Configure a timeout event (capture the ID for cancellation)
        self._afterid = self.after(self._interval.get(), self._timeout)

    def _interval_changed(self, interval):
        # Cancel the "pending" timeout and cause it to happen NOW
        self.after_cancel(self._afterid)
        self._timeout("Interval changed")

    def _timeout(self, msg="Timer just fired"):
        # Append a message to the Text widget
        interval = self._interval.get()
        self._text.insert(END, "{0}: interval is now {1}ms...\n".format(msg, interval))

        # If so configured, "follow" the end of the Text view
        if self._follow.get():
            self._text.see(END)

        # Set up the next event
        self._afterid = self.after(interval, self._timeout)


if __name__ == "__main__":
    TimerDemo().mainloop()

