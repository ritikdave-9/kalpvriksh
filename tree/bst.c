#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>

typedef struct node
{
    int data;
    struct node *left;
    struct node *right;

} node;

node *create_node(int date)
{
    node *newNode = (node *)malloc(sizeof(node));
    newNode->data = date;
    newNode->left = NULL;
    newNode->right = NULL;

    return newNode;
}

node *insert_node(node *root, int data)
{
    if (root == NULL)
    {
        return create_node(data);
    }

    if (data < root->data)
    {
        root->left = insert_node(root->left, data);
    }
    else if (data > root->data)
    {
        root->right = insert_node(root->right, data);
    }

    return root;
}

node *create_tree(node *root)
{
    int n;
    printf("enter -1 to exit \n");
    while (1)
    {
        printf("enter value");
        scanf("%d", &n);
        if (n == -1)
            break;

        root = insert_node(root, n);
    }

    return root;
}

int height(node *root)
{
    if (root == NULL)
    {
        return -1;
    }

    int left_height = height(root->left);
    int right_height = height(root->right);
    return (left_height > right_height) ? left_height + 1 : right_height + 1;
}

void inorder(node *root)
{
    if (root == NULL)
    {
        return;
    }

    inorder(root->left);
    printf("%d ,", root->data);
    inorder(root->right);
}

int max_in_bst(node *node1)
{

    if (!node1->right)
    {
        return node1->data;
    }

    return max_in_bst(node1->right);
}

int min_in_bst(node *root)
{
    if (!root->left)
    {
        return root->data;
    }

    return min_in_bst(root->left);
}

int main()
{
    node *root = create_node(5);

    create_tree(root);

    int h = height(root);
    printf("%d", h);

    return 0;
}