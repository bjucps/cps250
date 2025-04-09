#!/usr/bin/python

from threading import Thread

from time import sleep

class MyThread(Thread):
    def __init__(self, name, sleepy=False):
        super().__init__()  # CRITICAL to invoke the Thread.__init__ constructor here or the thread WON'T WORK
        self.name = name
        self.sleepy = sleepy
    
    def run(self):  # body of code that will run in the newly created thread
        for i in range(10):
            print("I am thread" , self.name + ":", i)
            sleep(.1)

        if self.sleepy:
            sleep(3)
            print(self.name, ": oh, did I fall asleep?")

      
fred = MyThread('Fred', sleepy=True)
jane = MyThread('Jane')

fred.start()    # to get the thread created/running, call .start(), never .run()!
jane.start()

print("MAIN PROGRAM DONE")

jane.join()     # you must .join() any threads you .start() [or else make them "daemon" threads; see the docs...]
fred.join()



