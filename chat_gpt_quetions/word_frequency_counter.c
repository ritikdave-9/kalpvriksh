#include <stdio.h>
#include <stdlib.h>

#include <string.h>
#define size 100

typedef struct Node
{
    char *key;
    int value;
    struct Node *next;

} Node;

Node *createNode(char *key, int value)
{
    Node *newnode = (Node *)malloc(sizeof(Node));
    newnode->key = strdup(key);
    newnode->value = value;
    newnode->next = NULL;
    return newnode;
}

typedef struct HMap
{
    Node *table[size];
} HMap;

HMap *createMap()
{
    HMap *newmap = (HMap *)malloc(sizeof(HMap));
    for (int i = 0; i < size; i++)
    {
        newmap->table[i] = NULL;
    }

    return newmap;
}

unsigned int hash(char *key)
{
    unsigned int index = 0;
    for (int i = 0; i < strlen(key); i++)
    {
        index <<= 4;
        index += key[i];
    }

    return index % size;
}

void insert(HMap *hm, char *key, int value)
{
    unsigned int index = hash(key);

    Node *current = hm->table[index];
    if(!current){
        hm->table[index] = createNode(key,value);
        return;
            }
    Node * prev = NULL;

    while (current)
    {
        if (strcmp(current->key, key) == 0)
        {
            current->value = value;
            return;
        }
        prev = current;
        current = current->next;
    }

    prev->next = createNode(key,value);

}

int search(HMap *hm, char *key)
{
    unsigned int index = hash(key);

    Node *current = hm->table[index];

    while (current)
    {
        if (strcmp(current->key, key) == 0)
        {
            return current->value;
        }
        current = current->next;
        /* code */
    }

    return 0;
}
void printMap(HMap* hm){
    int i = 0;
    while(i<size){

        Node* current = hm->table[i];

        while(current){
            printf("%s : %d\n",current->key,current->value  );
            current = current->next;


        }
        i++;

    }
}

int frequency(char *str, char *word)
{
    char temp[50];

    int i = 0;
    HMap *hm = createMap();

    while (*str)
    {
        if (*str == ' ' || *str == '\n')
        {
            if (i > 0)
            {
                temp[i] = '\0';
                int n = search(hm, temp);


                insert(hm,temp,n+1);
                i = 0;
            }
        }
        else
        {
            temp[i] = *str;
            i++;
        }
        str++;
    }
    if (i > 0)
    {
        temp[i] = '\0';
        int n = search(hm, temp);

        insert(hm,temp,n+1);
       
    }
    printMap(hm);
    return search(hm, word);
}




int main()
{
    HMap *hm = createMap();
    insert(hm, "a", 0);
    insert(hm, "b", 1);
    printf("%d", search(hm, "b"));

    char str[100];
    printf("\n");
    fgets(str,sizeof(str),stdin);
    printf("%d", frequency(str, "is"));
}

