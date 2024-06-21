#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
  int data;
  struct Node *left;
  struct Node *right;

} Node;

Node *createNode(int data) {
  Node *newNode = (Node *)malloc(sizeof(Node));
  newNode->data = data;
  newNode->left = NULL;
  newNode->right = NULL;
  return newNode;
}
int power(int base, int exponent) {
  int result = 1;
  for (int i = 0; i < exponent; i++) {
    result *= base;
  }
  return result;
}
Node *insert(Node *root, int data) {
  if (!root) {
    return createNode(data);
  }

  if (data < root->data) {
    root->left = insert(root->left, data);
  } else {
    root->right = insert(root->right, data);
  }

  return root;
}

Node *create_bst() {
  Node *root = NULL;

  while (1) {
    int n;
    scanf("%d", &n);
    if (n == -1) {
      return root;
    }

    root = insert(root, n);
  }

  return root;
}

int height(Node *root) {
  if (!root) {
    return 0;
  }

  int left = height(root->left);
  int right = height(root->right);

  return (left > right) ? left + 1 : right + 1;
}

int total_elements(Node *root) {
  if (!root) {
    return 0;
  }
  return total_elements(root->left) + total_elements(root->right) + 1;
}
void inorderUtils(Node *root, int *array, int *index) {
  if (!root) {
    return;
  }

  inorderUtils(root->left, array, index);
  array[*index] = root->data;
  (*index)++;
  inorderUtils(root->right, array, index);
}
int *inorder(Node *root) {
  int index = 0;
  int *array = (int *)calloc(sizeof(int), total_elements(root) + 1);
  inorderUtils(root, array, &index);

  return array;
}
void preorderUtils(Node *root, int *array, int *index) {
  if (!root) {
    return;
  }

  array[*index] = root->data;
  (*index)++;
  inorderUtils(root->left, array, index);
  inorderUtils(root->right, array, index);
}
int *preorder(Node *root) {
  int index = 0;
  int *array = (int *)calloc(sizeof(int), total_elements(root) + 1);
  preorderUtils(root, array, &index);

  return array;
}
void postorderUtils(Node *root, int *array, int *index) {
  if (!root) {
    return;
  }

  inorderUtils(root->left, array, index);
  inorderUtils(root->right, array, index);
  array[*index] = root->data;
  (*index)++;
}
int *postorder(Node *root) {
  int index = 0;
  int *array = (int *)calloc(sizeof(int), total_elements(root) + 1);
  postorderUtils(root, array, &index);

  return array;
}

typedef struct stack {
  int top;
  int size;
  Node **array;
} stack;

stack *createStack(int size) {
  stack *newstack = (stack *)malloc(sizeof(stack));
  newstack->size = size;
  newstack->top = -1;
  newstack->array = (Node **)malloc(sizeof(Node *) * size);
  return newstack;
}

void push(stack *st, Node *temp) {
  st->top++;
  st->array[st->top] = temp;
}

void print_array(int *array, int size) {
  printf("\n");
  for (int i = 0; i < size; i++) {
    // if (array[i] == 0)
    // {
    //     break;
    // }
    printf("%d, ", array[i]);
  }
  printf("\n");
}

// ===================================================================
// NOT CLEAR THE PROBLEM STATEMENT

// void width_utils(Node* root, int * left, int * right, int  n){
//     if(!root){
//         return ;
//     }

//     if(n>*left){
//         (*left)++;
//     }

//     if(n<*right){
//         (*right)--;
//     }

//     width_utils(root->left,left,right,n+1);
//     width_utils(root->right,left,right,n-1);

// }

// int width_of_tree(Node* root){
//     int left = 0;
//     int right = 0;

//     width_utils(root,&left,&right,0);
//     return -right + left;

// }

int max(int a, int b) { return a > b ? a : b; }

int most_left(Node *root) {
  if (!root->left) {
    return root->data;
  }

  return most_left(root->left);
}
int most_right(Node *root) {

  if (!root->right) {
    return root->data;
  }

  return most_right(root->right);
}
int predecissor(Node *root) {
  if (!root || !root->left) {
    return -1;
  }

  return most_right(root->left);
}

int successor(Node *root) {
  if (!root || !root->right) {
    return -1;
  }

  return most_left(root->right);
}
int diameter(Node *root) {
  if (!root) {
    return 0;
  }
  int left_height = height(root->left);
  int right_height = height(root->right);
  int left_diam = diameter(root->left);
  int right_diam = diameter(root->right);

  return max(left_height + right_height, max(left_diam, right_diam));
}

int valid_bst_using_inorder(Node *root) {
  int total = total_elements(root);
  int *array = inorder(root);
  int index = 0;

  for (int i = 0; i < total - 1; i++) {
    if (array[i] > array[i + 1]) {
      print_array(array, total);
      free(array);

      return 0;
    }
  }

  print_array(array, total);
  free(array);

  return 1;
}

void mirror(Node *root) {
  if (!root) {
    return;
  }
  mirror(root->left);
  mirror(root->right);

  Node *temp = root->left;
  root->left = root->right;
  root->right = temp;
}

int pathUtils(Node *root, int *array, int *index, int val) {

  if (!root) {
    return 0;
  }
  if (root->data == val) {
    array[*index] = val;
    (*index)++;
    return 1;
  }

  int l = pathUtils(root->left, array, index, val);
  int r = pathUtils(root->right, array, index, val);

  if (l || r) {
    array[(*index)++] = root->data;
    return 1;
  }

  return 0;
}

int *path(Node *root, int val) {
  int h = height(root);
  int *array = (int *)calloc(sizeof(int), h + 1);
  int index = 0;

  int n = pathUtils(root, array, &index, val);

  return array;
}

int lca(Node *root, int a, int b) {
  int *pathA = path(root, a);
  int *pathB = path(root, b);

  int h = height(root);
  int i = 0;
  while (pathA[i] != 0) {
    i++;
  }
  int j = 0;
  while (pathB[j] != 0) {
    j++;
  }
  int lca = -1;
  while (i >= 0 && j >= 0 && pathA[i] == pathB[j]) {
    lca = pathA[i];
    i--;
    j--;
  }

  return lca;
}

typedef struct qNode {
  Node *value;
  struct qNode *next;

} qNode;

qNode *createQNode(Node *value) {

  qNode *newNode = (qNode *)malloc(sizeof(qNode));
  newNode->value = value;
  newNode->next = NULL;
  return newNode;
}

typedef struct queue {
  qNode *start;
  qNode *end;
} queue;

queue *createQueue() {
  queue *newqueue = (queue *)malloc(sizeof(queue));
  newqueue->start = NULL;
  newqueue->end = NULL;
  return newqueue;
}

void pushqueue(queue *q, Node *node) {
  qNode *newnode = createQNode(node);

  if (!q->end) {

    q->start = newnode;
    q->end = newnode;
  } else {
    q->end->next = newnode;
  }
}

Node *pop(queue *q) {
  Node *temp = q->start->value;
  qNode *start = q->start;
  q->start = q->start->next;
  free(start);

  return temp;
}

Node *queueTop(queue *q) { return q->start->value; }

void printLevelInTree(Node *root, int level) {
  if (!root) {
    return;
  }
  if (level == 1) {
    printf("%d ", root->data);
  } else if (level > 1) {
    printLevelInTree(root->left, level - 1);

    printLevelInTree(root->right, level - 1);
  }
}

void printLevelOrder(Node *root) {
  int h = height(root);
  for (int i = 1; i < h + 1; i++) {
    printLevelInTree(root, i);
    printf("\n");
  }
}

int leafCount(Node *root) {
  if (!root) {
    return 0;
  }
  if (!root->left && !root->right) {
    return 1;
  }

  return leafCount(root->left) + leafCount(root->right);
}

int checkBalanced(Node *root) {

  if (!root) {
    return 1;
  }

  int left_height = height(root->left);
  int right_height = height(root->right);

  return (abs(left_height - right_height) <= 1 && checkBalanced(root->left) &&
          checkBalanced(root->right));
}

Node *copyTree(Node *root) {
  if (!root) {
    return NULL;
  }

  Node *newTree = createNode(root->data);
  newTree->left = copyTree(root->left);
  newTree->right = copyTree(root->right);
  return newTree;
}

void spiral(Node *root) {

  Node *mir = copyTree(root);

  mirror(mir);

  int h = height(root);

  for (int i = 1; i <= h; i++) {
    if (i % 2 == 1) {
      printLevelInTree(root, i);
      printf("\n");
    } else {
      printLevelInTree(mir, i);
      printf("\n");
    }
  }
}

int checkIdentical(Node *root1, Node *root2) {
  if (!root1 && !root2) {
    return 1;
  } else if (!root1 || !root2) {
    return 0;
  }

  if (root1->data == root2->data && checkIdentical(root1->left, root2->left) &&
      checkIdentical(root1->right, root2->right)) {
    return 1;
  }

  return 0;
}

void verticleElements(Node *root, int *array, int l, int curr) {
  if (!root) {

    return;
  }
  if (curr == l) {
    *array = root->data;
    array++;
  }
  verticleElements(root->right, array, l, curr + 1);
  verticleElements(root->left, array, l, curr - 1);
}
int *verticleOrderTraversal(Node *root, int l) {

  int *array = (int *)calloc(sizeof(int), 20);

  verticleElements(root, array, l, 0);
  return array;
}

void leftviewUtils(Node *root, int *array, int *level, int current) {
  if (!root) {
    return;
  }

  if (current == *level) {
    array[current] = root->data;
    (*level)++;
  }

  leftviewUtils(root->left, array, level, current + 1);
  leftviewUtils(root->right, array, level, current + 1);
}

int *leftView(Node *root) {
  int level = 0;
  int h = height(root);
  int *array = (int *)calloc(sizeof(int), h);

  leftviewUtils(root, array, &level, 0);

  return array;
}

void rightviewUtils(Node *root, int *array, int *level, int current) {
  if (!root) {
    return;
  }

  if (current == *level) {
    array[current] = root->data;
    (*level)++;
  }

  rightviewUtils(root->right, array, level, current + 1);
  rightviewUtils(root->left, array, level, current + 1);
}

int *rightView(Node *root) {
  int level = 0;
  int h = height(root);
  int *array = (int *)calloc(sizeof(int), h);

  rightviewUtils(root, array, &level, 0);

  return array;
}

int search_in_array(int *arr, int start, int end, int element) {
  for (int i = start; i <= end; i++) {
    if (arr[i] == element) {
      return i;
    }
  }

  return -1;
}

Node *convert_to_binary_tree(int *pre, int *in, int instart, int inend,
                             int *index) {

  if (instart > inend) {
    return NULL;
  }
  Node *root = createNode(pre[*(index)]);
  (*index)++;

  if (instart == inend) {
    return root;
  }

  int pos = search_in_array(in, instart, inend, root->data);

  root->left = convert_to_binary_tree(pre, in, instart, pos - 1, index);

  root->right = convert_to_binary_tree(pre, in, pos + 1, inend, index);

  return root;
}

int compare(Node *root1, Node *root2) {
  if (!root1 && !root2) {
    return 1;
  }
  if (!root1 || !root2) {
    return 0;
  }

  return (root1->data == root2->data) && compare(root1->left, root2->left) &&
         compare(root1->right, root2->right);
}

void delete_in_bst(Node *root, int data) {
  if (!root) {
    return;
  }
  if (root->left && root->left->data == data) {
    Node *temp = root->left;
    root->left =
        (root->left->left != NULL) ? root->left->left : root->left->right;

    Node *temp2 = root->left;

    if (temp2) {
      while (temp2->right) {
        temp2 = temp2->right;
      }

      temp2->right = temp->right;
    }

    free(temp);

    return;
  }
  if (root->right && root->right->data == data) {
    Node *temp = root->right;
    root->right =
        (root->right->left != NULL) ? root->right->left : root->right->right;

    Node *temp2 = root->right;

    if (temp2) {

      while (temp2->right) {
        temp2 = temp2->right;
      }
      temp2->right = temp->right;
    }

    free(temp);

    return;
  }
  delete_in_bst(root->left, data);
  delete_in_bst(root->right, data);
}

void leftHD(Node *root, int *max, int current) {
  if (!root) {
    return;
  }

  if (current < *max) {
    (*max)--;
  }
  leftHD(root->left, max, current - 1);

  leftHD(root->right, max, current + 1);
}

void rightHD(Node *root, int *max, int current) {
  if (!root) {
    return;
  }

  if (current > *max) {
    (*max)++;
  }
  rightHD(root->left, max, current - 1);
  rightHD(root->right, max, current + 1);
}

int HDofTree(Node *root) {

  int left = 0;

  int right = 0;

  leftHD(root, &left, 0);
  rightHD(root, &right, 0);

  return -left + right + 1;
}

void topViewUtils(Node *root, int left, int hd, int *arr) {
  if (!root) {
    return;
  }

  if (arr[hd - left] == 0) {

    arr[hd - left] = root->data;
  }
  topViewUtils(root->right, left, hd + 1, arr);
  topViewUtils(root->left, left, hd - 1, arr);
}

int *topView(Node *root) {

  int left = 0;
  int right = 0;

  leftHD(root, &left, 0);
  rightHD(root, &right, 0);

  int *arr = (int *)calloc(right - left + 1, sizeof(int));

  topViewUtils(root, left, 0, arr);

  return arr;
}

void bottomvviewUtils(Node *root, int left, int hd, int *arr) {
  if (!root) {
    return;
  }
  arr[hd - left] = root->data;
  bottomvviewUtils(root->right, left, hd + 1, arr);
  bottomvviewUtils(root->left, left, hd - 1, arr);
}

int *bottomView(Node *root) {
  int left = 0;
  int right = 0;
  int w = HDofTree(root);
  leftHD(root, &left, 0);
  rightHD(root, &right, 0);
  int *arr = (int *)calloc(w, sizeof(int));

  bottomvviewUtils(root, left, 0, arr);
  return arr;
}
void left_boundry(Node *root, int *arr, int *index) {
  if (!root) {
    return;
  }

  if (root->left) {

    arr[*index] = root->data;
    (*index)++;
    left_boundry(root->left, arr, index);

  } else if (root->right) {
    arr[*index] = root->data;
    (*index)++;
    left_boundry(root->right, arr, index);
  }
}

void leafNodeTraversal(Node *root, int *arr, int *index) {
  if (!root) {
    return;
  }
  leafNodeTraversal(root->left, arr, index);
  if (!root->left && !root->right) {
    arr[*index] = root->data;
    (*index)++;
  }
  leafNodeTraversal(root->right, arr, index);
}

void rightBoundryTraversal(Node *root, int *arr, int *index) {
  if (!root) {
    return;
  }

  if (root->right) {
    rightBoundryTraversal(root->right, arr, index);
    arr[*index] = root->data;
    (*index)++;
  } else if (root->left) {

    rightBoundryTraversal(root->left, arr, index);
    arr[*index] = root->data;
    (*index)++;
  }
}

int *boundryTraversal(Node *root) {
  int w = HDofTree(root);
  int *arr = (int *)calloc(2 * w, sizeof(int));
  int index = 0;
  arr[index] = root->data;
  index++;

  left_boundry(root->left, arr, &index);

  // leafNodeTraversal(root->left, arr, &index);
  leafNodeTraversal(root, arr, &index);

  if (!root->right) {

    rightBoundryTraversal(root->right, arr, &index);
  } else {
    rightBoundryTraversal(root, arr, &index);
  }

  return arr;
}

typedef struct DNode {
  int data;
  struct DNode *prev;
  struct DNode *next;

} DNode;

DNode *createDNode(int data) {
  DNode *new = (DNode *)malloc(sizeof(DNode));
  new->data = data;
  new->prev = NULL;
  new->next = NULL;
  return new;
}
Node *head = NULL, *tail = NULL;
void TreeToDListUtils(Node *root) {
  if (!root) {
    return;
  }

  TreeToDListUtils(root->left);
  Node *temp = root->right;
  if (!head) {
    head = tail = root;
    root->left = root->right = NULL;
  } else {
    tail->right = root;
    root->left = tail;
    root->right = NULL;
    tail = root->right;
  }

  TreeToDListUtils(temp);
}

void printDlist() {
  Node *temp = head;
  while (temp) {
    printf("%d = ", temp->data);
    temp = temp->right;
  }
}


int bstfloor(Node*root, int data){
  Node* temp = root;
  int floor  = -1;
  
  while(temp){
    if(temp->data==data){
      return data;
    }
    if(temp->data>data){
      temp = temp->left;
    }
    else {
      floor= temp->data;
      temp = temp->right;
    }
  }
  return  floor;

}

int bstceil(Node*root, int data){
  Node* temp = root;
  int floor  = -1;
  
  while(temp){
    if(temp->data==data){
      return data;
    }
    if(temp->data<data){
      temp = temp->right;
    }
    else {
      floor= temp->data;
      temp = temp->left;
    }
  }
  return  floor;

}

int *florAndCeil(Node *root, int data) {
  int *arr = (int *)malloc(sizeof(int)*2);

  arr[0] = bstfloor(root, data);
  arr[1] = bstceil(root, data);
  return arr;
  
}

int main() {
  Node *root1 = create_bst();
  // int * ans = florAndCeil(root1, 4);
  // print_array(ans,2);

  int fl = bstfloor(root1, 12);
  printf("%d ",fl);
  int ce = bstceil(root1, 12);
printf("%d",ce);

}
