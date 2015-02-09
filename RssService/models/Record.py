from enum import Enum


class StateType(Enum):
    Unknown = -1
    Unread = 0
    UnreadModified = 1
    Readed = 2


class Record():
    def __init__(self, id, feed_id, date, title, description, state=StateType.Unknown):
        self.id = id
        self.feed_id = feed_id
        self.date = date
        self.title = title
        self.description = description
        self.state = state

    def __init__(self, d):
        self.id = d["id"]
        self.feed_id = d["feed_id"]
        self.date = d["date"]
        self.title = d["title"]
        self.description = d["description"]
        self.state = d["state"]

    def dict(self):
        result = {
            "id": self.id,
            "feed_id": self.feed_id,
            "date": self.date,
            "title": self.title,
            "description": self.description,
            "state": self.state
            }
        return result;
