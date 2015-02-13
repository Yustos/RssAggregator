from tornado.web import RequestHandler
from Logger import LogApi
from db.database import db_context
from services.Records import Records
import json

class RecordServiceHandler(RequestHandler):
    def __init__(self, application, request, **kwargs):
        return super(RecordServiceHandler, self).__init__(application, request, **kwargs)

    @LogApi()
    def get(self, path):
        id = self.get_argument("id", default=None, strip=False)
        with db_context() as ctx:
            record = Records(ctx.conn()).getRecordById(int(id))[0]
            self.write(record.dict())

    @LogApi()
    def post(self,path):
        input = json.loads(self.request.body)
        with db_context() as ctx:
            Records(ctx.conn()).setRecordState(int(input["id"]), int(input["state"]))
            self.write("OK")