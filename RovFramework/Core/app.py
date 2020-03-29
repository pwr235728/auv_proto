def create_app():
    port = EthPort.find()
    dispatcher = Dispatcher()
    core = RovCore(dispatcher, port)

    thrusters = core.get_module('thrusters')
    gripper = core.get_module('gripper')
