from tornado.ioloop import IOLoop
from tornado.web import RequestHandler, Application, url, UIModule
from tornado import log
import logging
import os
from api.ListServiceHandler import ListServiceHandler
from api.RecordServiceHandler import RecordServiceHandler
from Logger import Logger
logInstance = None


class LoggerHandler(logging.Handler):
    def emit(self, record):
        logInstance.add("", self.format(record), record.logSource if hasattr(record, "logSource") else None)

    @staticmethod
    def LogRequest(handler):
            logInstance.add(handler.request.remote_ip, handler.request.uri)

settings = {
    "log_function": LoggerHandler.LogRequest
}

application = Application([
    url(r"/api/list(.*)", ListServiceHandler, name="listService"),
    url(r"/api/record(.*)", RecordServiceHandler, name="recordService"),
], **settings)

if __name__ == "__main__":
    logInstance = Logger()
    application.listen(9370)

    logInstance.add("local", "Start")
    log.app_log.addHandler(LoggerHandler())

    log.enable_pretty_logging()

    IOLoop.instance().start()

