#!/usr/bin/env python3
"""GUI Example 5: Modal dialog windows.

Refines Example 3.
"""
from tkinter import *
from tkinter.ttk import *

# We want some bold font text...
BOLD_FONT = ("Helvetica", 10, "bold")

class LoginWindow(Frame):
    """Simple "login" window that prompts for username/password."""
    def __init__(self, parent, user_var, pass_var, result_var):
        super().__init__(parent)
        self._parent = parent
        self._result_var = result_var

        Label(self, text="Username:", font=BOLD_FONT).grid(row=0, column=0)
        Label(self, text="Password:", font=BOLD_FONT).grid(row=1, column=0)
        Entry(self, textvariable=user_var).grid(row=0, column=1)
        Entry(self, textvariable=pass_var, show="*").grid(row=1, column=1)
        Button(self, text="Login", command=self._login).grid(row=2, column=1)

    def _login(self):
        self._result_var.set(True)
        self._parent.destroy()

def get_login():
    """Show a modal dialog and use it to get login info."""
    user_var = StringVar()
    pass_var = StringVar()
    ok_var = BooleanVar()

    window = Toplevel()
    login = LoginWindow(window, user_var, pass_var, ok_var)
    login.pack()
    window.resizable(False, False)

    window.grab_set()
    window.focus_set()
    window.wait_window()

    if ok_var.get():
        return user_var.get(), pass_var.get()
    else:
        return None, None

def main():
    root = Tk()

    text = Text(root)
    def handle_login():
        user, passwd = get_login()
        if user is not None and passwd is not None:
            text.insert(END, "You are {0}.  You have a password, but I will not reveal it here...\n".format(user))
    button = Button(root, text="Enter Credentials", command=handle_login)

    button.pack(side=BOTTOM, fill=X)
    text.pack(expand=YES, fill=BOTH)

    root.mainloop()

if __name__ == "__main__":
    main()

