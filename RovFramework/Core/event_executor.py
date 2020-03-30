import threading
import Core.event

import Core.event_queue

class EventExecutor:
    def __init__(self, event_queue, dispatcher, transmiter):
        self.dispatcher = dispatcher
        self.transmiter = transmiter
        self.queue = event_queue
        self.__loop_thread = threading.Thread(target=EventExecutor.__loop, args=(self,))
        self.__loop_thread.daemon = True

    def start(self):
        self.__loop_thread.start()

    def _dispatch(self, event):
        self.dispatcher.dispatch(event.get_data())

    def _transmit(self, event):
        self.transmiter.transmit(event.get_data())

    def __loop(self):
        while True:
            event = self.queue.dequeue()
            if event.get_type() is Core.event.EventType.MSG_INCOMING:
                self._dispatch(event)

            if event.get_type() is Core.event.EventType.MSG_OUTGOING:
                self._transmit(event)
