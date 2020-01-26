import socket
import time

import EthConnection
from RconSerializer import RconSerializer

class AuvDiscoverer:
    def __init__(self, udp_port=5005):
        self.UDP_IP = ''
        self.UDP_PORT = udp_port

        self.sock = socket.socket(socket.AF_INET,    # internet
                                  socket.SOCK_DGRAM) # UDP
        self.sock.bind((self.UDP_IP, self.UDP_PORT))
        self.sock.settimeout(0)

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
