import port

class RovDiscoverer:
    @staticmethod
    def discover()

target = RovDiscoverer.discover()

link = Link(target)

session = Session()
session.start_discoverer()

session.list_targets()



# user side:
from rov_application import *

rov_app = RovApplication.create(ROV.ETHERNET)

rov_app.bind_module(thrusters_controll)
rov_app.bind_module(sensor_data)

rov_app.start()

# infinite loop
while True:
    pass
