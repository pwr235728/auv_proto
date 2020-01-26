class AuvHost:
    def __init__(self, addr, uid):
        self.addr = addr
        self.uid = uid
        self.is_alive = True

    def set_is_alive(self, is_alive):
        self.is_alive = is_alive

    def get_is_alive(self):
        return self.is_alive

    def get_addr(self):
        return self.addr

    def get_uid(self):
        return self.uid
