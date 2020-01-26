from datetime import datetime
import time 
import struct

import RconSerializer
import RconSession


class AuvControll:
    def __init__(self, serializer, session):
        self.MODULE_ID = 1
        self.CMD_SET_DEPTH = 1
        self.serializer = serializer
        self.session = session

    def set_depth(self, depth):
        payload = struct.pack("<H", depth)
        id, data = self.serializer.encode(self.MODULE_ID, self.CMD_SET_DEPTH, payload)
        self.session.Transmit(data)
        return (id, data)