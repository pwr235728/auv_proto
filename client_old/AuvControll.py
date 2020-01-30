from datetime import datetime
import time 
import struct

from RconSerializer import RconSerializer
import RconSession


class AuvControll:
    def __init__(self, session):
        self.MODULE_ID = 1
        self.CMD_SET_DEPTH = 1
        self.session = session

    def set_depth(self, depth):
        payload = struct.pack("<H", depth)
        id, data = RconSerializer.encode(self.MODULE_ID, self.CMD_SET_DEPTH, payload)
        self.session.Transmit(data)
        return (id, data)