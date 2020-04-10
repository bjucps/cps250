# README

This folder contains utilities that compute a hash on a file of data.

* crunch.py - native Python 
* crunch.c - native C
* crunch_ctypes.py - Python interop with C
* crunchlib.c - A C library that can be directly imported into Python

## Compile

Execute the following:

    bash build_raw.sh - compiles crunch.c
    bash build_mod.sh - builds C library used by Python interop example

## Tests

Try executing the following tests:

    dd if=/dev/urandom of=bigfile.bin bs=1M count=500   # Create a 500 MB file of random data
    time ./crunch bigfile.bin    # time the C implementation
    time python3 crunch.py bigfile.bin   # time the Python implementation
    time python3 crunch_ctypes.py bigfile.bin     # time the Python implementation that uses C interop

