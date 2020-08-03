from cs50 import get_int

while True:
    h = get_int("Height : ")  # Getting user input
    if h in range(1, 9):
        break
for i in range(h):
    for j in range(i, h-1):
        print(" ", end="")  # alignment spaces
    for k in range(i+1):
        print("#", end="")  # Left sige of #
    print("  ", end="")
    for l in range(i+1):
        print("#", end="")  # Right side of #
    print()
