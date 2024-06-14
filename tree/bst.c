#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct node
{
    int data;
    struct node *left;
    struct node *right;

} node;

node *createNode(int data)
{
    node *newnode = (node *)malloc(sizeof(node));
    newnode->data = data;
    newnode->left = NULL;
    newnode->right = NULL;
    return newnode;
}
int power(int base, int exponent)
{
    int result = 1;
    for (int i = 0; i < exponent; i++)
    {
        result *= base;
    }
    return result;
}
node *insert(node *root, int data)
{
    if (!root)
    {
        return createNode(data);
    }

    if (data < root->data)
    {
        root->left = insert(root->left, data);
    }
    else
    {
        root->right = insert(root->right, data);
    }

    return root;
}

node *create_bst()
{
    node *root = NULL;

    while (1)
    {
        int n;
        scanf("%d", &n);
        if (n == -1)
        {
            return root;
        }

        root = insert(root, n);
    }

    return root;
}

int height(node *root)
{
    if (!root)
    {
        return -1;
    }

    int left = height(root->left);
    int right = height(root->right);

    return (left > right) ? left + 1 : right + 1;
}

int total_elements(node *root)
{
    if (!root)
    {
        return 0;
    }
    return total_elements(root->left) + total_elements(root->right) + 1;
}
void inorderUtils(node *root, int *array, int *index)
{
    if (!root)
    {
        return;
    }

    inorderUtils(root->left, array, index);
    array[*index] = root->data;
    (*index)++;
    inorderUtils(root->right, array, index);
}
int * inorder(node* root){
    int index = 0;
    int * array = (int * )calloc(sizeof(int),total_elements(root)+1);
    inorderUtils(root,array,&index);

    return array;


}
void preorderUtils(node *root, int *array, int *index)
{
    if (!root)
    {
        return;
    }

    array[*index] = root->data;
    (*index)++;
    inorderUtils(root->left, array, index);
    inorderUtils(root->right, array, index);
}
int * preorder(node* root){
    int index = 0;
    int * array = (int * )calloc(sizeof(int),total_elements(root)+1);
    preorderUtils(root,array,&index);

    return array;


}
void postorderUtils(node *root, int *array, int *index)
{
    if (!root)
    {
        return;
    }

    inorderUtils(root->left, array, index);
    inorderUtils(root->right, array, index);
    array[*index] = root->data;
    (*index)++;
}
int * postorder(node* root){
    int index = 0;
    int * array = (int * )calloc(sizeof(int),total_elements(root)+1);
    postorderUtils(root,array,&index);

    return array;


}

typedef struct stack
{
    int top;
    int size;
    node **array;
} stack;

stack *createStack(int size)
{
    stack *newstack = (stack *)malloc(sizeof(stack));
    newstack->size = size;
    newstack->top = -1;
    newstack->array = (node **)malloc(sizeof(node *) * size);
    return newstack;
}

void push(stack *st, node *temp)
{
    st->top++;
    st->array[st->top] = temp;
}

void print_array(int *array, int size)
{
    printf("\n");
    for (int i = 0; i < size; i++)
    {
        if (array[i] == 0)
        {
            break;
        }
        printf("%d, ", array[i]);
    }
    printf("\n");
}

// ===================================================================
// NOT CLEAR THE PROBLEM STATEMENT

// void width_utils(node* root, int * left, int * right, int  n){
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

// int width_of_tree(node* root){
//     int left = 0;
//     int right = 0;

//     width_utils(root,&left,&right,0);
//     return -right + left;

// }

int max(int a, int b)
{
    return a > b ? a : b;
}

int most_left(node *root)
{
    if (!root->left)
    {
        return root->data;
    }

    return most_left(root->left);
}
int most_right(node *root)
{

    if (!root->right)
    {
        return root->data;
    }

    return most_right(root->right);
}
int predecissor(node *root)
{
    if (!root || !root->left)
    {
        return -1;
    }

    return most_right(root->left);
}

int successor(node *root)
{
    if (!root || !root->right)
    {
        return -1;
    }

    return most_left(root->right);
}
int diameter(node *root)
{
    if (!root)
    {
        return 0;
    }
    int left_height = height(root->left);
    int right_height = height(root->right);
    int left_diam = diameter(root->left);
    int right_diam = diameter(root->right);

    return max(left_height + right_height, max(left_diam, right_diam));
}

int valid_bst_using_inorder(node *root)
{
    int total = total_elements(root);
    int *array = inorder(root);
    int index = 0;
    

    for (int i = 0; i < total - 1; i++)
    {
        if (array[i] > array[i + 1])
        {
            print_array(array, total);
            free(array);

            return 0;
        }
    }

    print_array(array, total);
    free(array);

    return 1;
}

void mirror(node *root)
{
    if (!root)
    {
        return;
    }
    mirror(root->left);
    mirror(root->right);

    node *temp = root->left;
    root->left = root->right;
    root->right = temp;
}
int main()
{
    node *root = create_bst();

    // printf("%d",h);

    // printf("%d",root->data);

    int *array =   inorder(root);

    int index = 0;


    int total = total_elements(root);

    printf("%d", total);

    print_array(array, 100);

    // int d = width_of_tree(root);
    // printf("%d",d);
    // int d = diameter(root);
    // printf("%d",d);

    // int suc = successor(root);
    // printf("%d", suc);
    // root->right->data = 50;
    printf("%d", valid_bst_using_inorder(root));
}
