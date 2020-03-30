import queue

class EventQueue:
    def __init__(self):
        self.queue = queue.Queue()

    def enqueue(self, event):
        self.queue.put(event)
        print(("EventQueue.enqueue(): ", event.get_data()))

    def dequeue(self):
        return self.queue.get()
