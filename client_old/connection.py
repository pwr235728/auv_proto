from abc import ABC, abstractmethod

class Connection(ABC):

    def __init__(self):
        super.__init__()

    @abstractmethod
    def send(self, data: bytearray) -> None:
        pass

    @abstractmethod
    def recv(self) -> bytearray:
        pass
