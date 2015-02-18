import sys
import psycopg2
import json
import os

__location__ = os.path.realpath(os.path.join(os.getcwd(), os.path.dirname(__file__)))
with open(os.path.join(__location__, "..", "settings.conf")) as f:
    CONFIG = json.load(f)

class db_context(object):

    def __init__(self):
        self.connectionString = CONFIG.get('connectionString');
        self._conn = None;

    def conn(self):
        return self._conn

    def commit(self):
        self._conn.commit()

    def __enter__(self):
        self._conn = psycopg2.connect(self.connectionString)
        return self

    def __exit__(self, type, value, traceback):
        try:
            self._conn.close()
        except:
            e = sys.exc_info()[0]
            print e

class execute_query(object):
    
    def __init__(self, conn, statement, *prepared_args, **kwargs):
        self.conn = conn
        self.stmt = statement
        self.prepared_args = kwargs
        self._cursor = None

    def cursor(self):
        return self._cursor

    def __enter__(self):
        self._cursor = self.conn.cursor()
        self._cursor.execute(self.stmt, self.prepared_args)
        return self

    def __exit__(self, type, value, traceback):
        try:
            self._cursor.close()
        except:
            e = sys.exc_info()[0]
            print e

class call_proc(object):
    
    def __init__(self, conn, statement, *prepared_args):
        self.conn = conn
        self.stmt = statement
        self.prepared_args = prepared_args
        self._cursor = None

    def cursor(self):
        return self._cursor

    def __enter__(self):
        self._cursor = self.conn.cursor()
        self._cursor.callproc(self.stmt, self.prepared_args)
        return self

    def __exit__(self, type, value, traceback):
        try:
            self._cursor.close()
        except:
            e = sys.exc_info()[0]
            print e

class execute_nonquery(object):
    
    def __init__(self, conn, statement, *prepared_args, **kwargs):
        self.conn = conn
        self.stmt = statement
        self.prepared_args = kwargs
        self._cursor = None

    def cursor(self):
        return self._cursor

    def __enter__(self):
        self._cursor = self.conn.cursor()
        self._cursor.execute(self.stmt, self.prepared_args)
        self.conn.commit()
        return self

    def __exit__(self, type, value, traceback):
        try:
            self._cursor.close()
        except:
            e = sys.exc_info()[0]
            print e
