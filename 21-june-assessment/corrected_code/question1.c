#include <stdio.h>

#include <stdlib.h>

#include <string.h>

typedef struct node {
  char *data;
  struct node *left;
  struct node *right;

} node;

node *create_node(char *data) {
  node *newnode = (node *)malloc(sizeof(node));
  newnode->data = strdup(data);
  newnode->left = NULL;
  newnode->right = NULL;
  return newnode;
}
int precedence(char c) {
  if (c == '+' || c == '-') {
    return 1;
  } else if (c == '*' || c == '/')
    return 2;

  else {
    return 0;
  };
}
int isOperator(char *c) {
  if (*c == '+' || *c == '-' || *c == '*' || *c == '/') {
    return 1;
  } else {
    return 0;
  }
}

node *createTree(char *str) {
  int length = strlen(str);
  if (length == 0)
    return NULL;

  char *temp = str;
  int index = -1;
  int minprecedence = 10;
  for (int i = 0; i < length; i++) {
    if (isOperator(&str[i]) && precedence(str[i]) <= minprecedence) {
      minprecedence = precedence(str[i]);
      index = i;
    }
  }
  if (index == -1) {
    return create_node(str);
  }

  char *opr = (char *)malloc(sizeof(char) * 2);
  opr[0] = str[index];
  opr[1] = '\0';

  node *root = create_node(opr);

  char *left = (char *)malloc(index + 1);
  strncpy(left, str, index);
  left[index] = '\0';

  char *right = (char *)malloc(length - index);
  strncpy(right, str + index + 1, length - index - 1);
  right[length - index - 1] = '\0';

  root->left = createTree(left);
  root->right = createTree(right);

  free(left);
  free(right);

  return root;
}

int convertInt(char *str) {
  int i = 0;

  int length = strlen(str);

  int num = 0;

  for (int i = 0; i < length; i++) {

    num = num * 10 + (str[i] - '0');
  }
  return num;
}

void inorder(node *root) {
  if (!root) {
    return;
  }

  inorder(root->left);
  printf("%s ", root->data);

  inorder(root->right);
}

int eveluate(node *root) {
  if (!isOperator(root->data)) {
    return convertInt(root->data);
  }

  if (strcmp(root->data, "+") == 0)
    return eveluate(root->left) + eveluate(root->right);
  if (strcmp(root->data, "-") == 0)
    return eveluate(root->left) - eveluate(root->right);
  if (strcmp(root->data, "*") == 0)
    return eveluate(root->left) * eveluate(root->right);
  if (strcmp(root->data, "/") == 0)
    return eveluate(root->left) / eveluate(root->right);
  return 0;
}

int correctExpression(char* str){
    int length = strlen(str);
    for(int i= 0;i<length;i++){
        if(isOperator(&str[i])&&isOperator(&str[i+1])){
            return 0;
        }
    }
    return 1;
}
int main() {
  char str[100];

  printf("Enter the infix Expression without space: \n");

  scanf("%s", str);

  if(correctExpression(str)){

  node *root = createTree(str);

  printf("The Expression is :\n");

  inorder(root);
  printf("\n");

  int ans = eveluate(root);
  printf("The Solution of the expression is :\n");
  printf("%d\n", ans);
  }
  else {
  printf("Enter a valid Expression\n");
  }

}
