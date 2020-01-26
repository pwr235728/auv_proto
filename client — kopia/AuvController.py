import RconClient
import struct

class AuvController:
    def __init__(self, module_id, rcon_client):
        self._rcon_client = rcon_client
        self.module_id = module_id

    def move(self, x, y):
        payload = bytearray()
        payload += struct.pack("<h", x)
        payload += struct.pack("<h", y)
        self._rcon_client.send(self.module_id, 1, payload)

    def set_depth(self, depth):
        self._rcon_client.send(self.module_id, 2, struct.pack("<h", depth))

    def get_depth(self, depth):
        pass