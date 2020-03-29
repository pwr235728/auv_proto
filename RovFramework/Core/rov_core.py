from port import Port
from module import Module
import queue

class RovCore:
    def __init__(self, dispacher, port):
        self.dispatcher = dispacher
        self.port = port

        self.input_queue = queue.Queue()
        self.output_queue = queue.Queue()

        self.__processor_thread = \
            threading.Thread(target=__processor_loop, args=(self,))
        self.__processor_thread.daemon = True

    def bind_module(self, rov_module):
        module_queue = rov_module.

        if not isinstance(rov_module, rov_module.RovModule):
            raise Exception("Given module is not a instance of RovModule")

        if rov_module in self.module_list:
            pass

        self.module_list.append(rov_module)

    def unbind_module(self, rov_module):
        if rov_module in self.module_list:
            self.module_list.remove(rov_module)

    def start(self):
        self.__processor_thread.start()

    def __processor_loop(self):
        while True:
            pass
