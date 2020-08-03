from cs50 import get_string


def main():  # MAIN function
    s = get_string("Text : ")
    letters = count_letters(s)  # calls the function to count letters
    words = count_words(s)  # calls the function to count words
    sentences = count_sentences(s)  # Calls the function to count sentences
    w = 100/words
    L = letters * w
    S = sentences / words
    S *= 100
    I = 0.0588 * L - 0.296 * S - 15.8  # The Coleman-Liau index formula
    I = round(I)
    if I < 1:  # Print segment
        print("Before Grade 1")
    elif I >= 1 and I <= 16:
        print(f"Grade {I}")
    else:
        print("Grade 16+")


def count_letters(s):   # Function to count letters
    letters = 0
    for i in s:
        if 'a' <= i and i <= 'z':
            letters += 1
        if 'A' <= i and i <= 'Z':
            letters += 1
    return letters
    

def count_words(s):  # function to count words
    # words = 1
    # for i in s:
    #     if s[i] == ' '
    #         words += 1

    return len(s.split())


def count_sentences(s):  # function to count words
    sentences = 0
    for i in s:
        if i == '.' or i == '!' or i == '?':
            sentences += 1
    return sentences
    

main()