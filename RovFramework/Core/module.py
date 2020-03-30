import queue
import Core.port

class Module:
    def __init__(self, id, port):
        self.port = port
        self.module_id = id

    def send(self, data):
        assert len(data) < 256, "msg is too long"
        self.port.send((self.module_id, len(data), data))

    def recv(self):
        try:
            return self.port.recv()
        except:
            return None

    def get_port(self):
        return self.port


class TestModule(Module):
    def __init__(self, port):
        super().__init__(0, port)

    def func1(self):
        super().send("FUNC1_DATA")

    def func2(self):
        super().send("FUNC2_DATA")
