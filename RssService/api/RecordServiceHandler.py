from tornado.web import RequestHandler
from Logger import LogApi
from db.database import db_context
from services.RecordService import RecordService
import json

class RecordServiceHandler(RequestHandler):
    def __init__(self, application, request, **kwargs):
        return super(RecordServiceHandler, self).__init__(application, request, **kwargs)

    @LogApi()
    def get(self, path):
        id = self.get_argument("id", default=None, strip=False)
        feed_id = self.get_argument("feed_id", default=None, strip = False)
        with db_context() as ctx:
            if feed_id is not None:
                start = self.get_argument("start", default=None, strip = False)
                count = self.get_argument("count", default=None, strip = False)
                records = RecordService(ctx.conn()).getRecordByFeedId(int(feed_id), int(count), None if start is None else int(start))
                self.write({"items": [r.dict() for r in records]})
            else:
                record = RecordService(ctx.conn()).getRecordById(int(id))[0]
                self.write(record.dict())

    @LogApi()
    def post(self,path):
        input = json.loads(self.request.body)
        with db_context() as ctx:
            RecordService(ctx.conn()).setRecordState(int(input["id"]), int(input["state"]))
            self.write("OK")