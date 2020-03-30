from Module import Module
from Session import SessionManager, Target

serializer = Serialzier.GetSerializer("mock")

target = SessionManager.CreateEthernet(serializer)
thrusters = Module(target)
