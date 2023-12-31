from cs50 import get_string


def main():
    # Input text from user
    text = get_string("Text: ")

    # Caluculate the number of letters per 100 words
    L = (count_letters(text) / count_words(text)) * 100
    # Caluculate the number of sentences per 100 words
    S = (count_sentences(text) / count_words(text)) * 100

    # Caluculate the Coleman-Liau index
    index = round(.0588 * L - 0.296 * S - 15.8)

    if index >= 16:
        print("Grade 16+")

    elif index < 1:
        print("Before Grade 1")

    else:
        print("Grade {}" .format(index))


# Count the number of letters
def count_letters(text):
    letters = 0
    for i in range(len(text)):
        if str.isalpha(text[i]):
            letters += 1

    return letters


# Count the number of words
def count_words(text):
    words = 1
    for i in range(len(text)):
        if text[i] == " ":
            words += 1

    return words


# Count the number of sentences
def count_sentences(text):
    sentences = 0
    for i in range(len(text)):
        if text[i] == "." or text[i] == "!" or text[i] == "?":
            sentences += 1

    return sentences


if __name__ == "__main__":
    main()
