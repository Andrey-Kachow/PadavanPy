from services import ExpensiveEvaluator
from proxies import CachedEvaluator

class Client:

    def run(self):

        evaluator = ExpensiveEvaluator()
        # evaluator = CachedEvaluator()

        expressions = [
            "1 + 1",
            "1 + 1",
            "1 + 1"
        ]

        for expression in expressions:
            print(expression, end=" = ", flush=True)
            print(evaluator.evaluate(expression))

        print("Done")


if __name__ == '__main__':
    Client().run()
