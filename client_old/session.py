from abc import ABC, abstractmethod

class Session(ABC):

    def __init__(self):
        super.__init__()

    @abstractmethod
    def transmit(self) -> None:
        pass
    
    @abstractmethod
    def receive(self) -> bytearray:
        pass

class EthSession(Session):

    def __init__(self):
        super.__init__()

    @abstractmethod
    def transmit(self) -> None:
        pass
    
    @abstractmethod
    def receive(self) -> bytearray:
        pass