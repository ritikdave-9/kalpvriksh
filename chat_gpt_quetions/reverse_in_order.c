#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
    int data;
    struct Node *next;
} Node;

typedef struct pair
{
    Node *first;
    Node *second;
} pair;
Node *createNode(int data)
{
    Node *newnode = (Node *)malloc(sizeof(Node));
    if(newnode==NULL){
        printf("cant allocate memory");
    }

    newnode->data = data;
    newnode->next = NULL;
    return newnode;
}
pair *createPair(Node *first, Node *second)
{
    pair *newpair = (pair *)malloc(sizeof(pair));
    if(newpair==NULL){
        printf("cant allocate memory");
    }
    newpair->first = first;
    newpair->second = second;
    return newpair;
}

Node *CreateList()
{

    Node *head = NULL;
    Node *temp = head;

    while (1)
    {
        int n;
        scanf("%d", &n);

        if (n == -1)
        {
            break;
        }
        if (!head)
        {
            head = createNode(n);
            temp = head;
        }
        else
        {
            temp->next = createNode(n);
            temp = temp->next;
        }
    }
    return head;
}

void printList(Node *head)
{
    Node *temp = head;
    while (temp)
    {
        printf("%d -> ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
}

pair *utils(Node *start, int k)
{

    Node *current = start;
    Node *prev = NULL;
    Node *next = NULL;
    int count = 0;

    while (current && count < k)
    {

        next = current->next;

        current->next = prev;
        prev = current;
        current = next;
        count++;
    }
    return createPair(prev, current);
}

Node *reverse(Node *head, int k)
{
    Node *Head_to_return = NULL;
    Node *current_tail = NULL;

    while (head)
    {
        pair *temp = utils(head, k);

        if (!Head_to_return)
        {
            Head_to_return = temp->first;
        }
        else
        {
            current_tail->next = temp->first;
        }

        current_tail = head;
        head = temp->second;
    }
    return Head_to_return;
}

int main()
{

    Node *list = CreateList();

    printList(list);

    list = reverse(list, 2);
    printf("\n");

    printList(list);

    while(list){
        Node* next = list->next;
        free(list);
        list=  next;
    }

}
