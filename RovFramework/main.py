import Core.event_queue
import Core.port
import Core.module
import Core.transmiter
import Core.connection
import Core.event_executor


queue = Core.event_queue.EventQueue()
port = Core.port.Port(queue)
module = Core.module.TestModule(port)

socket = Core.connection.PrintSocket()
transmiter = Core.transmiter.Transmiter(queue, socket)

dispatcher = None

event_executor = Core.event_executor.EventExecutor(queue, dispatcher, transmiter)

event_executor.start()
transmiter.start()

module.func1()
module.func2()

while True:
    pass
