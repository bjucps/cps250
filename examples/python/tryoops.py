#!/usr/bin/python

import sys

try:
   count = "123"
   x = int(count)
   name = "Fred"
   print "Hello"
   x = len(name)
   print "Leaving"
   sys.exit(0)
except:
   # Don't do this at home
   pass

print "Bye"
