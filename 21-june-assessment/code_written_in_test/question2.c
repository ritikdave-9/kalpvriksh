#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define size 100

typedef struct node{
    char*data;
    struct node* next;
}node;

node* createNode(char* str){
    node* newnode = (node*)malloc(sizeof(node));
    
    newnode->data = strdup(str);

    newnode->next = NULL;
    return newnode;

}

node* createList(){
    node* head = NULL;
    node* temp = NULL;

    while(1){
        char str[20];
        scanf("%s",str);

        if(strcmp(str,"end")==0){
            break;
        }
        node* current = createNode(str);

        if(!head){
            head = current;
            temp = current;
        }
        else{
            temp->next = current;
            temp = temp->next;
        }

    }

    return head;
}

void printList(node* head){
    node* temp = head;

    while (temp){
        printf("%s->",temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
    
}

typedef struct hnode
{
    char * key;
    int value;
    struct hnode* next;
    
}hnode;

hnode* createHnode(char* key, int value){
    hnode* new = (hnode*)malloc(sizeof(hnode));
    new->key = strdup(key);
    new->value = value;
    new->next = NULL;

    return new;

}

typedef struct htable{
    hnode* table[size];
}htable;

htable* createHtable(){
    htable* new = (htable*)malloc(sizeof(htable));
    for(int i = 0;i<size;i++){
        new->table[i] = NULL;
    }

    return new;
}

int hash(char* key){
    char * temp = key;

    int index = 0;

    while (*temp!='\0'){

        index = index + *temp;
        temp++;

    }

    return index%size;
    
    
}

void insert(htable* table,char * key , int value){
    int index = hash(key);

    hnode* current = table->table[index];

    if(!current){
        table->table[index] = createHnode(key, value);
        return;
    }

    hnode* prev = NULL;

    while (current)
    {
        if(strcmp(current->key,key)==0){
            current->value = value;
            return ;
        }

        prev = current;
        current = current->next;

        
    }

    prev->next = createHnode(key, value);

    


}

int get(htable* table , char* key){
    int index = hash(key);

    hnode* current = table->table[index];
    while (current)
    {
        if(strcmp(current->key,key)==0){
            return current->value;
        }
        current = current->next;
    }

    return -1;
    
}

void freeTable(htable* table){
    for(int i = 0;i<size;i++){
        free(table->table[i]->key);
        free(table->table[i]);
    }
}

void deleteDuplicateFiles(node* head){
    htable* table = createHtable();
    node* current = head;
    node* prev = NULL;
    node* next = NULL;
    while (current)
    {
        if(get(table,current->data)==-1){

            insert(table,current->data,1);
            prev = current;
            current = current->next;

           
        }
        else{
            next = current->next;
            node* temp = current;
            prev->next = current->next;
            free(temp);

            current = next;

        }
        
    }

    free(table);

    

}




int main(){

    printf("Enter the name of files and to stop enter \"end\":\n");
    node* head = createList();


    printf("files before deletion :\n");
    printList(head);
    printf("files after deletion :\n");

    deleteDuplicateFiles(head);

    printList(head);
}