from db.database import execute_nonquery, execute_query
from models.Record import Record, StateType

class Records(object):
    def __init__(self, mysql_connection):
        self.conn = mysql_connection

    def getRecordById(self, id):
        with execute_query(self.conn, "select id, feed_id, link, guid, date, link, title, description, state from record where id=%(id)s", id=id) as qry:
            return self.mapResult(qry.cursor())

    def getLastRecords(self, count):
        with execute_query(self.conn, "select id, feed_id, date, link, title, description, state from record where state<>%(state)s order by date desc limit %(count)s", state = StateType.Readed, count=count) as qry:
            return self.mapResult(qry.cursor())

    def setRecordState(self, id, state):
        with execute_nonquery(self.conn, "select set_record_state(%(id)s, %(state)s::smallint)", id = id, state = state) as qry:
            pass

    def mapResult(self, cursor):
        columns = [c.name for c in cursor.description]
        return [Record(dict(zip(columns, row))) for row in cursor.fetchall()]
