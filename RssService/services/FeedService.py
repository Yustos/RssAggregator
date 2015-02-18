from db.database import execute_nonquery, execute_query
from models.Feed import Feed

class FeedService(object):
    def __init__(self, mysql_connection):
        self.conn = mysql_connection

    def getAll(self):
        with execute_query(self.conn, "select id, url from feed") as qry:
            return self.mapResult(qry.cursor())

    def mapResult(self, cursor):
        columns = [c.name for c in cursor.description]
        return [Feed(dict(zip(columns, row))) for row in cursor.fetchall()]
