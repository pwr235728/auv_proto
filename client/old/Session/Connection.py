from abc import ABC, abstractmethod

class Connection(ABC):

    def __init__(self):
        super.__init__()

    @abstractmethod
    def send(self, data: bytearray) -> None:
        pass

    @abstractmethod
    def recv(self) -> bytearray:
        pass

# Implementation 

import socket
import time
import struct

from datetime import datetime
from datetime import timedelta

from connection import Connection

class EthConnection(Connection):
    def __init__(self, remote_addr:(str, int), local_addr:(str, int) = ('', 0)):
        super.__init__()
        self.target = remote_addr
        self.local = local_addr
        self.socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        self.socket.bind(local_addr) # local ip and port - random 
        self.socket.settimeout(0)

    def __del__(self):
        self.socket.close()

    def send(self, data: bytearray) -> None:
        self.socket.sendto(data, self.target)

    def recv(self) -> bytearray:
        try:
            data = self.socket.recv()
        except:
            data = bytearray()
        return data
