// Implements a dictionary's functionality

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <strings.h>
#include <string.h>
#include <ctype.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 16384;

// Hash table
node *table[N];

int size_of_dictionary = 0;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // Make node cursor pointer
    node *cursor = table[hash(word)];
    while (cursor != NULL)
    {
        // Check the word
        if (strcasecmp(word, cursor->word) == 0)
        {
            return true;
        }

        // Next pointer
        cursor = cursor->next;
    }

    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // Caluculate the key(sum of the ASCII code)
    long int key = 0;
    for (int i = 0; word[i] != '\0'; i++)
    {
        key += tolower(word[i]);
    }

    // Hssh fnction from INTRODUCTION TO ALGORITHMS P218
    const double A = (sqrt(5) - 1) / 2.0;
    long int value = floor(N * (key * A - floor(key * A)));

    return value;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // Open the dictionary file
    FILE *dp = fopen(dictionary, "r");
    // Check if return value is NULL
    if (dp == NULL)
    {
        printf("Can't open the dictionary file\n");
        return false;
    }

    // Make array to store a word
    char new_word[LENGTH + 1];

    // Read words from the dictionary file until EOF
    while (fscanf(dp, "%s", new_word) != EOF)
    {
        // Create a new node
        node *n = malloc(sizeof(node));
        // Check if return value is NULL
        if (n == NULL)
        {
            return false;
        }

        // Copy word into node
        strcpy(n->word, new_word);

        // Insert node into hash table
        n->next = table[hash(new_word)];
        table[hash(new_word)] = n;

        // Count the words
        size_of_dictionary++;
    }

    // Close the dictionary file
    fclose(dp);

    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return size_of_dictionary;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // Make cursor pointer
    node *cursor = NULL;
    // Repeat from table[0] to table[N - 1]
    for (int i = 0; i < N; i++)
    {
        // Assign cursor
        cursor = table[i];

        // Repeat until the end of linked list
        while (cursor != NULL)
        {
            // Make temporarily pointer to free up memory
            node *tmp = cursor;
            // Point next
            cursor = cursor->next;
            // Free up tmp
            free(tmp);
        }

        // Reach the end of linked list in table[N - 1]
        if (cursor == NULL && i == N - 1)
        {
            return true;
        }
    }

    return false;
}
