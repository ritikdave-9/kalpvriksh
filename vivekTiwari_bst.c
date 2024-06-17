#include<stdio.h>
#include<stdlib.h>

typedef struct btnode{
    int data;
    struct btnode* left;
    struct btnode* right;
}btnode;


typedef struct node{
    btnode *ptr;
    struct node * next;
}node;

typedef struct bfsqueue{
    node* front;
    node* back;
    int size;
}bfsqueue;

bfsqueue * initQueue(){
    bfsqueue* newqueue =  (bfsqueue*)malloc(sizeof(bfsqueue));
    newqueue->front = NULL;
    newqueue->back =NULL;
    newqueue->size = 0;
    return newqueue;
}


void addInBFSqueue(bfsqueue *q, btnode * root){
    node * newnode = (node*)malloc(sizeof(node));
    newnode->ptr = root;
    newnode->next = NULL;
    if(!q->front){
        q->front= newnode;
        q->back = newnode;
    }else{
    q->back->next = newnode;
    q->back = newnode;
    }
    (q->size)++;
}

node* removeInBFSqueue(bfsqueue *q){
    if(!q || !q->front) return NULL;
    node * temp = NULL;
    if(q->front == q->back){
        temp = q->front;
        q->front=NULL;
        q->back=NULL;
    }else{
    temp = q->front;
    q->front = q->front->next;
    }
    (q->size)--;
    return temp;
}


btnode* insertInBST(btnode* root, int val){
    if(!root){
        btnode* newnode = (btnode*)malloc(sizeof(btnode));
        if(!newnode){
            printf("Memory Allocation failed"); //Error Handling
            return NULL;
        }
        newnode->data = val;
        newnode->left = NULL;
        newnode->right = NULL;
        return newnode;
    }

    if(root->data <= val){
        root->right = insertInBST(root->right,val);
    }else{
        root->left= insertInBST(root->left,val);
    }
    return root;
}


int searchInBST(btnode* root,int val){
    if(!root)return 0;
    if(root->data == val){
        return 1;
    }
    return searchInBST(root->left,val) || searchInBST(root->right,val);
}

int max(int a, int b){
    if (a > b)return a;
    return b;
}

int heightOfTree(btnode *root){
    if(!root)return 0;
    return max(heightOfTree(root->left),heightOfTree(root->right))+1;
}

void printBST(btnode *root){
    if(!root){
        printf("-1\t ");  // this represent the NULL
        return;
    }
    printf("%d\t ",root->data);
    printBST(root->left);
    printBST(root->right);
}

void printInOrderOfTree(btnode* root){
    if(root){
        printInOrderOfTree(root->left);
        printf("%d\t ",root->data);
        printInOrderOfTree(root->right);
    }
}

void printPreOrderOfTree(btnode* root){
    if(root){
        printf("%d\t ",root->data);
        printPreOrderOfTree(root->left);
        printPreOrderOfTree(root->right);
    }
}

void printPostOrderOfTree(btnode* root){
     if(root){
        printPostOrderOfTree(root->left);
        printPostOrderOfTree(root->right);
        printf("%d\t ",root->data);
    }
}


void printLevelOrderOfTree(btnode*root){
    bfsqueue* q = (bfsqueue*)malloc(sizeof(bfsqueue));
    addInBFSqueue(q,root);
    while(q->size){
        int size = q->size;
        while(size--){
            node * f = removeInBFSqueue(q);
            btnode *fr = f->ptr;
            printf("%d\t",fr->data);
            if(fr->left){
                addInBFSqueue(q,fr->left);
            }
            if(fr->right){
                addInBFSqueue(q,fr->right);
            }
        }
        printf("\n");
    }
}

int rootToNodePath(btnode* root, int *arr, int *ind,int val){
    if(!root)return 0;
    if(root->data== val){
        *(arr+(*ind))=val;
        (*ind)++;
        return 1;
    }
    int l = rootToNodePath(root->left,arr,ind,val);
    int r = rootToNodePath(root->right,arr,ind,val);
    if(l||r){
        *(arr+(*ind))=root->data;
        (*ind)++;
        return 1;
    }
    return 0;
}


void printArray(int *arr,int len){
  for(int i = 0;i < len;i++){
    printf("%d  ",*(arr+i));
  }    
  printf("\n");
}

void printLCA(btnode *root, int v1, int v2){
    int he = heightOfTree(root);
    int *arr = (int*)calloc(sizeof(int),he+1);
    int *ind = (int *)malloc(sizeof(int));
    int r1 = rootToNodePath(root,arr,ind,v1);
    if(!r1){
        printf("%d Does Not Exist in Tree",v1);
        return;
    }
    int *arr2 = (int*)calloc(sizeof(int),he+1);
    int *ind2 = (int *)malloc(sizeof(int));
    int r2 = rootToNodePath(root,arr2,ind2,v2);
    if(!r2){
        printf("%d Does Not Exist in Tree",v2);
        return;
    }
    int *p1 = arr+(*ind-1);
    int *p2 = arr2+(*ind2-1);
    int ans = *p1;
    while(*p1==*p2){
        p1--;
        p2--;
        if(*p1==*p2){
            ans = *p1;
        }
    }

    printf("LCA is : %d\n",ans);

    
}


int helperCheckIfBST(btnode* root, int lrange,int rrange){
    if(!root){
        return 1;
    }
    if(!(lrange < root->data && root->data <= rrange)){
        return 0;
    }
    int l = helperCheckIfBST(root->left,lrange,root->data);
    int r = helperCheckIfBST(root->right,root->data,rrange);
    return l&&r;
}

void  checkIfBST(btnode *root){
     int a  = helperCheckIfBST(root,-1e9,1e9);
     if(!a){
        printf("Not A BST\n");
     }else{
        printf("Is A BST\n");
     }

}

typedef struct pair{
       btnode* p;
       btnode* q;
}pair;

pair * convertToDoubleLL(btnode *root){
    pair *g = (pair*)malloc(sizeof(pair));
    if(!root->left && !root->right){
        g->p=root;
        g->q=root;
        return g;
    }

    if(!root->left && root->right){
        g->p=root;
        pair *rg =convertToDoubleLL(root->right);
        root->right = rg->p;
        rg->p->left = root;
        g->q = rg->q;
        return g;
    }

    if(root->left && !root->right){
        pair*lg = convertToDoubleLL(root->left);
        g->p = lg->p;
        lg->q->right = root;
        root->left = lg->q;
        g->q=root;
        return g;
    }


    pair *lg = convertToDoubleLL(root->left);
    pair *rg = convertToDoubleLL(root->right);

    lg->q->right = root;
    // rg->q->right = root;
    root->right = rg->p;
    rg->p->left = root;
    g->p = lg->p;
    g->q = rg->q;
    return g;

}

btnode* convertToCircularLL(btnode *root){
    pair* g = convertToDoubleLL(root);
    btnode *temp = g->p;
    g->p->left = g->q;
    g->q->right = temp;

    return temp;  
}

void printCircularLL(btnode* pt){
    btnode *temp = pt;
    do{
        printf("%d ",temp->data);
        temp = temp->right;
    }while(temp!=pt);

    printf("\n");
}

void printDoubleLL(pair *pt){
    btnode *temp = pt->p;
    while(temp ){
        printf("%d ",temp->data);
        temp = temp->right;
    }
    printf("\n----------\n");
    temp = pt->q;
    while(temp){
        printf("%d ",temp->data);
        temp = temp->left;
    }
    printf("\n");
}

void printAtLevelK(btnode* root, int k){
    if(!root)return;
    if(k==0){
        printf("%d ",root->data);
        return;
    }
    printAtLevelK(root->left,k-1);
    printAtLevelK(root->right,k-1);
}

int printAtDistanceK(btnode*root,int val,int k){
    if(!root)return -1;
    if(root->data == val){
        printAtLevelK(root,k);
        return k-1;
    }
    int lk = printAtDistanceK(root->left,val,k);
    if(lk != -1){
        if(lk==0){
            printf("%d ",root->data);
        return -1;
        }
        printAtLevelK(root->right,lk);
        return lk-1;
    }
    int rk = printAtDistanceK(root->right,val,k);
    if(rk != -1){
        if(rk==0){
            printf("%d ",root->data);
        return -1;
        }
        printAtLevelK(root->left,rk);
        return rk-1;
    }
}

typedef struct pairint{
    int f;
    int s;
}pairint;

void helpwidthOfTree(btnode* root,int *mi ,int *mx, int p){
    if(!root)return;
    if(p < *mi){
        *mi=p;
    }
    if(p > *mx){
        *mx=p;
    }
    helpwidthOfTree(root->left,mi,mx,p-1);
    helpwidthOfTree(root->right,mi,mx,p+1);
}

pairint* widthOfTree(btnode*root){
    int mia=0,mxa=0;
    int *mi = &mia;
    int *mx = &mxa;

    helpwidthOfTree(root,mi,mx,0);
    pairint* pi = (pairint*)malloc(sizeof(pairint));
    pi->f = mia;
    pi->s = mxa;
    return pi;
}

typedef struct nodeint{
    int data;
    int ex;
    struct nodeint *next;
}nodeint;

typedef struct linkedlistint{
    int data;
    nodeint *head;
    nodeint *tail;
}linkedlistint;

typedef struct nodeL{
    btnode *ptr;
    struct nodeL * next;
    int ex;
}nodeL;

typedef struct bfsqueueL{
    nodeL* front;
    nodeL* back;
    int size;
}bfsqueueL;


void addInBFSqueueL(bfsqueueL *q, btnode * root,int ex){
    nodeL * newnode = (nodeL*)malloc(sizeof(nodeL));
    newnode->ptr = root;
    newnode->next = NULL;
    newnode->ex = ex;
    if(!q->front){
        q->front= newnode;
        q->back = newnode;
    }else{
    q->back->next = newnode;
    q->back = newnode;
    }
    (q->size)++;
}

nodeL* removeInBFSqueueL(bfsqueueL *q){
    if(!q || !q->front) return NULL;
    nodeL * temp = NULL;
    if(q->front == q->back){
        temp = q->front;
        q->front=NULL;
        q->back=NULL;
    }else{
    temp = q->front;
    q->front = q->front->next;
    }
    (q->size)--;
    return temp;
}

void insertInLLextra(linkedlistint *ll, int data,int ex){
    nodeint* temp = (nodeint *)malloc(sizeof(nodeint));
    temp->data = data;
    temp->next = NULL;
    temp->ex = ex;
    if(!ll->head){
        ll->head = ll->tail = temp;
        return;
    }
    ll->tail->next = temp;
    ll->tail = temp;
}

void printlinkedlistLL(btnode * root,linkedlistint **arr,int he){
    pairint* al = widthOfTree(root); 
    int exh = -1*(al->f);
    int he2 = exh+al->s+2;
   
   linkedlistint **brr =  (linkedlistint ** )calloc(sizeof(linkedlistint*),he2);
   for(int i = 0;i < he2;i++){
        *(brr+i) = (linkedlistint *)malloc(sizeof(linkedlistint));
        (*(brr+i))->head = NULL;
        (*(brr+i))->tail = NULL;
    }


    for(int i = 0;i < he;i++){
        nodeint *temp = (*(arr+i))->head;
        while(temp){
            linkedlistint *row = *(brr+(temp->ex+exh));
            insertInLLextra(row,temp->data,temp->ex+exh);
            temp = temp->next;
        }
        
    }
    
    
     for(int i = 0;i < he2-1;i++){
        nodeint *temp = (*(brr+i))->head;
        printf("%d :-> ",i-exh);
        while(temp){
            printf("%d ",temp->data,temp->ex+exh);
            temp = temp->next;
        }
        printf("\n");
        
    }

    printf("\n");

}

void printVerticalOrderTraversal(btnode*root){
    int he = heightOfTree(root);
    linkedlistint **arr = (linkedlistint ** )calloc(sizeof(linkedlistint*),he);
    for(int i = 0;i < he;i++){
        *(arr+i) = (linkedlistint *)malloc(sizeof(linkedlistint));
        (*(arr+i))->head = NULL;
        (*(arr+i))->tail = NULL;
    }

    bfsqueueL* q = (bfsqueueL*)malloc(sizeof(bfsqueueL));
    addInBFSqueueL(q,root,0);
    int level = 0;
    while(q->size){
        int size = q->size;
        while(size--){
            nodeL * f = removeInBFSqueueL(q);
            btnode *fr = f->ptr;
            int ex = f->ex;
            // printf("%d\t",fr->data);
            linkedlistint *row = *(arr+level);
            insertInLLextra(row,fr->data,ex);         
            if(fr->left){
                addInBFSqueueL(q,fr->left,ex-1);
            }
            if(fr->right){
                addInBFSqueueL(q,fr->right,ex+1);
            }
        }
        level++;
    }
    
    printlinkedlistLL(root,arr,he);

}

btnode* initTree(){
    int data;
    scanf("%d",&data);
    if(data == -1){
        return NULL;
    }
    btnode * root = (btnode* )malloc(sizeof(btnode));
    root->data = data;
    root->left = initTree();
    root->right =initTree();
    return root;
}


int main(){
    btnode* root=NULL;
    root = insertInBST(root,5);
    root =insertInBST(root,4);
    root =insertInBST(root,7);
    root =insertInBST(root,8);
    root =insertInBST(root,2);
    root =insertInBST(root,6);

    // printf("%p\n",root);
    int search_value = 8;
    int flag = searchInBST(root,search_value);
    if(flag){
        printf("%d Exist In BST\n",search_value);
    }else{
        printf("%d Does Not Exist In BST\n",search_value);
    }

    int he = heightOfTree(root);
    printf("%d is Height of BST\n",he);
    printf("BST\n");
    printBST(root);
    printf("\n");
    printf("PreOrder Of BST\n");
    printPreOrderOfTree(root);
    printf("\n");
    printf("InOrder of BST\n");
    printInOrderOfTree(root);
    printf("\n");
    printf("PostOrder of BST\n");
    printPostOrderOfTree(root);
    printf("\n");
    printf("LevelOrder Of BST\n");
    printLevelOrderOfTree(root);
    printf("\n");

    int *arr = (int*)calloc(sizeof(int),he+1);
    int *ind = (int *)malloc(sizeof(int));
    rootToNodePath(root,arr,ind,6);
    printArray(arr,he);
    printLCA(root,2,4);
    checkIfBST(root);

    // btnode* rt = (btnode*)malloc(sizeof(btnode));
    // rt->data = 2;
    // btnode* rl = (btnode*)malloc(sizeof(btnode));
    //  rl->data = 1;
    // rl->left = NULL;
    // rl->right = NULL;
    // btnode* rr = (btnode*)malloc(sizeof(btnode));
    //  rr->data = 3;
    // rr->left = NULL;
    // rr->right = NULL;
    // rt->left = rl;
    // rt->right = rr;
    // pair * xd = convertToDoubleLL(rt);
    // printDoubleLL(xd);
    // btnode * ls = convertToCircularLL(root);
    // printCircularLL(ls);
    // printAtLevelK(root,2);
    printf("==========\n");
    // printAtDistanceK(root,2,3);
    // printf("\n");
    // pairint* lls = widthOfTree(root);
    // printf("%d  %d\n",lls->f,lls->s);
    btnode * nrt = initTree();
    printVerticalOrderTraversal(nrt);
}
