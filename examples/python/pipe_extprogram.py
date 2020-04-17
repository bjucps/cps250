#!/usr/bin/env python3

import os

readfd, writefd = os.pipe()  # Create pipe

kidpid = os.fork()

if kidpid > 0:
    # Parent executes this
    os.close(writefd)
    readfile = os.fdopen(readfd)
    for line in readfile:  # Iterate over lines of data produced by child
        print("[Parent] Received from child: " + line.strip())
    readfile.close()

elif kidpid == 0:
    # Child executes this
    os.close(readfd)
    os.dup2(writefd, 1)           # replace STDOUT (1) with writefd
    os.execvp("ls", ["ls", "-l"]) # Does not return
    
else:
    print("Uh oh: fork() failed!")

