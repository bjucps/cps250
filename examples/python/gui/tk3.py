#!/usr/bin/env python3
"""GUI Example 3: Fun with the "grid" layout manager.

Also demonstrates Tk Fonts and "Variables" for data binding.
"""

from tkinter import *
from tkinter.ttk import *

# We want some bold font text...
BOLD_FONT = ("Helvetica", 12, "bold")

class LoginWindow(Frame):
    """Simple "login" window that prompts for username/password."""
    def __init__(self, parent):
        super().__init__(parent)

        # We'll use Tcl/Tk "Variables" to monitor
        # the values typed into our entry boxes
        self._user_var = StringVar()
        self._pass_var = StringVar()

        Label(self, text="Username:", font=BOLD_FONT).grid(row=0, column=0)
        Label(self, text="Password:", font=BOLD_FONT).grid(row=1, column=0)
        Entry(self, textvariable=self._user_var).grid(row=0, column=1)
        Entry(self, textvariable=self._pass_var, show="*").grid(row=1, column=1)
        Button(self, text="Login", command=self._login).grid(row=2, column=1)

    def _login(self):
        print("Logging in as user '{0}' (password '{1}')".format(
            self._user_var.get(), self._pass_var.get()))
        

def main():
    root = Tk()
    root.title("Login")

    # Create the login widgets
    login = LoginWindow(root)

    # Use the pack manager to display it in the root window
    login.pack(padx=5, pady=5)

    # Make the root window a fixed size
    root.resizable(False, False)

    root.mainloop()

if __name__ == "__main__":
    main()

