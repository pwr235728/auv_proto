import AuvAR
import RconClient

import time


# Pozyskiwanie adresu IP łodzi

# poszukiwana sygnatura przy pozyskiwaniu adresu ip łodzi
signature = "AUV\0"

addr_res = AuvAR.AuvAddressResolver(udp_port=5004)
addr = ""

try:
    addr = addr_res.acquireAddress(signature=signature, timeout=2000)
    print("Acquired IP address: ", addr)   
except Exception as err:
    print(err) 
    raise err


# Łączenie się z łodzią 

client = RconClient.RconClient()
client.connect(addr, 5005)

counter = 0
while True:
  counter += 1
  print("packet nubmer:", counter)

  led = input("Podajnumer leda [1-3]: ")
  if led == "1":
    client.send("1")  
  if led == "2":
    client.send("2")  
  if led == "3":
    client.send("3")  
    
  time.sleep(0.05)  



