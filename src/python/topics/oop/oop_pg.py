class MyClass:
    pass

instance_1 = MyClass()
instance_2 = MyClass()

instance_1.first = 1
instance_1.second = 2
instance_1.third = 3
instance_1.fourth = 4

MyClass.class_property = 100


##############################FUN_VS_METHODS####################################


class Cheburek:

    # Later
    def price_increase(self, amount):
        self.price += amount


def cheburek_price_increase(cheburek, amount):
    cheburek.price += amount

cheb_1 = Cheburek()
cheb_2 = Cheburek()

cheb_1.price = 100
cheb_2.price = 100


############################## CONSTRUCTORS ####################################


class Pizza:
    pass

    # Later
    # def __init__(self, cheese, tomato, mushrooms):
    #     self.cheese = cheese
    #     self.tomato = tomato
    #     self.mushrooms = mushrooms


def pizza_create(cheese, tomato, mushrooms):
    pizza = Pizza()
    pizza.cheese = cheese
    pizza.tomato = tomato
    pizza.mushrooms = mushrooms
    return pizza


############################## CONSTRUCTORS ####################################
