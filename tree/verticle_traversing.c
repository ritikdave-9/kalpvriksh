#include <stdio.h>
#include<stdlib.h>
#include <time.h>

#define size 100

typedef struct treeNode{
    int data;
    struct treeNode *left;
    struct treeNode * right;
    
}treeNode;

treeNode* createTreeNode(int data){
    treeNode* newNode = (treeNode*)malloc(sizeof(treeNode));

    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

typedef struct pair{
    int data;
    treeNode* node;
}pair;

pair* createPair(int data , treeNode* node){
    pair* newpair = (pair*)malloc(sizeof(pair));
    newpair->data = data;
    newpair->node = node;
    return newpair;
}



typedef struct node{
    pair* data;
    struct node* next;
}node;

node* createNode(pair* data){
    node* newnode = (node*)malloc(sizeof(node));
    newnode->data = data;
    newnode->next = NULL;
    return newnode;
}

typedef struct Queue{
    node* front;
    node* end;

}Queue;

Queue* createQueue(){
    Queue* q = (Queue*)malloc(sizeof(Queue));
    q->end = NULL;
    q->front = NULL;
    return q;
}

void enQueue(Queue*q,pair* data){
    node* newnode = createNode(data);
    if(q->front==NULL){
        q->front = newnode;
        q->end = newnode;
        return ;

    }
    q->end = newnode;
    return ;
    
}

pair* dqueue(Queue* q){
    if(q->front==NULL){
        return NULL;
    }

    node* newnode = q->front;
    pair* data = newnode->data;
    q->front = newnode->next;
    free(newnode);
    return  data;
    
    
}

pair* queuetop(Queue*q){
    return q->front->data;
}


typedef struct hashNode{
    int key;
    node* value;
    struct hashNode* next;
    
}hashNode ;

hashNode* createHashNode(int key , node* value){
    hashNode* new = (hashNode*)malloc(sizeof(hashNode));
    new->key = key;
    new->value = value;
    new->next = NULL;
    return new;
}



typedef struct Htable{
    hashNode* table[size];
}Htable ;

Htable * createTable(){
    Htable* new = (Htable*)malloc(sizeof(Htable));
    for(int i = 0;i<size;i++){
        new->table[i] = NULL;
    }

    return new;
}

int hash(int key){
    if(key<0){
        return (size + key)%size;
    }
    else{
        return key%size;
    }
}

void insert_in_table(Htable* table,int key , node* value){
    int index= hash(key);

    hashNode* current = table->table[index];


    if(!current){
        table->table[index] = createHashNode(key,value);

        return ;

    }

    while (current->next) {
        if(current->key==key){
            current->value = value;
            return;
        }
        current = current->next;

    
    }

    current->next = createHashNode(key, value);

}

node* get_hash_table(Htable* table , int key){
    int index  = hash(key);

    hashNode* current = table->table[index];

    while (current) {
        if(current->key== key){
            return current->value;
        }
        current = current->next;
    
    }
    return  NULL;
}

void levelOrder(treeNode* root,Queue* q, int level, Htable* table){
    if(!root){
        return;
    }


    if(root->left){
        enQueue(q,createPair(level-1,root->left));
        levelOrder(root->left, q,level-1,table);
    }

    if(root->right){
        enQueue(q,createPair(level-1,root->right));
                levelOrder(root->left, q,level-1,table);

    }

    table->table[hash(dqueue(q)->data)] = createHashNode(dqueue(q)->data,createNode(createPair(level-1, root)));

    
}


int * verticleOrder(treeNode*root){

    Queue* q = createQueue();
    Htable* table = createTable();
    levelOrder(root,q , 0, table);

    





    





}



int main(){
    // Create ss
}

