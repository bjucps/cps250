#!/usr/bin/env python3
import socket
import sys

try:
    ip = sys.argv[1]
    port = int(sys.argv[2])
except (IndexError, ValueError):
    print(f"usage: {sys.argv[0]} IP PORT [TIME_FMT]", file=sys.stderr)
    sys.exit(1)

if len(sys.argv) > 3:
    time_fmt = sys.argv[3] + "\n"
else:
    time_fmt = "%a, %d %b %Y %T %z\n"

sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM, 0)
sock.connect((ip, port))

sock.sendall(time_fmt.encode("ascii"))

rdr = sock.makefile('r', buffering=1, encoding='ascii')
answer = rdr.readline()
print(answer)
