from cs50 import get_int

# Input pyramid height (1 ~ 8)
while True:
    height = get_int("Height: ")
    if height >= 1 and height <= 8:
        break

# Create pyramid
for h in range(height):
    print(" " * (height - h - 1) + "#" * (h + 1))
