/**
 * dictionary.c
 *
 * Computer Science 50
 * Problem Set 5
 *
 * Implements a dictionary's functionality.
 */

#include <stdbool.h>
#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#include "dictionary.h"

#define APOSTROPHE 123 // So that subtracting 'a' will put apostrophes in 26th array position
node* root;
unsigned int counter;

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char* word)
{
    node* trav = root;
    for (int i = 0, length = strlen(word); i < length; i++)
    {
        int index;
        char c = tolower(word[i]);
        
        if(c == '\'')
        {
            c = APOSTROPHE;
        }
        index = ((int) c) - 'a';
        
        if(trav->children[index] == NULL)
        {
            return false;
        }
        else
        {
            trav = trav->children[index];
        }
    }
    return (trav->is_word == true) ? true : false; // Maybe can just return trav->is_word ?
}

/**
 * Loads dictionary into memory.  Returns true if successful else false.
 */
bool load(const char* dictionary)
{
    FILE* fp = fopen(dictionary, "r");
    if(fp == NULL)
    {
        return false;
    }
    
    root = (node*) malloc(sizeof(node));
    node* trav = root;

    for (char c = fgetc(fp); c != EOF; c = fgetc(fp))
    {
        if(c == '\n')
        {
            trav->is_word = true;
            counter++;
            trav = root;
        }
        else
        {
            if(c == '\'')
            {
                c = APOSTROPHE;
            }
            int index = ((int) c) - 'a';
            if(trav->children[index] == NULL)
            {
                trav->children[index] = (node*) malloc(sizeof(node));
            }
            trav = trav->children[index];
        }
    }
    fclose(fp);
    return true;
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    if(root == NULL)
    {
        return 0;
    }
    return counter;
}

/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
bool unload(void)
{
    return trieUnload(root);
}

bool trieUnload(node* node)
{
    for(int i = 0; i < 27; i++)
    {
        if(node->children[i] != NULL)
        {
            trieUnload(node->children[i]);
        }
    }
    if(node != NULL)
    {
        free(node);
    }
    return true;
}