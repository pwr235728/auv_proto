import queue


class MessageBroker:

    def __init__(self):
        self.modules_queues = {}
        self.send_queue = queue.Queue()

    def add_module(self, module):
        self.modules_queues[module] = queue.Queue()


class Module:

    def bind(self, broker):
        self.broker = broker
        broker.add_module(self)

    def send(self, msg):
        self.broker.send(self.id, msg)

    def recv(self):
        return self.broker.recv(self.id)
