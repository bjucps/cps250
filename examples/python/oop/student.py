#!/usr/bin/python

class Student:
  
  nextid = 1

  def __init__(self, newname):
    self.name = newname
    self.id = Student.nextid
    Student.nextid = Student.nextid + 1
    
    
  def display(self):
    print("I am %s and my id is %d" % (self.name, self.id))

  @staticmethod    
  def showNextId():
    print("The next ID is", Student.nextid)
    
#----------- Main program -------------------
if __name__ == "__main__":
    joe = Student("Joe")
    sally = Student("Sally")

    joe.display()
    sally.display()

    Student.showNextId()

