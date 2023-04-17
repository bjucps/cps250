#!/usr/bin/env python3

import subprocess

print("Launching `ls -l`")

# If using python 3.7+
result = subprocess.run(["ls", "-l"], capture_output=True, text=True)

# If using python 3.6, must use older form:
#result = subprocess.run(["ping", "localhost", "-c", "5"], stdout=subprocess.PIPE, stderr=subprocess.PIPE, universal_newlines=True)

print(f"Process sent to stdout: {result.stdout}")
print(f"Process sent to stderr: {result.stderr}")
print(f"Finished with exit code {result.returncode}")
