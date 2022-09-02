import time


class ExpensiveEvaluator:

    def __delay(self, seconds):
        time.sleep(seconds)

    def evaluate(self, expression):
        self.__delay(seconds=5)
        return eval(expression)
