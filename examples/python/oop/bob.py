#!/usr/bin/python

class Bob:

    numbobs = 0

    def __init__(self, lname, height):
        self.lname = lname
        self.height = height
        Bob.numbobs = Bob.numbobs + 1
        
    def printme(self):
        print "I am Bob %s and I am %d feet tall." % \
           (self.lname, self.height)
        
mr = Bob('Carl', 5)

print mr.lname
print mr.height

mr.lname = 'Schaub'
print mr.lname

print Bob.numbobs
Bob.numbobs = Bob.numbobs + 1


