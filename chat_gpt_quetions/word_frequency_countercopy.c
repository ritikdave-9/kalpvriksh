#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 100

typedef struct Node {
    char *key;
    int value;
    struct Node *next;
} Node;

Node *createNode(char *key, int value) {
    Node *newnode = (Node *)malloc(sizeof(Node));
    newnode->key = strdup(key);
    newnode->value = value;
    newnode->next = NULL;
    return newnode;
}

typedef struct HMap {
    Node *table[SIZE];
} HMap;

HMap *createMap() {
    HMap *newmap = (HMap *)malloc(sizeof(HMap));
    for (int i = 0; i < SIZE; i++) {
        newmap->table[i] = NULL;
    }
    return newmap;
}

unsigned int hash(char *key) {
    unsigned int index = 0;
    for (int i = 0; i < strlen(key); i++) {
        index <<= 4;
        index += key[i];
    }
    return index % SIZE;
}

void insert(HMap *hm, char *key, int value) {
    unsigned int index = hash(key);
    Node *current = hm->table[index];
    if (!current) {
        hm->table[index] = createNode(key, value);
        return;
    }

    while (current->next) {
        if (strcmp(current->key, key) == 0) {
            current->value = value;
            return;
        }
        current = current->next;
    }

    if (strcmp(current->key, key) == 0) {
        current->value = value;
    } else {
        current->next = createNode(key, value);
    }
}

int search(HMap *hm, char *key) {
    unsigned int index = hash(key);
    Node *current = hm->table[index];

    while (current) {
        if (strcmp(current->key, key) == 0) {
            return current->value;
        }
        current = current->next;
    }

    return -1;
}

int frequency(char *str, char *word) {
    char temp[50];
    int i = 0;
    HMap *hm = createMap();

    while (*str) {
        if (*str == ' ' || *str == '\n' || *str == '\t') {
            if (i > 0) {
                temp[i] = '\0';
                int n = search(hm, temp);
                if (n == -1) {
                    insert(hm, temp, 1);
                } else {
                    insert(hm, temp, n + 1);
                }
                i = 0; // Reset index for the next word
            }
        } else {
            temp[i] = *str;
            i++;
        }
        str++;
    }

    // Add the last word if there is one
    if (i > 0) {
        temp[i] = '\0';
        int n = search(hm, temp);
        if (n == -1) {
            insert(hm, temp, 1);
        } else {
            insert(hm, temp, n + 1);
        }
    }

    int result = search(hm, word);
    return result == -1 ? 0 : result; // Return 0 if the word is not found
}

int main() {
    char str[100];
    printf("Enter a string: ");
    scanf(" %[^\n]", str);

    printf("Enter the word to find its frequency: ");
    char word[50];
    scanf("%s", word);

    printf("Frequency of '%s': %d\n", word, frequency(str, word));
    return 0;
}
