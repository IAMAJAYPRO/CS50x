def main():
    while True:
        try:
            owed = float(input("Change: "))*100  # cents
            assert owed >= 0
            break
        except (ValueError, AssertionError):
            pass

    owed = int(owed)
    print(get_coins(owed))


def get_coins(change: int):
    coins = 0
    coin_types = [25, 10, 5, 1]
    for coin in coin_types:
        while change >= coin:
            coins += 1
            change -= coin
    return coins


if __name__ == "__main__":
    main()
