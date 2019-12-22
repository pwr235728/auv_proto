import RconClient

class AuvController:
    def __init__(self, rcon_client):
        self._rcon_client = rcon_client

    def move(self, x, y ,z):
        self._rcon_client.send(1, "AuvController.move")

    def set_depth(self, depth):
        self._rcon_client.send(1, "AuvController.set_depth")

    def get_depth(self, depth):
        pass