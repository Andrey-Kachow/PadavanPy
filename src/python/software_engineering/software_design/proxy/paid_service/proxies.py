from services import ExpensiveEvaluator


class CachedEvaluator:

    def __init__(self):
        self.saved_results = {}
        self.evaluator = ExpensiveEvaluator()

    def evaluate(self, expression):
        if expression in saved_results:
            return saved_results[expression]
        return self.evaluator.evaluate(expression)
