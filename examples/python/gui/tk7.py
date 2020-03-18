#!/usr/bin/env python3
"""GUI Example 7: Timers and Threads

Also demonstrates the use of Tk menubars and drop-down menus.
"""
import platform
import queue
import threading
import time

from tkinter import *
from tkinter.ttk import *
from tkinter import filedialog, messagebox


class LoaderThread(threading.Thread):
    """Example background worker thread that reads from a file VERY SLOWLY."""
    def __init__(self, q: queue.Queue, filename: str):
        super().__init__()
        self.daemon = True   # "Daemonize" the thread so we won't hang on shutdown

        self._q = q
        self._f = open(filename)

    def run(self):
        # Read lines from the file and enqueue them
        # (Sleep for .5 second between lines--simulating
        # the world's slowest filesystem).
        for i, line in enumerate(self._f):
            self._q.put("{0:04}: {1}".format(i+1, line))
            time.sleep(0.5)

        # Notify the GUI that we are DONE
        self._q.put(None)


class FileLoader(Tk):
    def __init__(self):
        super().__init__()
        if platform.system() == "Linux":
            # Srsly, guys...
            Style(self).theme_use("clam")

        # The 80's called: they want their ugly tear-off menus back...
        self.option_add("*tearOff", FALSE)

        # No background thread going yet
        self._q = None

        self._text = Text(self)
        scrolly = Scrollbar(self, orient=VERTICAL, command=self._text.yview)
        self._text['yscrollcommand'] = scrolly.set
        scrolly.pack(side=RIGHT, fill=Y)
        self._text.pack(expand=YES, fill=BOTH)

        top_menu = Menu(self)
        self['menu'] = top_menu
        self._file_menu = Menu(top_menu)
        self._file_menu.add_command(label="Open", command=self._open, underline=0)  # Shortcut: O
        self._file_menu.add_separator()
        self._file_menu.add_command(label="Exit", command=self.quit, underline=1)   # Shortcut: x 
        top_menu.add_cascade(label="File", menu=self._file_menu, underline=0)

    def _open(self):
        """Open-file menu option handler."""
        fname = filedialog.askopenfilename()
        if fname:
            # Disable the "open" menu option (item 0 in that menu)
            self._file_menu.entryconfigure(0, state=DISABLED)

            # Clear out the text area
            self._text.delete("1.0", END)

            # Create a thread-safe queue and give the new thread a reference to it
            self._q = queue.Queue()
            thread = LoaderThread(self._q, fname)
            
            # Spin off the thread
            thread.start()

            # And register our timer to monitor the queue for events
            self.after(100, self._check)

    def _check(self):
        # As long as we (think) we hav lines...
        while not self._q.empty():
            try:
                line = self._q.get(False)   # Make SURE we don't block
            except queue.Empty:
                # Weird, but carry on...we're done with this loop...
                break
            else:
                if line is None:
                    # This is our thread's signal for EOF: the thread is now/soon dead...
                    self._q = None

                    # Reenable the open menu
                    self._file_menu.entryconfigure(0, state=NORMAL)

                    # And QUIT without reregistering the timer
                    return
                else:
                    # Next line...
                    self._text.insert(END, line)
        
        # Unless we returned prematurely (i.e., end of file), re-register timer
        self.after(100, self._check)


if __name__ == "__main__":
    FileLoader().mainloop()

