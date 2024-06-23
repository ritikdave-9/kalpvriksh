#include<stdio.h>

#include<stdlib.h>

int isnum(char str){
    if(str=='+'||str=='-'||str=='*'||str=='/'){
        return 0;
    }
    else{
    return 1;
    }
}

typedef struct node{
    char data;
    struct node* left;
    struct node* right;
}node;

node* createNode(char data){
    node* newnode = (node*)malloc(sizeof(node));

    

    newnode->data = data;

    newnode->left = NULL;
    newnode->right = NULL;

    return newnode;

}

int evaluate(node* root){
    

    if(isnum(root->data)){
        return root->data - '0';
    }
    else{
            if(root->data=='+')
            return evaluate(root->left) + evaluate(root->right);
            
            if(root->data=='-')
            return evaluate(root->left) - evaluate(root->right);
            

            if(root->data=='*')
            return evaluate(root->left) * evaluate(root->right);
            if(root->data=='/')
            return evaluate(root->left) / evaluate(root->right);


        
    }
}




int main(){
    node* root = createNode('-');
    root->left = createNode('+');
    root->right = createNode('/');
    root->right->left = createNode('4');
    root->right->right = createNode('2');
        

    root->left->left =createNode('3');
    root->left->right = createNode('*');
    root->left->right->left = createNode('2');
    root->left->right->right = createNode('5');

    // node* head2 = NULL;

    // createTree(head2,'-');




    int ans = evaluate(root);

    printf("Answer for Given tree Is :\n");

    printf("%d",ans);
}



