class HeadChef:

    def __init__(self, pastry_chef, waiter):
        self.pastry_chef = pastry_chef
        self.waiter = waiter

    def order(self, main, desert):
        self.pastry_chef.order(desert)

    def customer_ready_for(self, dish):
        if self.pastry_chef.is_cooked(dish):
            self.waiter.serve(dish)
