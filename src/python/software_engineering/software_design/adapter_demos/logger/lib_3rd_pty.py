import smtplib, ssl, os

class __FileWriter:
    def __init__(self, filename):
        self.filename = filename
        with open(filename, "w") as f:
            f.write("")

    def _write(self, msg):
        with open(self.filename, "a") as f:
            f.write(msg + "\n")


class FileInfoWriter(__FileWriter):

    def __init__(self, filename):
        super().__init__(filename)

    def info(self, msg):
        self._write(f"[INFO] - {msg}")

    def error(self, msg):
        self._write(f"[ERROR] - {msg}")

    def debug(self, msg):
        self._write(f"[DEBUG] - {msg}")


class HtmlGenerator(__FileWriter):

    def __init__(self, filename):
        super().__init__(filename)

    def add_paragrath(self, msg):
        self._write(f"<p>{msg}</p>")

    def add_line_break(self):
        self._write("<br>")

    def add_heading(self, msg):
        self._write(f"<h2>{msg}</msg>")
