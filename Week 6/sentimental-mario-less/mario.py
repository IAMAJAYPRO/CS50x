def main():
    while True:
        try:
            size = int(input("Height: "))
            assert 1 <= size <= 8
            break
        except (ValueError, AssertionError):
            pass

    size = int(size)
    print(get_blocks(size), end="")


def get_blocks(n: int):
    st = ""
    for i in range(1, n+1):
        st += " "*(n-i)+"#"*i + "\n"
    return st


if __name__ == "__main__":
    main()
