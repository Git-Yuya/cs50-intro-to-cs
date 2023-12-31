#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>
#include <cs50.h>

bool alphabet_is_unique(string alpha);


int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
    for (int i = 0, len = strlen(argv[1]); i < len; i++)
    {
        if (len != 26)
        {
            printf("Key must contain 26 characters.\n");
            return 1;
        }
        else if (isalpha(argv[1][i]) == false)
        {
            printf("Key must only contain alphabetic characters.\n");
            return 1;
        }
        else if (alphabet_is_unique(argv[1]) == false)
        {
            printf("Key must not contain repeated characters.\n");
            return 1;
        }
    }

    // text from user
    string text = get_string("plaintext: ");

    // convert to uppercase
    string key = argv[1];
    for (int i = 0, len = strlen(key); i < len; i++)
    {
        key[i] = toupper(key[i]);
    }

    // print ciphertext
    printf("ciphertext: ");
    for (int i = 0, len = strlen(text); i < len; i++)
    {
        if (isupper(text[i]))
        {
            printf("%c", key[text[i] - 'A']);
        }
        else if (islower(text[i]))
        {
            printf("%c", tolower(key[text[i] - 'a']));
        }
        else
        {
            printf("%c", text[i]);
        }
    }
    putchar('\n');

    return 0;
}


bool alphabet_is_unique(string alpha)
{
    for (int i = 0, len = strlen(alpha); i < len; i++)
    {
        for (int j = i + 1; j < len; j++)
        {
            if (alpha[i] == alpha[j])
            {
                return false;
            }
        }
    }

    return true;
}