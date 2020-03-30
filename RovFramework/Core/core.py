from  ispatcher import *
from event_queue import *
from event_executor import *
from  transmiter import *
from connection import *
from  ort import *
from eth_socket import *

event_queue = EventQueue()
dispatcher = Dispatcher()

eth_socket = EthSocket(("dupa", 0))
transmiter = Transmiter(event_queue, eth_socket)

event_executor = EventExecutor(event_queue, dispatcher, transmiter)

event_executor.start()
transmiter.start()
