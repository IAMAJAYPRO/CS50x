def main():
    text = input("Text: ").strip()
    grade_lvl = get_grade_lvl(text)
    print(grade_lvl)


def get_grade_lvl(text: str):
    words, letters, sentences = count(text)
    L = letters*100/words
    S = sentences*100/words
    index = 0.0588 * L - 0.296 * S - 15.8
    if index < 1:
        return "Before Grade 1"
    elif 1 <= index < 16:
        return f"Grade {round(index)}"
    else:
        return "Grade 16+"


def count(text: str):
    """
    Counts the number of words, letters, and sentences in the given text.

    Args:
        text (str): The input text to be analyzed.

    Returns:
        tuple: A tuple containing the number of words, letters, and sentences in the text.

    Example:
        words, letters, sentences = count("Hello! How are you?")
    """
    sen_sp = "!.?"  # sentence splitter
    words = text.count(" ")+1
    letters = 0
    sentences = 0
    for ch in text:
        if ch.isalnum():
            letters += 1
        if ch in sen_sp:
            sentences += 1

    text.count(" ")
    return words, letters, sentences


if __name__ == "__main__":
    main()
