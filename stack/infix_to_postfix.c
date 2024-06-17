#include <stdio.h>
#include <stdlib.h>

typedef struct stack
{
    int top;
    char *array;
    int size;

} stack;

int precidence(char c)
{
    switch (c)
    {
    case ')':
        return 1;
    case '*':
    case '/':
        return 5;
    case '+':
    case '-':
        return 3;
    case '(':
        return 6;
    default:
        return 0;
    }
}

int isoprator(char c)
{
    if (c == '+' || c == '-' || c == '(' || c == ')' || c == '*' || c == '/')
    {
        return 1;
    }
    return 0;
}

int string_length(char *str)
{
    int i = 0;
    int length = 0;
    char *temp = str;

    while (*temp)
    {
        length++;
        temp++;
    }

    return length;
}

stack *createStack(int size)
{
    stack *st = (stack *)malloc(sizeof(stack));
    st->size = size;

    st->top = -1;

    st->array = (char *)malloc(sizeof(char) * size);

    return st;
}
int isEmpty(stack *st)
{
    return st->top == -1;
}
int isFull(stack *st)
{
    return st->top >= st->size - 1;
}
void push(stack *st, char data)
{

    if (isFull(st))
    {
        printf("stack is full");
        return;
    }

    st->top++;
    st->array[st->top] = data;
}

void print_stack(stack *st)
{
    int i = st->top;
    printf("\n");

    while (i >= 0)
    {
        printf("%c, ", st->array[i--]);
    }
    printf("\n");
}

char pop(stack *st)
{
    if (!isEmpty(st))
    {
        return st->array[st->top--];
    }
    else
    {
        return -1;
    }
}

char top(stack *st)
{
    return st->array[st->top];
}

char *infix_to_postfix(char *str)
{

    char *temp = str;

    char *ans = (char *)malloc(sizeof(char) * string_length(str) + 1);
    char *Ans_temp = ans;

    stack *st = createStack(100);

 

}

int main()
{
    stack *st = createStack(10);

    push(st, 'c');

    print_stack(st);
    int n = pop(st);
    printf("%d", n);
    print_stack(st);
    char *str = "(a+b)*(c+d)";

    printf("%s", infix_to_postfix(str));
}