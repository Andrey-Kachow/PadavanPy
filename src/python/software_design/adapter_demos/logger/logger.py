from lib_3rd_pty import FileInfoWriter


# Interface
class Logger:
    def log(self, msg):
        pass


# PrintLogger implements Logger
class PrintLogger(Logger):
    # Override
    def log(self, msg):
        print(msg)


# ADAPTER
# FileLogger also implements Logger
class FileLogger(Logger):

    def __init__(self, filename):
        self.writer = FileInfoWriter(filename)

    # Override
    def log(self, msg):
        self.writer.info(msg)
