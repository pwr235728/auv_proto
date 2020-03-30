import socket
import time

class RovSocket:
    def send(self, data):
        pass

    def recv(self):
        pass


class PrintSocket(RovSocket):
    def __init__(self):
        self.counter = 0

    def send(self, data):
        print(("PrintSocket.send(): ",data))

    def recv(self):
        time.sleep(3)
        self.counter += 1
        return "PrintSocketRecv:{0}".format(self.counter)


class EthSocket(RovSocket):
    def __init__(self, remote_addr:(str, int), local_addr:(str, int) = ('', 0)):
        self.target = remote_addr
        self.local = local_addr
        self.socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        self.socket.bind(local_addr) # local ip and port - random

    def __del__(self):
        self.socket.close()

    def send(self, data):
        self.socket.sendto(data, self.target)

    def recv(self):
        return self.socket.recv()
