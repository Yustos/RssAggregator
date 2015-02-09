# -*- coding: utf-8 -*-
import functools
from tornado import log
import time
import os

API_Source = 1


class LogApi(object):
    def __init__(self, logger=None):
        self.logger = logger

    def __call__(self, func):
        @functools.wraps(func)
        def wrapper(*args, **kwargs):
            self.log_api(True, func.__name__, args[0].request.uri, args[0].request.body)
            f_result = func(*args, **kwargs)
            self.log_api(False, func.__name__, args[0].request.uri, "\r\n".join(str(i) for i in args[0]._write_buffer))
            return f_result

        return wrapper

    def log_api(self, is_start, name, uri, body):
        log.app_log.info("[%s]\r\n%s\r\n%s\r\n%s" % ('begin' if is_start else 'end', name, uri, body),
                         extra={"logSource": API_Source})


class Logger():
    def __init__(self):
        print "Logger initialized"

    def add(self, client, message, source=None):
        item = dict(date=time.time(), client=client, message=message)
        if source is not None:
            item["source"] = source
        print item
