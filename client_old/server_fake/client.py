import socket
import time
import datetime

class AuvClient:
    def __init__(self, destination):
        self.UDP_IP = '127.0.0.1'
        self.UDP_PORT = 0 # mean random port

        self.dest = destination

        self.sock = socket.socket(socket.AF_INET,
                                  socket.SOCK_DGRAM)
        self.sock.bind((self.UDP_IP, self.UDP_PORT))

    def send(self, data):
        self.sock.sendto(data, self.dest)

    def recv(self):
        return self.sock.recvfrom(1024)


# main:

number = 0
client = AuvClient(('127.0.0.1', 5005))
while True:
    number += 1
    print("Client", end=" | ")
    print(datetime.datetime.now(), end=" | ")
    print("destination: ", client.dest, end=" | ")
    data = "data: " + str(number)
    client.send(data.encode())
    print("data: '", data,"'")

    time.sleep(0.5)

 