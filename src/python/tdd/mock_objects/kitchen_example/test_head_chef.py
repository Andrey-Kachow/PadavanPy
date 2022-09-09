from kitchen import *

class MyMockery:
    def __init__(self):
        self.expectations = []
        self.actuals = []
        self.objects = []
        self.exp_index = -1
        self.act_index = -1

    def add_mock(self, obj):
        self.objects.append(obj)

    def add_expectations(self, expectations):
        self.expectations += expectations

    def check_call(self):
        self.exp_index += 1
        self.act_index += 1
        assert self.expectations[self.exp_index] == self.actuals[self.act_index]

        if self.exp_index + 1 >= len(self.expectations):
            return None
        maybe_return = self.expectations[self.exp_index + 1]
        if isinstance(maybe_return, Returns):
            self.exp_index += 1
            return maybe_return.value
        return None

class Returns:
    def __init__(self, value):
        self.value = value

    def __eq__(self, other):
        return self.value == other.value

class MyMock:
    def __init__(self, context):
        self.context = context
        self.callcounts = {}


class DummyPastryChef(MyMock):

    def order(self, desert):
        self.context.actuals.append((self, self.order, (desert,)))
        self.context.check_call()

    def is_cooked(self, desert):
        self.context.actuals.append((self, self.is_cooked, (desert,)))
        return self.context.check_call()


class DummyWaiter(MyMock):

    def serve(self, dish):
        self.context.actuals.append((self, self.serve, (dish,)))
        self.context.check_call()

tart = "Apple Tart"
chicken = "Roast Chicken"

def kitchen_mocks_setup():
    context = MyMockery()

    pastry_chef = DummyPastryChef(context)
    waiter = DummyWaiter(context)

    context.add_mock(pastry_chef)
    context.add_mock(waiter)

    return context, pastry_chef, waiter


def test_head_chef_delegates_deserts_to_pastry_chef():

    context, pastry_chef, waiter = kitchen_mocks_setup()

    context.add_expectations([
        (pastry_chef, pastry_chef.order, (tart,))
    ])

    head_chef = HeadChef(pastry_chef, waiter)

    # Actual Scenario
    head_chef.order(chicken, tart)
    # End of actual Scenario


def test_head_chef_asks_waiter_to_serve_desert_when_ready():

    context, pastry_chef, waiter = kitchen_mocks_setup()

    context.add_expectations([
        (pastry_chef, pastry_chef.is_cooked, (tart,)), Returns(True),
        (waiter, waiter.serve, (tart,))
    ])

    head_chef = HeadChef(pastry_chef, waiter)

    # Actual Scenario
    head_chef.customer_ready_for(tart)
    # End of actual Scenario


def test_head_chef_does_not_ask_waiter_to_serve_desert_when_not_ready():

    context, pastry_chef, waiter = kitchen_mocks_setup()

    context.add_expectations([
        (pastry_chef, pastry_chef.is_cooked, (tart,)), Returns(False),
    ])

    head_chef = HeadChef(pastry_chef, waiter)

    # Actual Scenario
    head_chef.customer_ready_for(tart)
    # End of actual Scenario
