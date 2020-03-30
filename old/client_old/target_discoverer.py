import socket
import time

from eth_connection import EthConnection

class AuvDiscoverer:
    def __init__(self, udp_port=5004):
        self.connection = EthConnection(remote_addr=('', udp_port), local_addr=('', udp_port))

    def FindAuv(self, signature="AUV", timeout=15):
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