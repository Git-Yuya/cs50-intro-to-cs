from cs50 import get_float

# Input money(>0)
while True:
    dollars = get_float("Change owed: ")
    if dollars > 0:
        break

# Convert dollars into cents
cents = round(dollars * 100)

count_coins = 0
while cents >= 1:
    # The rest of change >= 25
    if cents >= 25:
        count_coins += 1
        cents -= 25

    # 10 <= The rest of change < 25
    elif cents >= 10:
        count_coins += 1
        cents -= 10

    # 5 <= The rest of change < 10
    elif cents >= 5:
        count_coins += 1
        cents -= 5

    # 1 <= The rest of change < 5
    elif cents >= 1:
        count_coins += 1
        cents -= 1

    else:
        count_coins += 0

print(count_coins)
