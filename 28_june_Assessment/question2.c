#include<stdio.h>
#include<stdlib.h>

#include<string.h>


typedef struct Qnode{
    char* data;
    struct Qnode* next;
}Qnode;

Qnode* createQnode(char* data){
    Qnode* newnode = (Qnode*)malloc(sizeof(Qnode));
    newnode->data = strdup(data);
    newnode->next = NULL;
    return newnode;

}

typedef struct queue{
    Qnode* front;
    Qnode* back;
}queue;

queue* createQueue(){
    queue* newqueue = (queue*)malloc(sizeof(queue));
    newqueue->front = NULL;
    newqueue->back = NULL;

    return newqueue;
}

void enQueue(queue* q, char* data){
    Qnode* newnode = createQnode(data);
    if(!q->front){
        q->front = newnode;
        q->back = newnode;
    }
    else{
        q->back->next = newnode;
        q->back = newnode;
    }
}

Qnode* deQueue(queue* q){
    if(!q->front){
        return NULL;
    }
    Qnode* current = q->front;
    
    q->front = current->next;

    return current;

}
Qnode * topQueue(queue* q){
    return q->front;
}


void pushOnQueue(queue* q, char* data){
    enQueue(q,data);

    Qnode* flag = q->back;

    while(topQueue(q)!=flag){
        enQueue(q,deQueue(q)->data);

    }
}

int main(){
    queue* q = createQueue();
    
    int op;

    while(1){

    printf("\n 1 for push a new commit to current branch\n 2 pop the most recent commit from current branch \n 3 view the most recent commit \n 4 check if there are any commit present \n 5 Exit\n");

    scanf("%d",&op);
    switch(op){
        case 1:
        printf("\nEnter string:\n");
        char str[20];
        scanf("%s",str);
        pushOnQueue(q,str);
        break;

        case 2:
        deQueue(q);
        printf("popped top commit of current branch \n");
        break;

        case 3:
        printf("the latest commit is :\n");
        printf("%s\n",topQueue(q)->data);

        break;

        case 4:
        
        break;

        case 5:
        break;
        default:
        break;


    }
    }
}

