import socket
import time
import struct


TCP_IP = '192.168.100.113'
TCP_PORT = 5005

'''
 RCON frame format:
 [ '>' | ID: u16 | Module: u8 | Cmd: u8 | LEN: u8 | BODY: 0-255 bytes | '<' ]
 '>'     : char
 id      : uint16_t
 module  : uint8_t
 cmd     : uint8_t
 len     : uint8_t : length of the data field
 data    : uint8_t[255] binary data
 '<'     : uint8_t
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
    
    
  def _get_data(self, id, module, cmd, payload):
    data = bytearray()
    data += b'>'
    data += struct.pack("<H", id)
    data += struct.pack("<B", module)
    data += struct.pack("<B", cmd)
    size = len(payload)
    data += struct.pack("<B", size)
    data += payload
    data += b'<'
    return data
  
  def send(self, module, cmd, payload = b'', timeout_ms=100):
    self.counter += 1
    data = self._get_data(self.counter, module, cmd, payload)
    self.socket.sendto(data, self.dest)
    return self.counter

  def recv(self):
    return self.socket.recv(1000)
    
    
# example code
def _example():
  client = RconClient()
  client.connect(TCP_IP, TCP_PORT)

  ...
    
    
    
    
    
    
    
    
    
    
