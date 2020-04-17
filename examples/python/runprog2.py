#!/usr/bin/env python3

import subprocess

print("Launching ping utility")

# Launch external process
proc = subprocess.Popen(["ping", "localhost", "-c", "5"], stdout=subprocess.PIPE, stderr=subprocess.PIPE, universal_newlines=True)

# Now, read each line produced by process as it arrives 
for line in proc.stdout:
    print(f"Received from subprocess: {line.strip()}")

proc.communicate() # Wait for process to exit 
print(f"Process finished with exit code {proc.returncode}")

