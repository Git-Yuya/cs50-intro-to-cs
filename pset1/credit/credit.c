#include <stdio.h>
#include <cs50.h>

bool checksum(long n);
void print_card_company(long n);

int main(void)
{
    long card_number;
    do
    {
        card_number = get_long("Number:");
    }
    while (card_number < 0);

    if (checksum(card_number))
    {
        print_card_company(card_number);
    }
    else
    {
        printf("INVALID\n");
    }

}

bool checksum(long n)
{
    int sum = 0;
    for (int i = 0; n != 0; i++, n /= 10)
    {
        if (i % 2 == 0)
        {
            sum += n % 10;
        }

        else
        {
            int digit = n % 10;
            sum += (2 * digit) / 10 + (2 * digit) % 10;
        }
    }

    return (sum % 10) == 0;
}

void print_card_company(long n)
{

    if ((n >= 34e+13 && n < 35e+13) || (n >= 37e+13 && n < 38e+13))
    {
        printf("AMEX\n");
    }

    else if (n >= 51e+14 && n < 56e+14)
    {
        printf("MASTERCARD\n");
    }
    else if ((n >= 4e+12 && n < 5e+12) || (n >= 4e+15 && n < 5e+15))
    {
        printf("VISA\n");
    }

    else
    {
        printf("INVALID\n");
    }
}