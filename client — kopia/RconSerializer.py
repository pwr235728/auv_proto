import socket
import time
import struct

from datetime import datetime
from datetime import timedelta

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
class RconSerializer:
  def __init__(self):
    self.counter = 0  
  
  def encode(self, module, cmd, payload = b''):
    self.counter += 1
    data = bytearray()
    data += b'>'
    data += struct.pack("<H", self.counter)
    data += struct.pack("<B", module)
    data += struct.pack("<B", cmd)
    size = len(payload)
    data += struct.pack("<B", size)
    data += payload
    data += b'<'
    return (self.counter, data)

  def decode(self):
    pass

  @staticmethod
  def decode_IsAliveMsg(raw_data):
    # format:
    # signature:uid
    # signaturre is string, uid is 12 byte number
    length = len(raw_data)
    if length > 13:
      sig = raw_data[0:-13]
      uid = raw_data[-13:-1]
      return (sig, uid)
    else:
      # wrong format
      return ('', bytearray(12))
