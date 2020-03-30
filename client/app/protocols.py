"""
udp - frame - pdu (module data) - module_content


FORMATS:
udp:                 {FRAME:u16}
frame(pdu):          {SIGNATURE:char[4], LEN:u16, PAYLOAD[LEN]}
payload(serializer): {ID:u8, DATA_LEN:u8, DATA[DATA_LEN]}

"""
import struct

class Protocol:
    pass

class Pdu(Protocol):
    pass

class Serializer(Protocol):
    pass

class PduData:
    def __init__(self):
        self.__signature = "AUV:"
        self.__data = bytearray()

    def get_len(self):
        return len(self.__data)

    def get_payload(self):
        return self.__data

    def set_payload(self, data):
        if type(data) is not bytearray:
            raise Exception("Data type have to be a bytearray")
        self.__deta = data

    def __bytes__(self):
        header = struct.pack('!4cH', self.__signature, self.get_len)
        payload_template = "!{0}B".format(self.get_len())
        payload = struct.pack(payload_template,, self.__data)
        data = header + payload

    def pack(self):
        return self.__bytes__()

    def unpack(self, data):
        if len(data) < 6:
            return None

        signature, length = struct.unpack('!4cH', data[0:6])
        if len(data) < 6+length:
            return None

        if signature != "AUV:":
            asdasdas

        payload_template = "!{0}B".format(length)
        payload = struct.unpack(payload_template, data[6:6+length])
