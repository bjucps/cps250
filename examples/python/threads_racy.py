#!/usr/bin/python
import os
import random
from threading import Thread, Lock
from time import sleep

g_sum = 0

RACY = os.environ.get("RACY", "0") == "1"   # run with "RACY=1" to set this environment variable

class MyThread(Thread):

    lock = Lock() # class variable (shared among all instances)

    def __init__(self, name):
        super().__init__()
        self.name = name
        if not RACY:
            self._sync = MyThread.lock # shared lock -- causes mutual exclusion
        else:
            self._sync = Lock()  # my own private lock that nobody else shares or synchronizes on BWAHAHAHA

    def run(self):
        global g_sum
        for i in range(100):
            print("I am thread" , self.name + ":", i)
            with self._sync:                # take and hold our synchronizing lock, releasing on any exit from the `with ...:` block (on success or exception raised)
                tmp = g_sum                 # do a non-Python-bytecode-atomic update to `g_sum`
                if random.random() > 0.5:   # 50% chance of doing a micro-sleep here to simulate non-deterministic thread switching (simple Python code with the GIL is pretty deterministic...)
                    sleep(0.1)
                g_sum = tmp + 1
          
fred = MyThread('Fred')
jane = MyThread('Jane')

print("The sum is initially:", g_sum)

fred.start()
jane.start()

print("And they're off!")

fred.join()
jane.join()

print("And the sum is finally:", g_sum)

