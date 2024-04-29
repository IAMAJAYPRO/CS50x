def main():
    while True:
        try:
            card = input("Number: ").strip()
            assert card.isnumeric()
            break
        except (ValueError, AssertionError):
            pass

    if checksum(card) and (type_card := card_type(card)):
        print(type_card)
    else:
        print("INVALID")


def checksum(card: str):
    rev = card[::-1]
    su_ev_digs: str = "".join([str(2*int(x)) for x in rev[1::2]])
    # print("digs_ev=", su_ev_digs)
    su_ev_2 = sum([int(x) for x in su_ev_digs])
    su_od = sum([int(x) for x in rev[::2]])
    total = su_ev_2+su_od
    # print("total:", total)
    if total % 10 == 0:
        return True


def card_type(card: str):
    card_len = len(card)
    front_two_digs = card[:2]
    if card_len == 15 and front_two_digs in ["34", "37"]:
        return "AMEX"
    elif card_len == 16 and 51 <= int(front_two_digs) <= 55:
        return "MASTERCARD"
    elif card_len in [13, 16] and card[0] == "4":
        return "VISA"


if __name__ == "__main__":
    main()
