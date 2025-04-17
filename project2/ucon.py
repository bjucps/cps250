#!/usr/bin/env python3
'''ucon.py: CpS 250 Project 2 for YOUR NAME HERE (yourloginhere)

from starting code provided by Dr. J, (c) 2025 Bob Jones University
'''
import ctypes
import os
import sys

# contents scraped from system header files (the output of the constants.c tool)
CLONE_NEWNS     = 0x00020000
CLONE_NEWPID    = 0x20000000

# ctypes libc wrangling with tips from https://github.com/PexMor/unshare/blob/master/01-syscall.py
libc = ctypes.CDLL(None)

# libc defines this internal helper to get the thread-specific "errno" variable via a returned pointer
get_errno_loc = libc.__errno_location
get_errno_loc.restype = ctypes.POINTER(ctypes.c_int)

# int unshare(int flags) /* syscall wrapper */
libc.unshare.argtypes = [ctypes.c_int]
libc.unshare.restype = ctypes.c_int


def get_errno() -> int:
    '''return current thread's C errno value
    '''
    return get_errno_loc()[0]


def raise_errno(msg: str = None):
    '''raise an OSError with the current `errno` value and `msg` (if given)
    
    uses `os.strerror(...)` to produce a default message if `msg` is None
    '''
    erno = get_errno()
    if msg is None:
        msg = os.strerror(erno)
    else:
        msg = f"{msg}: {os.strerror(erno)}"
    raise OSError(erno, msg)


def unshare(flags: int):
    '''call `unshare` syscall with `flags` and raise OSError if return value indicates failure
    '''
    if libc.unshare(flags) < 0:
        raise_errno("unshare")


# TODO: probably need more syscalls defined via ctypes


def main(argv):
    # TODO: actually write the program
    pass

if __name__ == "__main__":
    main(sys.argv)
