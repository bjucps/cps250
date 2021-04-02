#!/usr/bin/env python3
 
# A simple web server in Python
 
import socket
import re
import signal
import sys

def ctrlc_handler(signal, frame):
    print('You pressed Ctrl+C!')
    sys.exit(0)
        
def return_error_page(sockfile, errornum, errormsg):
      sockfile.write("""HTTP/1.0 {0} {1}
Content-Type: text/html

<html>
<head>
<title>{1}</title>
</head>
<body>
{1}
</body>
</html>
  """.format(errornum, errormsg))

signal.signal(signal.SIGINT, ctrlc_handler)
 
# Standard socket stuff:
if len(sys.argv) == 2:
  port = int(sys.argv[1])
else:
  port = 8080
  
sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
sock.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
sock.bind(('', port))  # listen on all network interfaces
sock.listen(1)         # at most 1 client waiting to be accepted

workersock = 0

try: 
  # Loop forever, listening for requests:
  while True:
    print("Web server active on port " + str(port) + ", waiting for connection...")
    workersock, caddr = sock.accept()
    print("Connection from: " + str(caddr))
      
    with workersock.makefile('rw', 1024) as sockfile:
      # Process request        
            
    workersock.close()
finally:
  print("Shutting down...")
  if workersock:
    workersock.close()  
  sock.close()
  
  