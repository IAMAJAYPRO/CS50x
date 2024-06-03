// Implements a dictionary's functionality

#include "stdio.h"
#include <ctype.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 46;
int count = 0;
// Hash table
node *table[N] = {NULL};

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    char wordc[LENGTH + 1];
    for (int i = 0; i < LENGTH + 1; i++)
    {
        wordc[i] = tolower(word[i]);
        if (word[i] == '\0')
        {
            break;
        }
    }
    node *tmp = table[hash(wordc)];
    while (tmp != NULL)
    {
        if (strcmp(tmp->word, wordc) == 0)
        {
            return true;
        }
        else
        { // printf("||%s:%s||\n", tmp->word, word);
            tmp = tmp->next;
        }
    } // TODO
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    int ct = 0;
    for (int i = 0; i < LENGTH + 1; i++)
    {
        if (word[i] == '\0')
        {
            break;
        }
        ct++;
    }
    return --ct;
    // return toupper(word[0]) - 'A';
}

// Loads dictionary into memory, returning true if successful, else false
bool insert(const char word[]);

bool load(const char *dictionary)
{
    FILE *file = fopen(dictionary, "r");

    if (file == NULL)
    {
        return false;
    }
    char word[LENGTH + 1];
    char c;

    while (fscanf(file, "%s", word) != EOF)
    {
        if (insert(word) == false)
        {
            return false;
        };
        count++;
    }
    fclose(file);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return count;
}

bool free_ll(node *ll);

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    for (int i = 0; i < N; i++)
    {
        if (table[i] == NULL)
        {
            continue;
        }
        else if (free_ll(table[i]) != true)
        {
            return false;
        };
    }
    return true;
}

bool free_ll(node *ll)
{
    if (ll->next != NULL)
    {
        free_ll(ll->next);
    }
    // ll->next=NULL;
    free(ll);
    return true;
}

bool insert(const char word[])
{
    node *tmp = malloc(sizeof(node));
    if (tmp == NULL)
    {
        return false;
    }
    strcpy(tmp->word, word);
    tmp->next = NULL;
    int hs = hash(word);
    if (table[hs] == NULL)
    {

        table[hs] = tmp;
        return true;
    }
    node *ptr = table[hs];

    while (ptr->next != NULL)
    {
        ptr = ptr->next;
    }
    ptr->next = tmp;
    return true;
}
