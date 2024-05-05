#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum
{
    int_type,
    float_type,
    double_type,
    string_type
} type;

typedef struct Node
{
    type type;
    void *data;
    struct Node *next;
} Node;

Node *createNode(type t, void *data)
{
    Node *newNode = (Node *)malloc(sizeof(Node));

    switch (t)
    {
    case int_type:
        newNode->data = malloc(sizeof(int));
        *((int *)newNode->data) = *((int *)data);
        break;
    case float_type:
        newNode->data = malloc(sizeof(float));
        *((float *)newNode->data) = *((float *)data);
        break;
    case double_type:
        newNode->data = malloc(sizeof(double));
        *((double *)newNode->data) = *((double *)data);
        break;
    case string_type:
        newNode->data = malloc(strlen((char *)data) + 1);
        strcpy((char *)newNode->data, (char *)data);
        break;
    default:
        printf("Unsupported data type\n");
        exit(1);
    }

    newNode->type = t;
    newNode->next = NULL;
    return newNode;
}

void insertAtBeginning(Node **head, type t, void *data)
{
    Node *newNode = createNode(t, data);
    newNode->next = *head;
    *head = newNode;
}

void printList(Node *head)
{
    Node *temp = head;
    while (temp != NULL)
    {
        switch (temp->type)
        {
        case int_type:
            printf("%d  ", *((int *)(temp->data)));
            break;
        case float_type:
            printf("%f  ", *((float *)(temp->data)));
            break;
        case double_type:
            printf("%lf  ", *((double *)(temp->data)));
            break;
        case string_type:
            printf("%s  ", (char *)(temp->data));
            break;
        default:
            printf("type not supported\n");
            break;
        }
        temp = temp->next;
    }
}

void insertatEnd(Node **head, type t, void *data)
{
    Node *newNode = createNode(t, data);
    if (*head == NULL)
    {
        *head = newNode;
        return;
    }
    Node *current = *head;
    while (current->next != NULL)
    {
        current = current->next;
    }
    current->next = newNode;
}

Node *NodeOnIndex(Node *head, int index)
{
    int i = 0;
    Node *current = head;
    while (current != NULL && i < index)
    {
        current = current->next;
        i++;
    }
    return current;
}

void insertAtIndex(Node **head, int index, type t, void *data)
{
    if (index == 0)
    {
        insertAtBeginning(head, t, data);
        return;
    }

    Node *newNode = createNode(t, data);
    Node *prevNode = NodeOnIndex(*head, index - 1);
    if (prevNode == NULL)
    {
        printf("index out of size\n");
        exit(1);
    }
    newNode->next = prevNode->next;
    prevNode->next = newNode;
}

int main()
{
    Node *head = NULL;

    int intData = 10;
    float floatData = 20.5;
    double doubleData = 30.123;
    char *stringData = "google";

    insertAtBeginning(&head, int_type, &intData);
    insertAtBeginning(&head, float_type, &floatData);
    insertAtBeginning(&head, double_type, &doubleData);
    insertAtBeginning(&head, string_type, stringData);

    printList(head);
    printf("\n");
    insertatEnd(&head, int_type, &intData);

    insertAtIndex(&head, 2, int_type, &intData);

    printList(head);

    return 0;
}
