#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("Error\n");
        return 1;
    }
    for (int i = 0; argv[1][i] != '\0'; i++)
    {
        if (isdigit(argv[1][i]) == false)
        {
            printf("Usage: ./caesar key\n");
            return 1;
        }
    }

    int key = atoi(argv[1]);

    // get text from user
    string text = get_string("plaintext: ");

    // print shifted text
    printf("ciphertext: ");
    for (int i = 0, len = strlen(text); i < len; i++)
    {
        if (isupper(text[i]))
        {
            printf("%c", (text[i] - 'A' + key) % 26 + 'A');
        }
        else if (islower(text[i]))
        {
            printf("%c", (text[i] - 'a' + key) % 26 + 'a');
        }
        else
        {
            printf("%c", text[i]);
        }
    }
    putchar('\n');

    return 0;
}

