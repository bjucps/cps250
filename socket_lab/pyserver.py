#!/usr/bin/env python3
import socket
import sys
import time

def handle_client(conn):
    rdr = conn.makefile('r', buffering=1, encoding='ascii')
    fmt = rdr.readline()
    rdr.close()

    answer = time.strftime(fmt)
    conn.sendall(answer.encode('ascii'))
    conn.close() 


try:
    ip = sys.argv[1]
    port = int(sys.argv[2])
except (IndexError, ValueError):
    print(f"usage: {sys.argv[0]} IP PORT", file=sys.stderr)
    sys.exit(1)

sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM, 0)
sock.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
sock.bind((ip, port))
sock.listen(5)

while True:
    conn, addr = sock.accept()
    print(f"BEGIN: connection from {addr[0]}:{addr[1]}")
    handle_client(conn)
    print(f"END: connection from {addr[0]}:{addr[1]}")

