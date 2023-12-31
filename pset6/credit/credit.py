from cs50 import get_string


def main():
    # Input card number from user
    while True:
        card_number = get_string("Number: ")
        if int(card_number) > 0:
            break

    # Check if the card number is valid
    if checksum(card_number) == True:
        print_card_company(card_number)
    else:
        print("INVALID")


# Check if the card number is valid
def checksum(card_number):
    # Find digits
    digits = len(card_number)

    # Convert str into int
    card_number = int(card_number)

    sum = 0
    for i in range(digits):
        # Find the number of digits
        digit = card_number % 10

        if i % 2 == 0:
            sum += digit
        else:
            sum += (digit * 2) // 10 + (digit * 2) % 10

        card_number //= 10

    # Check if the sum is divisible by 10
    if sum % 10 == 0:
        return True
    else:
        return False


def print_card_company(card_number):
    # Find the number of digits
    digits = len(card_number)

    if digits == 15 and (card_number[0:2] == "34" or card_number[0:2] == "37"):
        print("AMEX")
    elif digits == 16 and (card_number[0:2] == "51" or card_number[0:2] == "52" or card_number[0:2] == "53" or card_number[0:2] == "54" or card_number[0:2] == "55"):
        print("MASTERCARD")
    elif (digits == 13 or digits == 16) and card_number[0] == "4":
        print("VISA")
    else:
        print("INVALID")


if __name__ == "__main__":
    main()
