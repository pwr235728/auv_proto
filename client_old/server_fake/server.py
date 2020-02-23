import socket
import time
import datetime
from threading import Thread
from array import array
import struct

class AuvServer:
    def __init__(self):
        self.UDP_IP = ' '
        self.UDP_PORT = 5005

        self.sock = socket.socket(socket.AF_INET,
                                  socket.SOCK_DGRAM)
        self.sock.bind((self.UDP_IP, self.UDP_PORT))
        self.sock.settimeout(0)

    def send(self, data, destination):
        self.sock.sendto(data, destination)

    def recv(self):
        return self.sock.recvfrom(1024)

# main:
server = AuvServer()

while True:
    try:
        data, addr = server.recv()
        print("server: ip", socket.gethostbyname(socket.gethostname()), end = " | ")
        print(datetime.datetime.now(), end =" | ")
        print(addr, end =" | ")
        print(data)
    except:
        time.sleep(0.1)



 