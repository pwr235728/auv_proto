from datetime import datetime
import time 

import AuvDiscoverer
import RconSerializer
import EthConnection
import RconSession
import AuvControll

signature = "AUV"

LOCAL = True

if not LOCAL:
    discoverer = AuvDiscoverer.AuvDiscoverer()
    target = discoverer.FindAuv(signature)
else:
    target = ('127.0.0.1', bytearray(12))

connection = EthConnection.EthConnection()

session = RconSession.RconSession(connection, (target[0], 5005))


controller = AuvControll.AuvControll(session)
depth = 0
while True:
    depth += 2
    id, data = controller.set_depth(depth)    

    print("client", end = " | ")
    print(datetime.now(), end =" | ")
    print("packet (", id, ",", str(data), ")")        
    time.sleep(1)  



