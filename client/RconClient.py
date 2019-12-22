import socket
import time
import struct


TCP_IP = '192.168.100.113'
TCP_PORT = 5005

'''
# RCON frame format
# '>'     : char
# id      : uint16_t
# type    : uint8_t
# size    : uint8_t : size of the data field
# data    : uint8_t[255]
# '<'     : uint8_t
'''

# proba ubrania tego w klase
class RconClient:
  def __init__(self):
    self.socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    #self.connection = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    self.counter = 0
   
   
  def connect(self, ip_addr, port):
    self.dest = (ip_addr, port)
    #self.connection.connect((ip_addr, port))
    # return some state or idk
    
    
  def _get_data(self, packet_id, packet_type, packet_msg):
    data = bytearray()
    data += b'>'
    data += struct.pack("<H", packet_id)
    data += struct.pack("<B", packet_type)
    size = len(packet_msg) +1  # +1 - null-terminating char
    data += struct.pack("<B", size)
    data += packet_msg.encode()
    data += b'\x00'
    data += b'<'
    return data
  
  def send(self, type, msg, timeout_ms=100):
    self.counter += 1
    data = self._get_data(self.counter, type, msg)
    self.socket.sendto(data, self.dest)
    #self.connection.send(data)
    # receive the response
    # retransmit
    # etc    
    return self.counter

  def request(self, type, msg, timeout_ms=100):
      self.counter += 1
      data = self._get_data(self.counter, type, msg)
      self.socket.sendto(data, self.dest)

  def recv(self):
    return self.socket.recv(1000)
    
    
# example code
def _example():
  client = RconClient()
  client.connect(TCP_IP, TCP_PORT)

  counter = 0
  while True:
    counter += 1
    print("packet nubmer:",counter)
    client.send(1, "test")
    #ret = client.recv()
    #print("ret: ", ret)
    #client.send(2, "test")
    
    time.sleep(0.1)  
    
    
    
    
    
    
    
    
    
    
