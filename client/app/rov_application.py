import rov_module
import sys, threading, time
import enum

class ROV(enum.Enum):
    ETHERNET = 1

class RovApplication:
    @staticmethod
    def create(rov_type):
        assert rov_type in ROV, "{0} is not valid value."
        if rov_type == ROV.ETHERNET:
            return __create_ethernet()

    @staticmethod
    def __create_ethernet():



class RovApp():
    def __init__(self, link):
        self.module_list = []
        self.__processor_thread = \
            threading.Thread(target=__processor_loop, args=(self,))
        self.__processor_thread.daemon = True

    def bind_module(self, rov_module):
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
