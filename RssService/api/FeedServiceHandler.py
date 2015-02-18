from tornado.web import RequestHandler
from Logger import LogApi
from db.database import db_context
from services.FeedService import FeedService
import json

class FeedServiceHandler(RequestHandler):
    def __init__(self, application, request, **kwargs):
        return super(FeedServiceHandler, self).__init__(application, request, **kwargs)

    @LogApi()
    def get(self, path):
        with db_context() as ctx:
            feeds = FeedService(ctx.conn()).getAll()
            self.write({ "items": [f.dict() for f in feeds]})
