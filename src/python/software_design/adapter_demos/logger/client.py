import os

from logger import PrintLogger
from logger import FileLogger
from ans_html_logger import HtmlLogger


class Client:

    # logger = PrintLogger()
    logger = FileLogger("mylogfile.log")
    # logger = HtmlLogger("logs.html")

    def run(self):
        Client.logger.log("Client started working...")

        # Do some stuff

        Client.logger.log("Client finished working...")


if __name__ == '__main__':
    Client().run()
