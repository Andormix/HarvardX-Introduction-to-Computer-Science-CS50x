// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include "dictionary.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>
#include <strings.h>

// Recount of words loaded.
int words_loaded = 0;

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Choose number of buckets in hash table. (Maximum number of my own hash function - Tradeoff: Memory)
const int  N = 99999999;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // Get the pointer where it should be the word
    node *n = table[hash(word)];

    while (n != NULL)
    {
        if (strcasecmp(word, n->word) == 0)
        {
            return true;
        }

        n = n->next;
    }
    return false;
}

// Hashes word to a number (The hash function you write should ultimately be your own, not one you search for online.)
unsigned int hash(const char *word)
{
    unsigned long long  key = 1;
    int i = 0;

    // Iterates the characters of the array
    while (word[i] != '\0')
    {
        // I will use a simplistic hash key (1/10th colisions) multyply by CS50 ;)
        key = (tolower(word[i]) * key * 50);
        i++;
    }

    return key % 99999999;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // Get file pointer of the dictionary
    FILE *dict_ptr = fopen(dictionary, "r");
    if (dict_ptr == NULL)
    {
        return false;
    }

    // Buffer to store 1 word
    node *new_node = malloc(sizeof(node));
    new_node->next = NULL;

    // Variables to help getting words
    char ch;
    int i = 0;
    int key;

    // Update global
    words_loaded = 0;

    // Iterates every character in the file
    while ((ch = fgetc(dict_ptr)) != EOF)
    {
        // If we get a new line we need to store another word
        if (ch == '\n')
        {
            // End current word
            new_node->word[i] = '\0';

            // Get hash key
            key = hash(new_node->word);

            // Store node in hash table
            if (table[key] == NULL)
            {
                // If hash table position is empty put the nothe in there
                table[key] = new_node;
            }
            else
            {
                // If its not, insert it on the first place
                new_node->next = table[key];
                table[key] = new_node;

            }
            words_loaded++;

            // Allocate memory for new node
            new_node = malloc(sizeof(node));
            new_node->next = NULL;
            i = 0;
        }
        else
        {
            new_node->word[i] = ch;
            i++;
        }
    }

    // Close dictionary pointer
    free(new_node);
    fclose(dict_ptr);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return words_loaded;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{

    node *n = NULL;

    for (int i = 0; i <= N - 1; i++)
    {
        if (table[i] != NULL)
        {
            n = table[i];

            while (n != NULL)
            {
                n = n->next;
                free(table[i]);
                table[i] = n;
            }
        }
    }
    return true;
}

void print_hash_table()
{
    for (int i = 0; i <= N; i++)
    {
        if (table[i] != NULL)
        {
            printf("At index:%i is %s\n", i, table[i]->word);
        }
    }
}