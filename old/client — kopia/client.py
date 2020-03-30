from datetime import datetime
import time 

import AuvDiscoverer
import RconSerializer
import EthConnection
import RconSession
import AuvControll

signature = "AUV"

LOCAL = True

if LOCAL:
    discoverer = AuvDiscoverer.AuvDiscoverer()
    auvHost = discoverer.FindAuv(signature)
else:
    auvHost = ('127.0.0.1', bytearray(12))

connection = EthConnection.EthConnection()

dispatcher = Dispatcher(auvHost)


session = RconSession.RconSession(connection, target)


controller = AuvControll.AuvControll(serializer, session)
depth = 0
while True:
    depth += 2
    id, data = controller.set_depth(depth)    

    print("client", end = " | ")
    print(datetime.now(), end =" | ")
    print("packet (", id, ",", str(data), ")")        
    time.sleep(1)  



