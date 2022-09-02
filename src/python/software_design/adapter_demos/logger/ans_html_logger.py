from lib_3rd_pty import HtmlGenerator
from logger import Logger


# HtmlLogger also implements Logger
class HtmlLogger(Logger):

    def __init__(self, filename):
        self.generator = HtmlGenerator(filename)

    # Override
    def log(self, msg):
        self.generator.add_paragrath(msg)
