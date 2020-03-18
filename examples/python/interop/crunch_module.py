#!/usr/bin/env python3
import os

# Import our custom module
import crunchlib

if __name__ == "__main__":
    import sys

    # What file should we hash?
    try:
        filename = sys.argv[1]
    except IndexError:
        print("usage: crunch.py FILENAME")
        exit()

    with open(filename, 'rb') as fd:
        blob = fd.read()
    
    # Call our module
    hash_val = crunchlib.crunch(blob)

    print("{0}: 0x{1:08x}".format(filename, hash_val))

