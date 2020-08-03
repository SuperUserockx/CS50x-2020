from cs50 import get_int


card = get_int("Number : ")
card_bac = card
odd = 0
even = 0
flag = False
if card in range(0, 1000000000000):
    print("INVALID")
    exit(1)
else:
    while card != 0:
        if flag is False:
            odd += card % 10
            card = int(card / 10)
            flag = True
        else:
            s = card % 10
            s *= 2
            while s != 0:
                even += s % 10
                s = int(s / 10)
            card = int(card / 10)
            flag = False

    sum = odd + even
    if sum % 10 is 0:
        while card_bac > 100:
            card_bac = int(card_bac / 10)
        if card_bac == 34 or card_bac == 37:
            print("AMEX")   # Check or AMEX card
            exit()
        elif card_bac in range(51, 56):
            print("MASTERCARD")  # Check for MASTERCARD
            exit()
        else:
            card_bac = int(card_bac / 10)
            if card_bac is 4:
                print("VISA")   # Check for VISA
                exit()
            else:
                print("INVALID")  # If invalid
                exit(1)
    else:
        print("INVALID")    # If invalid
        exit(1)
