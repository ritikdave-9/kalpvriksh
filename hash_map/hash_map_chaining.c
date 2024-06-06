#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <limits.h>

#define size 100
typedef struct Node
{
    char *key;
    int value;
    struct Node *next;

} Node;

typedef struct HashMap
{
    Node *table[size];
} HashMap;

Node *createNode(char *key, int value)
{
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->key = strdup(key);
    newNode->value = value;
    newNode->next = NULL;

    return newNode;
}

HashMap *createHashMap()
{
    HashMap *newmap = (HashMap *)malloc(sizeof(HashMap));
    for (int i = 0; i < size; i++)
    {
        newmap->table[i] = NULL;
    }

    return newmap;
}

unsigned int hash(char *key)
{
    unsigned int index = 0;

    char *str = key;

    for (int i = 0; i < strlen(key) && index < ULONG_MAX; i++)
    {
        index <<= 4;
        index += key[i];
    }

    return index % size;
}

void insert_hash_map(HashMap *hm, char *key, int value)
{
    unsigned int index = hash(key);

    Node *current = hm->table[index];
    if (!hm->table[index])
    {
        hm->table[index] = createNode(key, value);
        return;
    }

    while (current->next)
    {
        if (strcmp(current->key, key) == 0)
        {
            current->value = value;
            return;
        }
        current = current->next;
    }
    if (strcmp(current->key, key) == 0)
    {
        current->value = value;
        return;
    }
    current->next = createNode(key, value);
}

int search_in_hash_map(HashMap *hm, char *key)
{

    unsigned int index = hash(key);
    Node *current = hm->table[index];
    if (!current)
    {
        return -1;
    }

    while (current)
    {
        if (strcmp(current->key, key) == 0)
        {
            return current->value;
        }
        current = current->next;
    }
    return -1;
}

void delete_in_hash_map(HashMap *hm, char *key)
{
    unsigned int index = hash(key);
    Node *current = hm->table[index];

    
    Node *prev = NULL;

    while (current&&strcmp(current->key,key))
    {

        
        prev = current;
        current = current->next;
    }
    if(!current){
        printf("key not found");
        return;
    }
    if(!prev){
        hm->table[index] = current->next;

    }
    else{
        prev->next = current->next;
    }
    free(current->key);
    free(current);
    printf("\n deleted key \n");
}

int main()
{
    Node *node = createNode("key1", 1);
    // printf("%s",node->key);
    HashMap *hm = createHashMap();

    printf("%lu", strlen(node->key));

    unsigned int index = hash(node->key);
    printf("%d", index);



    insert_hash_map(hm,node->key,10);
    int x = search_in_hash_map(hm,node->key);

    delete_in_hash_map(hm,node->key);
    x = search_in_hash_map(hm,node->key);

    printf("%d",x);
}
