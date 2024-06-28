#include <stdio.h>
#include <stdlib.h>

#include <string.h>

typedef struct node {
  char *data;
  struct node *next;
} node;

node *createNode(char *str) {
  node *newnode = (node *)malloc(sizeof(node));
  newnode->data = strdup(str);

  newnode->next = NULL;

  return newnode;
}

node *createList() {
  node *head = NULL;
  node *current = NULL;

  while (1) {

    char str[20];

    scanf("%s", str);

    if (strcmp(str, "stop") == 0) {
      break;
    }

    node *newnode = createNode(str);

    if (!head) {
      head = newnode;
      current = newnode;
    } else {
      current->next = newnode;
      current = newnode;
    }
  }

  return head;
}

void printList(node *head) {
  node *current = head;

  printf("\n");
  while (current) {
    printf("%s -> ", current->data);
    current = current->next;
  }
  printf("NULL\n");
}

typedef struct hashNode {
  char *key;
  char ** values;
  int index;
  struct hashNode *next;

} hashNode;

typedef struct hashTable {
  hashNode **table;
  int size;
} hashTable;

hashNode *createHashNode(char *key) {
  hashNode *newnode = (hashNode *)malloc(sizeof(hashNode));
  newnode->values = (char **)calloc(20,sizeof(char*));

  newnode->key = strdup(key);
  newnode->index = -1;
  newnode->next = NULL;
  return newnode;
}

void insertHashNode(hashNode* hnode,char * str){
  hnode->index++;
  hnode->values[hnode->index] = strdup(str);

}

hashTable *createHashTable(int size) {
  hashTable *newtable = (hashTable *)malloc(sizeof(hashTable));
  newtable->table = (hashNode **)calloc(size, sizeof(hashNode *));

  newtable->size = size;
  return newtable;
}

void swap(char *a, char *b) {
  char temp = *a;
  *a = *b;
  *b = temp;
}

char *sortedString(char *str) {
  char *key = strdup(str);
  int n = strlen(str);
  for (int i = 0; i < n - 1; i++) {
    for (int j = 0; j < n - 1; j++) {
      if (key[j] > key[j + 1]) {
        swap(key + j, key + j + 1);
      }
    }
  }

  return key;
}

int hash(char *key, int size) {

  int index = 0;
  int n = strlen(key);

  for (int i = 0; i < n; i++) {
    index += key[i];
  }

  return index % size;
}

void insertHashTable(hashTable *table, char *data) {
  char * key = sortedString(data);

  
  int index = hash(key, table->size);
  hashNode *current = table->table[index];
  if (!current) {

    hashNode * newnode = createHashNode(key);
    insertHashNode(newnode,data);
    table->table[index] = newnode;
    return;
  }
  hashNode * prev = NULL;

  while (current) {
    if(strcmp(current->key, key)==0){
      insertHashNode(current, data);
      return ;
    }

    prev = current;
    current= current->next;
  
  }

  prev->next = createHashNode(key);
  insertHashNode(prev->next, data);


}

void printTable(hashTable* table){
  for(int i = 0;i<table->size;i++){
    hashNode* current = table->table[i];
    while (current) {

      for(int i = 0;i<=current->index;i++){
        printf("%s, ",current->values[i]);

      }

      printf("\n");
    
    current = current->next;
    }

  }
}

int main() {
char *array[] = {
    "listen", "silent", "tac", "inlets", "google", "gogole", 
    "evil", "vile", "veil", "live", "fluster", "restful", 
    "race", "care", "acre", "bored", "robed", "god", "dog", 
    "cat", "act", "brag", "grab", "rat", "tar", "art",
    "elvis", "lives", "veils", "levis", "stone", "notes", "tones"
};

hashTable* table = createHashTable(100);


for(int i = 0;i<33;i++){
  insertHashTable(table, array[i]);

}

printTable(table);


  
}