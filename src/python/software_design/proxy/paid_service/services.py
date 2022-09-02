import time


class AdvertismentEvaluator:

    PREMIUM_PRICE = 100

    def __print_charwise(self, msg, end="\n"):
        for ch in msg:
            print(ch, end="", flush=True)
            time.sleep(0.3)
        print(end)

    def __display_ads(self):
        print()
        self.__print_charwise("""
            ### Cегодняшний спонсор: ###

            Магазин "Пельмешки без спешки"!

            - Наслаждайся сколько хочешь!
                            без спешки!
        """)
        print()

    def evaluate(self, expression, money):
        if money < AdvertisentEvaluator.PREMIUM_PRICE:
            self.__display_ads()
        return eval(expression)
