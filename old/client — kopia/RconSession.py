import socket
import time
import struct

from datetime import datetime
from datetime import timedelta

class RconSession:
  def __init__(self, connection, target):
    self.connection = connection
    self.target = target

  def Transmit(self, msg):
    self.connection.sendto(msg, self.target)

  def Receive(self, timeout_ms = 100):
    while True:
      if timeout_ms <= 0:
        return (b'', ('',0))
      data, addr = self.connection.recvfrom()
      if addr[0] == '' and addr[1] == 0: # no data
        timeout_ms -= 1
        time.sleep(0.001)
      else:
        return (data, addr) 