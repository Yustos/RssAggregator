from tornado.web import RequestHandler
from Logger import LogApi
from db.database import db_context
from services.Records import Records

class ListServiceHandler(RequestHandler):
    def __init__(self, application, request, **kwargs):
        return super(ListServiceHandler, self).__init__(application, request, **kwargs)

    @LogApi()
    def get(self, path):
        count = self.get_argument("count", default=None, strip=False)
        with db_context() as ctx:
            records = Records(ctx.conn()).getLastRecords(int(count))
            self.write({ "items": [r.dict() for r in records] })

