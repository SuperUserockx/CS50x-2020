// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <stdlib.h>
#include "dictionary.h"
#include <ctype.h>

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;
int sizeD = 0;
// Number of buckets in hash table
const unsigned int N = 1000000;

// Hash table
node *table[N];

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    // TODO
    //char *tmpS = malloc(strlen(word)*sizeof(char));
    //strcpy(tmpS,word);
    int hashD = hash(word);
    node *temp = table[hashD];
    //node *xx = *table;
    //printf("%i\n",strcasecmp("aaa","AAA"));
    while (temp != NULL)
    {
        //printf("\n \n %i \n",strcasecmp(tmpS,temp->word));
        if (strcasecmp(word, temp->word) == 0)
        {
            return true;
        }
        temp = temp->next;
    }
    //free(tmpS);
    return false;
}

// Hashes word to a number

unsigned int hash(const char *word)
{
    unsigned int value = 0;
    value += tolower(word[0]);
    for (int i = 1; i < strlen(word); i++)
    {
        value *= tolower(word[i]);
    }
    return value % N; //N is size of hashtable
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // TODO
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        return false;
    }
    // for (int i = 0; i < N; i++)
    // {
    //     table[i] = malloc(sizeof(node));
    //     if(table[i] == NULL)
    //     {
    //         return false;
    //     }
    // }
    char word[LENGTH + 1];
    while (fscanf(file, "%s", word) != EOF)
    {
        int hCode = hash(word);
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            return false;
        }
        strcpy(n->word, word);
        n->next = NULL;
        node *temp = table[hCode];
        if (table[hCode] == NULL)
        {
            table[hCode] = n;
            sizeD++;
        }
        else
        {
            while (temp->next != NULL)
            {
                temp = temp->next;
            }
            temp -> next = n;
            //free(n);
            sizeD++;
        }
    }
    fclose(file);
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    // printf("%i",sizeD);
    return sizeD;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    // TODO
    //node *temp = NULL;
    for (int i = 0; i < N; i++)
    {
        // while(table[i]->next != NULL)
        // {
        //     temp = table[i] -> next;
        //     free(table[i]);
        // }
        // free(temp);
        while (table[i] != NULL)
        {
            node *temp = table[i];
            table[i] = table[i]->next;
            free(temp);

        }
    }
    return true;
}
