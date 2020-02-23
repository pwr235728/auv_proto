from Module import Module
from Target import Target
from MessageBroker import MessageBroker
from Connection import Connection, EthConnection
from Serialzier import Serialzier
from SessionManager import SessionManager

serializer = Serialzier.GetSerializer("mock")

target = SessionManager.CreateEthernet(serializer)

thrusters = Module(target)
