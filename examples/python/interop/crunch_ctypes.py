#!/usr/bin/env python3
import os
import ctypes

SO_FILENAME = "./crunch.so"

# Load containing library
_so_handle = ctypes.cdll.LoadLibrary(SO_FILENAME)


def my_hash_function(buff):
    """Python stub that calls a C function."""
    # Invoke function (automatically guesses the parameter types)
    # Then AND it with 0xFFFFFFFF to make it unsigned
    return _so_handle.crunch(buff, len(buff)) & 0xFFFFFFFF


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

