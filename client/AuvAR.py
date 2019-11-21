import socket
import time

class AuvAddressResolver:
    def __init__(self, udp_port=5005):
        self.UDP_IP = ''
        self.UDP_PORT = udp_port

        self.sock = socket.socket(socket.AF_INET,    # internet
                                  socket.SOCK_DGRAM) # UDP
        self.sock.bind((self.UDP_IP, self.UDP_PORT))
        self.sock.settimeout(0)


    def acquireAddress(self, signature="AUV", timeout=15):
        time_left = timeout # s

        print("Acquiring server ip address...")
        while time_left>0:
            print("Time left: ", time_left, "s.")
            time_left -= 1
            try:
                data, addr = self.sock.recvfrom(1024)
                if data == signature.encode():
                    return addr[0]
            except:
                pass

            time.sleep(1)

        raise Exception('Address acquisition timed out')


# example code
def _example():
    res = AuvAddressResolver()

    try:
        addr = res.acquireAddress(signature="AUV2.0", timeout=20)
    except Exception as err:
        print(err) 
        raise err

    print("Acquired IP address: ", addr)       