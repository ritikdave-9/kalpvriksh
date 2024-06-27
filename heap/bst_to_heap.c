#include <stdio.h>

#include <stdlib.h>

typedef struct node{
    int data;
    struct node* left;
    struct node* right;

}node;

typedef struct qnode{
    node* data;
    struct qnode* next;
    
}qnode ;

typedef struct queue{
    qnode* first;
    qnode* last;

}queue;

node* createNode(int data){
    node* newnode = (node*)malloc(sizeof(node));
    newnode->data = data;
    newnode->left = NULL;
    newnode->right = NULL;
    return newnode;
}

qnode* createqnode(node* data){
    qnode* newqnode = (qnode*)malloc(sizeof(qnode));
    newqnode->data = data;
    newqnode->next = NULL;
    return newqnode;
}

queue* createQueue(){
    queue*newqueue =  (queue*)malloc(sizeof(queue));
    newqueue->first = NULL;
    newqueue->last = NULL;

    return newqueue;
}

void enQueue(queue* q,node* data){
    qnode* newQnode = createqnode(data);

    if(!q->first){
        q->first = newQnode;
        q->last = newQnode;
    }
    else{
        q->last->next = newQnode;
        q->last = q->last->next;
    }

}
node* deQueue(queue* q){
    node* temp = q->first->data;
    qnode* current = q->first;
    q->first = q->first->next;
    free(current);
    return temp;
}
node* topQueue(queue* q){
    return q->first->data;
}

node* insertBst(node* root,int data){

    if(!root){
        return createNode(data);
    }

    if(data<root->data){
        root->left = insertBst(root->left,  data);
    }
    if(data>root->data){
        root->right = insertBst(root->right, data);
    }

    return root;
    

}

node* createBst(){
    node* root = NULL;

    while(1){
        int n;
        scanf("%d",&n);
        if(n==-1){
            return root;
                }
        root = insertBst(root, n);

    }
    return root;
}

void inorder(node* root){
    if(!root){
        return;
    }

    inorder(root->left);
    printf("%d, ",root->data);
    inorder(root->right);
}


void bst_to_heap_Utils(node* root,queue*q,node**heaproot){
    if(!root){
        return;
    }
    node* temp = root->left;

    bst_to_heap_Utils(root->right, q, heaproot);

    root->left = NULL;
    root->right = NULL;

    if(!*heaproot){
        enQueue(q, root);
        *heaproot = root;
    }

    else if(!topQueue(q)->left){
        topQueue(q)->left = root;
        enQueue(q, root);
        
    }
    else if(!topQueue(q)->right){
        enQueue(q   ,root);
        topQueue(q)->right = root;
        deQueue(q);
        
    
    }

    bst_to_heap_Utils(temp, q, heaproot);



}



node* bst_to_heap(node* root){
    node* newhroot = NULL;
    queue* q = createQueue();

    bst_to_heap_Utils(root, q, &newhroot);

    return newhroot;



}

void printQueue(queue*q){
    qnode* current = q->first;
        printf("\n");

    while (current) {

        printf("%d -> ",current->data->data);
        current = current->next;
    
    }

    printf("\n");
}

void levelorder(node* root){
    queue* q = createQueue();

    enQueue(q, root);

    while (q->first) {
        if(topQueue(q)->left){
        
        enQueue(q,topQueue(q)->left);}

        if(topQueue(q)->right){
        enQueue(q, topQueue(q)->right);
        }

        printf("%d, ",topQueue(q)->data);
        deQueue(q);
    
    }

}

int main(){
    queue*q = createQueue();
    node* root = createBst();
    levelorder(root);

    printf("\n");


    node* heap = bst_to_heap(root);

    printf("\n");

    levelorder(heap);
    }

