#!/usr/bin/env python3
import os

def my_hash_function(buff):
    """Dumb little "hashing" function for a buffer of bytes."""
    val = 0xDEADBEEF
    for byte in buff:
        # Add byte to running "hash-sum"
        val += byte

        # Do magic bit-mashing/mixing
        val = ((val << 5) | (val >> 27)) & 0xffffffff
    return val

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
    

    hash_val = my_hash_function(blob)
    print("{0}: 0x{1:08x}".format(filename, hash_val))

