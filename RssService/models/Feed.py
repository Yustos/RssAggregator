class Feed():
    def __init__(self, id, url):
        self.id = id
        self.url = url

    def __init__(self, d):
        self.id = d["id"]
        self.url = d["url"]

    def dict(self):
        result = {
            "id": self.id,
            "url": self.url
            }
        return result;
