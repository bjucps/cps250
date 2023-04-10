#!/usr/bin/env python3
 
# A simple web server in Python
 
import socket
import re
import signal
import sys

def ctrlc_handler(signal, frame):
    print('You pressed Ctrl+C!')
    sys.exit(0)
        
# Capture Ctrl-C
signal.signal(signal.SIGINT, ctrlc_handler)
 
if len(sys.argv) == 2:
  port = int(sys.argv[1])
else:
  port = 8080

# Create socket
sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

# Allow this socket to be reused right away after this server shuts down
sock.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1) 

# Bind to specified port and configure to listen
sock.bind(('', port))
sock.listen(1)  # allow only 1 client to be queued waiting to connect at a time

# Loop forever, listening for requests:
while True:
  print("Echo server active on port " + str(port) + ", waiting for connection...")
  workersock, caddr = sock.accept()
  print("Connection from: " + str(caddr))

  try:      
    with workersock.makefile('r', 1024) as sockfile:
      workersock.sendall("Welcome to the echo server!\n".encode())
      
      req = sockfile.readline()
      while req != '' and req.strip() != 'quit':
          print("Received: ", req.strip())
          workersock.sendall((req.strip() + "\n").encode())
          req = sockfile.readline()
  except IOError as e:
      print("I/O Error:", e)
  
  workersock.close()

