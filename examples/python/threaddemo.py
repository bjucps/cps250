#!/usr/bin/python

from threading import Thread

from time import sleep

class MyThread(Thread):
    def __init__(self, name, sleepy=False):
        super().__init__(daemon=True)
        self.name = name
        self.sleepy = sleepy
    
    def run(self):
        for i in range(10):
            print("I am thread" , self.name + ":", i)
            sleep(.1)

        if self.sleepy:
            sleep(10)
            print(self.name, ": oh, did I fall asleep?")

      
fred = MyThread('Fred', sleepy=True)
jane = MyThread('Jane')

fred.start()
jane.start()

print("MAIN PROGRAM DONE")



