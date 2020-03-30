import Core.connection
from Core.event import *
import threading

class Transmiter:
    def __init__(self, event_queue, eth_socket):
        self.__connection_thread = \
            threading.Thread(target=Transmiter.__connection_loop, args=(self,))
        self.__connection_thread.daemon = True
        self.event_queue = event_queue
        self.eth_socket = eth_socket

    def transmit(self, data):
        self.eth_socket.send(data)

    def start(self):
        self.__connection_thread.start()

    def __connection_loop(self):
        while True:
            data = self.eth_socket.recv()
            self.event_queue.enqueue(EventResponse(data))
            #self.event_queue.put(Event(EventType.MSG_INCOMING, data))
