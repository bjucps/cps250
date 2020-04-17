#!/usr/bin/env python3

import socket
import sys
import time

sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

if len(sys.argv) == 2:
    # Receiver
    port = int(sys.argv[1])
    sock.bind(('', port))
    print(f"Listening for pings on port {port}...")
    while True:
        data, address = sock.recvfrom(1024)
        data = data.decode('ascii')  # Convert from bytes to str
        srcip, port = address
        print(f"Received message: {data} from: {srcip} port {port}")

elif len(sys.argv) == 3:
    # Sender
    port = int(sys.argv[1])
    destip = sys.argv[2]

    msg = 0
    while True:
        print(f"Sending ping message to {destip} port {port}...")
        sock.sendto(f"Ping #{msg}".encode('ascii'), (destip, port))
        msg += 1
        time.sleep(1)
else:
    print("Usage: ping.py <port> [ <destip> ]")
    exit(1)



