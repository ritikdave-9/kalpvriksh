#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define size 5

#define DELETED (Node *)(-1)

typedef struct Node {
    char *key;
    int value;
} Node;

typedef struct HashMap {
    Node *table[size];
    int total_filled;
} HashMap;

Node *createNode(char *key, int value) {
    Node *newnode = (Node *)malloc(sizeof(Node));
    newnode->key = strdup(key);
    newnode->value = value;
    return newnode;
}

HashMap *createMap() {
    HashMap *hm = (HashMap *)malloc(sizeof(HashMap));
    for (int i = 0; i < size; i++) {
        hm->table[i] = NULL;
    }
    hm->total_filled = 0;
    return hm;
}

unsigned int hash1(char *key) {
    unsigned int index = 0;
    for (int i = 0; i < strlen(key); i++) {
        index = (index << 5) + key[i];
    }
    return index % size;
}

void insertLinearProbing(HashMap *hm, char *key, int val) {
    unsigned int index = hash1(key);
    while (hm->table[index] != NULL) {
        index = (index + 1) % size;
    }
    hm->table[index] = createNode(strdup(key), val);
    hm->total_filled++;
}

void delete_linear_probing(HashMap *hm, char *key) {
    unsigned int index = hash1(key);
    while (hm->table[index]) {
        if (strcmp(hm->table[index]->key, key) == 0) {
            free(hm->table[index]->key);
            free(hm->table[index]);
            hm->table[index] = DELETED;
            printf("\nDeleted key: %s\n", key);
            hm->total_filled--;
            return;
        }
        index = (index + 1) % size;
    }
    printf("\nKey not found: %s\n", key);
}

int search_linear_probing(HashMap *hm, char *key) {
    unsigned int index = hash1(key);
    while (hm->table[index]) {
        if (hm->table[index] != DELETED && strcmp(hm->table[index]->key, key) == 0) {
            return hm->table[index]->value;
        }
        index = (index + 1) % size;
    }
    return -1;
}

void printTable(HashMap *hm) {
    for (int i = 0; i < size; i++) {
        if (hm->table[i] != NULL && hm->table[i] != DELETED) {
            printf("%s : %d\n", hm->table[i]->key, hm->table[i]->value);
        }
    }
}

int main() {
    HashMap *hm = createMap();

    insertLinearProbing(hm, "key1", 10);
    insertLinearProbing(hm, "key2", 20);
    insertLinearProbing(hm, "key3", 30);

    delete_linear_probing(hm, "key2");

    printf("\nSearching for key 'key3'...\n");
    int result = search_linear_probing(hm, "key3");
    if (result != -1) {
        printf("Value found: %d\n", result);
    } else {
        printf("Key not found!\n");
    }

    printf("\nSearching for key 'key2'...\n");
    result = search_linear_probing(hm, "key2");
    if (result != -1) {
        printf("Value found: %d\n", result);
    } else {
        printf("Key not found!\n");
    }

    printf("\nHashMap Contents:\n");
    printTable(hm);

    return 0;
}
