from db.database import execute_nonquery, execute_query
from models.Record import Record, StateType

class Records(object):
    def __init__(self, mysql_connection):
        self.conn = mysql_connection

    def getRecordById(self, id):
        with execute_query(self.conn, "select id, feed_id, guid, date, link, title, description, state from records where id=%(id)s", id=id) as qry:
            return Record(dict(zip(qry.cursor().column_names, qry.cursor().fetchone())))

    def getLastRecords(self, count):
        with execute_query(self.conn, "select id, feed_id, guid, date, link, title, description, state from records where state<>%(state)s order by date desc limit %(count)s", state = StateType.Readed, count=count) as qry:
            return [Record(dict(zip(qry.cursor().column_names, r))) for r in qry.cursor().fetchall()]

    def setRecordState(self, id, state):
        with execute_nonquery(self.conn, "call set_record_state(%(id)s, %(state)s)", id = id, state = state) as qry:
            pass
