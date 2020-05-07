#!/usr/bin/python

from threading import Thread, Lock
from time import sleep

sum = 0

class MyThread(Thread):

  lock = Lock()

  def __init__(self, name):
    super().__init__()
    self.name = name
    
  def run(self):
    global sum
    for i in range(10):
      print("I am thread" , self.name + ":", i)
      with MyThread.lock:  
        sum += 1
      sleep(.1)
      
fred = MyThread('Fred')
jane = MyThread('Jane')

fred.start()
jane.start()

