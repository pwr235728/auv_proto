from Module import Module
from Target import Target
from MessageBroker import MessageBroker
from Connection import Connection, EthConnection
from Serialzier import Serialzier


import socket
import time

from eth_connection import EthConnection

class EthRovDiscoverer:
    def __init__(self, udp_port=5004):
        self.connection = EthConnection(remote_addr=('', udp_port), local_addr=('', udp_port))

    def FindRov(self, signature="AUV", timeout=15):
        time_left = timeout # s

        print("Acquiring server ip address...")
        while time_left>0:
            print("Time left: ", time_left, "s.")
            time_left -= 1
            try:
                data, addr = self.sock.recvfrom(1024)
                sig, uid = RconSerializer.decode_IsAliveMsg(data)
                if sig == signature.encode():
                    return (addr[0], uid)
            except:
                pass

            time.sleep(1)

        raise Exception('Address acquisition timed out')


class SessionManager:

    @staticmethod
    def CreateEthernet(serializer):
        discoverer = EthRovDiscoverer()
        ethRovAddr = discoverer.FindRov() # get addr
        ethRov = EthConnection(remote_add=ethRovAddr)

        broker = MessageBroker(serializer)
        ethTarget = Target(broker, ethRov)
        return ethTarget
