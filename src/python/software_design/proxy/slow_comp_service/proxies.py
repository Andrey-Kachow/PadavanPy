from services import ExpensiveEvaluator


class CachedEvaluator:

    def __init__(self):
        self.saved_results = {}
        self.evaluator = ExpensiveEvaluator()

    def evaluate(self, expression):
        if expression in self.saved_results:
            return self.saved_results[expression]

        result = self.evaluator.evaluate(expression)
        self.saved_results[expression] = result
        return result
