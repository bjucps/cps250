#!/usr/bin/python

from threading import Thread, Lock
from time import sleep



class MyThread(Thread):

  lock = Lock()

  def __init__(self, name):
    super().__init__()
    self.name = name
    
  def run(self):
    for i in range(10):
      #MyThread.lock.acquire()
      with MyThread.lock:  
        print("I am thread" , self.name + ":", i)
        sleep(.1)
      #MyThread.lock.release()
      
fred = MyThread('Fred')
jane = MyThread('Jane')

fred.start()
jane.start()

