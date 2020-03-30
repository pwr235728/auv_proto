import enum


class EventType(enum.Enum):
    MSG_INCOMING = 1
    MSG_OUTGOING = 2


class Event:
    def __init__(self, event_type, data):
        self.type = event_type
        self.data = data

    def get_type(self):
        return self.type

    def get_data(self):
        return self.data

class EventRequest(Event):
    def __init__(self, data):
        super().__init__(EventType.MSG_OUTGOING, data)

class EventResponse(Event):
    def __init__(self, data):
        super().__init__(EventType.MSG_INCOMING, data)
