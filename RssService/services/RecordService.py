from db.database import execute_nonquery, execute_query, call_proc
from models.Record import Record, StateType

class RecordService(object):
    def __init__(self, mysql_connection):
        self.conn = mysql_connection

    def getRecordByFeedId(self, feed_id, count, start):
        #with call_proc(self.conn, "select get_records(%(feed_id)s, %(start)s, %(count)s)",
        #        feed_id = feed_id, start = start, count = count) as qry:
        with call_proc(self.conn, "get_records", feed_id, start, count, "result") as qry:
            result_cur = qry.conn.cursor("result")
            return self.mapResult(result_cur)

        #with execute_query(self.conn, "select id, feed_id, link, guid, date, link, title, description, state from record where feed_id=%(feed_id)s order by id desc limit %(count)s",
        #        feed_id = feed_id, count = count) as qry:
        #    return self.mapResult(qry.cursor())

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
        #TODO: fetch later
        rows = cursor.fetchall()
        columns = [c.name for c in cursor.description]
        return [Record(dict(zip(columns, row))) for row in rows]
        #columns = [c.name for c in cursor.description]
        #return [Record(dict(zip(columns, row))) for row in cursor.fetchall()]
