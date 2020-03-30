
class Port:

    def __init__(self, udp_ip ='', udp_port = 0):
        self.udp_ip = udp_ip
        self.udp_port = udp_port
        self.remote_port = None

    def connect(self, port):
        if self.remote_port is not None:
            raise Exception("Port is already connected")
        if port.remote_port is not None:
            raise Exception("Given port is already connected")

        self.remote_port = port
        port.remote_port = self

import socket

class Link:
    def __init__(self, target_port = None):
        self.socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        self.socket.bind('',0)
        self.target_port = None
        
        if target_port is not None:
            self.connect(self, target_port)

    def __del__(self):
        self.socket.close()

    def connect(self, port):
        self.target_port = port

    def send(self, data):
        self.socket.sendto(data, self.target_port)

    def recv(self):
        try:
            data = self.socket.recv()
        except:
            data = None
        return data 
