#!/usr/bin/env python3

import subprocess

print("Launching ping utility")

# Launch external process
proc = subprocess.Popen(["ping.exe", "bju.edu", "-n", "5"], stdout=subprocess.PIPE, stderr=subprocess.DEVNULL, text=True)

# Now, read each line produced by process as it arrives 
for line in proc.stdout:
    print(f"Received from subprocess: {line.strip()}")

proc.communicate() # Wait for process to exit 
print(f"Process finished with exit code {proc.returncode}")

