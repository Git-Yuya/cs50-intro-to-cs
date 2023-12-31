from cs50 import get_int

# Input pyramid height (1 ~ 8)
while True:
    height = get_int("Height: ")
    if height >= 1 and height <= 8:
        break

# Create 2 pyramids
for h in range(height):
    # Create left pyramid
    print(" " * (height - h - 1) + "#" * (h + 1), end="")
    # Insert 2 spaces
    print(" " * 2, end="")
    # Create right pyramid
    print("#" * (h + 1))
