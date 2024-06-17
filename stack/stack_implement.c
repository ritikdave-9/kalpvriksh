#include<stdio.h>
#include<stdlib.h>

typedef struct stack{
    int top;
    int *array;
    int size;

}stack;

stack *createStack(int size){
    stack* st = (stack*)malloc(sizeof(stack));
    st->size = size;

    st->top = -1;

    st->array = (int*)malloc(sizeof(int)*size);

    return st;

}
int isEmpty(stack*st){
    return st->top == -1;
}
int isFull(stack* st){
    return st->top >= st->size - 1;

}
void push(stack* st,int data){

    if(isFull(st)){
        printf("stack is full");
        return ;
    }
    
    st->top++;
    st->array[st->top] = data;

    

}

void print_stack(stack*st){
    int i = st->top;
    printf("\n");

    while(i>=0){
        printf("%d, ",st->array[i--]);
    }
    printf("\n");
}


int pop(stack *st){
    if(!isEmpty(st)){
        return st->array[st->top--];

    }
    else{
        return -1;
    }
}

int top(stack*st){
    return st->array[st->top];
}

int main(){
    stack* st = createStack(10);

    push(st,2);    push(st,1);
    push(st,3);
    push(st,4);
    push(st,5);
    push(st,6);

    print_stack(st);
    int n = pop(st);
    printf("%d",n);
        print_stack(st);

}