#include <linux/limits.h>
#include <stdio.h>

#include <stdlib.h>
#include <sys/types.h>

typedef struct tnode {
  int data;
  struct tnode *left;
  struct tnode *right;
  

} tnode;

typedef struct Qnode {
  tnode *data;
  struct Qnode *next;
  

} Qnode;

Qnode *createQnode(tnode *data) {
  Qnode *new = (Qnode *)malloc(sizeof(Qnode));
  new->data = data;
  new->next = NULL;
  return new;
}

tnode *createTnode(int data) {
  tnode *new = (tnode *)malloc(sizeof(tnode));
  new->data = data;
  new->left = NULL;
  new->right = NULL;
  return new;
}

typedef struct Queue {
  Qnode *top;
  Qnode *bottom;

} Queue;

Queue *createQueue() {
  Queue *new = (Queue *)malloc(sizeof(Queue));
  new->top = NULL;
  new->bottom = NULL;
  return new;
}

void enqueue(Queue *q, tnode *data) {

  if (!q->top) {
    q->top = createQnode(data);
    q->bottom = q->top;

  } else {
    q->bottom->next = createQnode(data);
    q->bottom = q->bottom->next;
  }
}

tnode *dequeue(Queue *q) {
  tnode *temp = q->top->data;

  Qnode *qtemp = q->top;

  q->top = q->top->next;

  free(qtemp);
  return temp;
}

tnode *topQueue(Queue *q) { return q->top->data; }

void levelOrderUtils(Queue *q, int *arr, int index) {
  if (q->top == NULL) {
    return;
  }
  arr[index] = topQueue(q)->data;
  if (topQueue(q)->left) {
    enqueue(q, topQueue(q)->left);
  }
  if (topQueue(q)->right) {
    enqueue(q, topQueue(q)->right);
  }

  dequeue(q);
  levelOrderUtils(q, arr, index+1);
}

int *levelorder(tnode *root) {

  int *arr = (int *)calloc(100, sizeof(int));
  int index = 0;

  Queue *q = createQueue();
  enqueue(q, root);

  levelOrderUtils(q, arr, index);

  return arr;
}

void preorder(tnode* root){
    if(!root){
        return;
    }

    printf("%d, ",root->data);
    preorder(root->left);
    preorder(root->right);
}

void hdleft(tnode* root, int *left, int current){
    if(!root){
        return ;
    }

    if(current<(*left)){
        *left = current;
    }

    hdleft(root->left, left, current-1);
    hdleft(root->right, left, current+1);
    
}
void hdright(tnode* root, int *right, int current){
    if(!root){
        return ;
    }

    if(current>(*right)){
        *right = current;
    }

    hdright(root->left, right, current-1);
    hdright(root->right, right, current+1);
    
}

typedef struct pair{
    int data;
    int level;
}pair;

pair* createpair(int data, int level){
    pair* new = (pair*)malloc(sizeof(pair));
    new->data = data;
    new->level = level;
    return new;
}

void topViewUtils(tnode* root , pair* arr, int level , int hd, int left){

    if(!root){
        return;
    }

    if(arr[hd-left].level>level){
        arr[hd-left] = *(createpair(root->data  ,  level));
    }
    
    
    topViewUtils(root->left, arr, level+1, hd-1,left);
    
    topViewUtils(root->right, arr, level+1, hd+1,left);


    
}



void top_view(tnode* root){

    int left= 0;
    int right = 0;
    hdleft(root, &left, 0);
    hdright(root, &right, 0);
    // printf("%d",right-left+1);

    pair * arr = (pair *)calloc(right-left +1, sizeof(pair));

    for(int i = 0;i<right-left+1;i++){
        arr[i].level = 1e9;
    }

topViewUtils(root, arr, 0, 0, left);
for(int i = 0;i<right-left+1;i++){
    printf("%d ",arr[i].data);

}




}
int main() {
  tnode *root = createTnode(2);

  root->right = createTnode(7);
  root->left = createTnode(3);
  root->left->left = createTnode(4);
  root->left->left->right = createTnode(9);
  root->left->left->left = createTnode(5);
  

//   preorder(root);
   
//   int *level = levelorder(root);

//   for (int i = 0; i < 100; i++) {
//     if (level[i] != 0) {
//       printf("%d, ", level[i]);
//     }
//   }
// int left = 0;
// int right = 0;
// hdleft(root, &left, 0);
// hdright(root, &right, 0);

// printf("%d",right-left+1);

top_view(root);

}
