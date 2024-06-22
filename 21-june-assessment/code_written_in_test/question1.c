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

// node* createTree(node* root,int value){
//     if(!root){
//         createNode(value);
        
//     }

//     char res;

//     printf("want to insert in left enter y/n:\n");
//     scanf("%c",&res);

//     if(res=='y'){
//         char temp;
//          scanf("%c",&temp);


        
//     }else{
//         root->left= NULL;
//     }
//     res = '\0';

//     printf("want to insert in right enter y/n:\n");

//     if(res=='y'){
//         root->right = createTree(root->right,value);
//     }
//     else{
//         return NULL;
//     }

//     return root;


    



    
// }


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



