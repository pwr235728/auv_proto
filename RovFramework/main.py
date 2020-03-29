from rov_core import *
from port_eth import *

# port = SpiRov()
eth_rov = EthernetRov()
port = eth_rov.find()
rov = RovCore(port)

rov.bind_module(...)
rov.bind_module(...)

rov.start()
