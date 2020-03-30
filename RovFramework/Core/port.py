from Core.event import *
from queue import Queue

class Port:
    def __init__(self, event_queue):
        self.queue = Queue()
        self.event_queue = event_queue

    def put_response(self, data):
        self.queue.put(data)

    def send(self, data):
        self.event_queue.enqueue(EventRequest(data))
        #self.event_queue.put(Event(EventType.MSG_OUTGOING, data))

    def recv(self):
        return self.queue.dequeue()
