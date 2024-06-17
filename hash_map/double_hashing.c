#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#include <string.h>

#define DELETED (Node *)(-1)


#define size 100
typedef struct Node
{
    char *key;
    int value;
} Node;

typedef struct HashMap
{
    Node *table[size];
    int totalElements;
} HashMap;

Node *createNode(char *key, int value)
{
    Node *newnode = (Node *)malloc(sizeof(Node));
    newnode->key = strdup(key);
    newnode->value = value;
    return newnode;
}

HashMap *createHashMap()
{
    HashMap *newmap = (HashMap *)malloc(sizeof(HashMap));
    for (int i = 0; i < size; i++)
    {
        newmap->table[i] = NULL;
    }

    newmap->totalElements = 0;
}

unsigned int hash1(char *key)
{
    unsigned int index = 0;

    for (int i = 0; i < strlen(key); i++)
    {
        index <<= 8;
        index += key[i];
    }

    return index % size;
}

unsigned int hash2(unsigned int key)
{
    key <<= 6;

    return key % size;
}

void insert_in_hash_map(HashMap *hm, char *key, int value)
{

    unsigned int index = hash1(key);

    if (hm->totalElements == size)
    {
        printf("table is full");
        return;
    }

    while (hm->table[index] != NULL||hm->table[index]!=DELETED)
    {
        if (strcmp(hm->table[index]->key, key) == 0)
        {
            hm->table[index]->value = value;
            return;
        }
        index = (hash2(index)) % size;
    }

    hm->table[index] = createNode(key, value);
        hm->totalElements++;

}

void printTable(HashMap*hm){
    for(int i = 0;i<size;i++){
        if(hm->table[i]!=NULL){
            printf("%s : %d\n",hm->table[i]->key,hm->table[i]->value);
        }
    }
}

int search_hash_table(HashMap*hm,char*key){
    unsigned int index = hash1(key);
    while(hm->table[index]!=NULL){
        if(strcmp(hm->table[index]->key,key)==0){
            return hm->table[index]->value;

        }
        index = hash2(index)%size;
    }

    return -1;

    
    
}


void delete_in_hash_map(HashMap*hm,char*key){


}



int main() {
    HashMap *hm = createHashMap();

    
    char* key1 = "key1";
    int val1 = 10;
    insert_in_hash_map(hm, key1, val1);

    printTable(hm);
    printf("%d",search_hash_table(hm,key1));
    // printf("Search value: %d\n", search_linear_probing(hm, key1));

    
    // char* key2 = "key2"; 
    // int val2 = 20;
    // insertLinearProbing(hm, key2, val2);
    // printf("Inserted value (key2): %d\n", search_linear_probing(hm, key2));

    
    // int newVal1 = 30;
    // insertLinearProbing(hm, key1, newVal1);
    // printf("Updated value (key1): %d\n", search_linear_probing(hm, key1));

    
    // char* key3 = "key3"; 
    // delete_linear_probing(hm, key3);

    
    // // delete_linear_probing(hm, key1);
    // printf("Search after delete (key1): %d\n", search_linear_probing(hm, key1));
    // printf("Search after delete (key3): %d\n", search_linear_probing(hm, key3));

    // printTable(hm);

    
    
    // printf("Table full test completed.\n");

    
    

    return 0;
}


