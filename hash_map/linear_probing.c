#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

#define size 100

#define DELETED (Node *)(-1)

typedef struct Node
{
    char *key;
    int value;
} Node;

typedef struct HashMap
{
    Node *table[size];
    int total_filled;
} HashMap;

Node *createNode(char *key, int value)
{
    Node *newnode = (Node *)malloc(sizeof(Node));
    newnode->key = strdup(key);
    newnode->value = value;
    return newnode;
}

HashMap *createMap()
{
    HashMap *hm = (HashMap *)malloc(sizeof(HashMap));
    for (int i = 0; i < size; i++)
    {
        hm->table[i] = NULL;
    }
    hm->total_filled = 0;
    return hm;
}

unsigned int hash1(char *key)
{
    unsigned int index = 0;
    for (int i = 0; i < strlen(key); i++)
    {
        index = (index << 5) + key[i];
    }
    return index % size;
}

unsigned int hash2(unsigned int h1)
{
    h1 = (h1 << 6);
    return h1 % size;
}

void insertLinearProbing(HashMap *hm, char *key, int val)
{
    unsigned int index = hash1(key);

    if (hm->total_filled == size)
    {
        printf("table full");
        return;
    }

    while (hm->table[index] != NULL && hm->table[index] != DELETED)
    {
        if (strcmp(hm->table[index]->key, key) == 0)
        {
            hm->table[index]->value = val;
            return;
        }

        index = (index + 1) % size;
    }

    hm->table[index] = createNode(strdup(key), val);
    hm->total_filled++;
}

void delete_linear_probing(HashMap *hm, char *key)
{
    unsigned int index = hash1(key);
    while (hm->table[index])
    {
        if (hm->table[index] != DELETED && strcmp(hm->table[index]->key, key) == 0)
        {
            free(hm->table[index]->key);
            free(hm->table[index]);
            hm->table[index] = DELETED;
            printf("\ndeleted\n");
            hm->total_filled--;
            return;
        }
        index = (index + 1) % size;
    }
    printf("\nnot found key\n");
    return;
}

int search_linear_probing(HashMap *hm, char *key)
{
    unsigned int index = hash1(key);
    while (hm->table[index])
    {
        if (hm->table[index] != DELETED && strcmp(hm->table[index]->key, key) == 0)
        {
            return hm->table[index]->value;
        }
        index = (index + 1) % size;
    }
    return -1;
}

void printTable(HashMap *hm)
{
    for (int i = 0; i < size; i++)
    {
        if (hm->table[i] != NULL && hm->table[i] != DELETED)
        {
            printf("%s : %d\n", hm->table[i]->key, hm->table[i]->value);
        }
    }
}

int main()
{
    HashMap *hm = createMap();

    char *key1 = "key1";
    int val1 = 10;
    insertLinearProbing(hm, key1, val1);
    printf("Inserted value: %d\n", hm->table[hash1(key1)]->value);
    printf("Search value: %d\n", search_linear_probing(hm, key1));

    char *key2 = "key2";
    int val2 = 20;
    insertLinearProbing(hm, key2, val2);
    printf("Inserted value (key2): %d\n", search_linear_probing(hm, key2));

    int newVal1 = 30;
    insertLinearProbing(hm, key1, newVal1);
    printf("Updated value (key1): %d\n", search_linear_probing(hm, key1));

    char *key3 = "key3";
    delete_linear_probing(hm, key3);

    delete_linear_probing(hm, key1);
    printf("Search after delete (key1): %d\n", search_linear_probing(hm, key1));
    printf("Search after delete (key3): %d\n", search_linear_probing(hm, key3));

    printTable(hm);

    printf("Table full test completed.\n");

    return 0;
}
