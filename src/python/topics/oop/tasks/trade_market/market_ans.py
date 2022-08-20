def main():

    marry = User("Mary", "mary@email", 54900)
    duncan = User("Duncan", "duncan@email", 1450)
    james = User("James", "james@email", 9000)

    iphone = Product("IPhone", 1000, james)

    auction = james.place_auction(iphone)

    duncan.offer(auction, 1010)
    james.offer(auction, 1400)
    duncan.offer(aucion, 1450)

    purchase = auction.sell()


if __name__ == '__main__':
    main()
