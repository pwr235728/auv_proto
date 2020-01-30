import socket
import time
import struct

from datetime import datetime
from datetime import timedelta

class EthConnection:
  def __init__(self):
      self.socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
      self.socket.bind(('', 0)) # local ip and port - random 
      self.socket.settimeout(0)

  def sendto(self, data, target):
    self.socket.sendto(data, target)

  def recvfrom(self):
    try:
      data, addr = self.socket.recv()
      return (data, addr)
    except:
      return ( b'' , ('', 0))