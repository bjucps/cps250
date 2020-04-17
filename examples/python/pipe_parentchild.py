#!/usr/bin/env python3

import os

readfd, writefd = os.pipe()  # Create pipe

kidpid = os.fork()

if kidpid > 0:
    # Parent executes this
    os.close(readfd)
    os.write(writefd, b"Hello, dear child!")
    print("[Parent] Wrote message to child")

elif kidpid == 0:
    # Child executes this
    os.close(writefd)
    bytearr = os.read(readfd, 1024) # read up to 1024 bytes
    print("[Child] Received message: " + bytearr.decode('ascii'))
    
else:
    print("Uh oh: fork() failed!")

