import queue

class Module:
    def __init__(self):
        self.input_queue = queue.Queue()
        self.output_queue = None
        self.module_id = None

    def send(self, msg):
        assert len(msg) < 256, "msg is too long"

        self.output_queue.put((self.module_id, len(msg), msg))

    def recv(self):
        try:
            return self.input_queue.get(block=false)
        except:
            return None

    def bind(self, output_queue):
        return input_queue

    def unbind(self):
        self.output_queue = None
