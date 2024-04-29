#include <stdio.h>
#include <stdlib.h>


typedef struct node {
    int data;
    struct node *prev;
    struct node *next;
} Node;


Node *createNode(int data) {
    Node *newNode = (Node *)malloc(sizeof(Node));
   
    newNode->data = data;
    newNode->prev = NULL;
    newNode->next = NULL;
    return newNode;
}


void insertAtStart(Node **head, int data) {
    Node *newNode = createNode(data);
    if (*head == NULL) {
        *head = newNode;
    } else {
        newNode->next = *head;
        (*head)->prev = newNode;
        *head = newNode;
    }
}


void insertAtEnd(Node **head, int data) {
    Node *newNode = createNode(data);
    if (*head == NULL) {
        *head = newNode;
    } else {
        Node *tmp = *head;
        while (tmp->next != NULL) {
            tmp = tmp->next;
        }
        tmp->next = newNode;
        newNode->prev = tmp;
    }
}


void insertAtIndex(Node **head, int data, int index) {
   
    if (index == 0) {
        insertAtStart(head, data);
        return;
    }
    Node *newNode = createNode(data);
    Node *temp = *head;
    int i = 0;
    while (temp != NULL && i < index - 1) {
        temp = temp->next;
        i++;
    }
    if (temp == NULL) {
        printf("Index out of range");
        return;
    }
    newNode->next = temp->next;
    newNode->prev = temp;
    if (temp->next != NULL)
        temp->next->prev = newNode;
    temp->next = newNode;
}


void deleteAtStart(Node **head) {
    if (*head == NULL) {
        printf("empty\n");
        return;
    }
    Node *temp = *head;
    *head = (*head)->next;
    if (*head != NULL)
        (*head)->prev = NULL;
    free(temp);
}


void deleteAtEnd(Node **head) {
    if (*head == NULL) {
        printf("empty\n");
        return;
    }
    Node *temp = *head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    if (temp->prev != NULL)
        temp->prev->next = NULL;
    free(temp);
}


void deleteAtIndex(Node **head, int index) {
    if (*head == NULL) {
        printf("empty\n");
        return;
    }
    if (index < 0) {
        printf("Invalid  index\n");
        return;
    }
    if (index == 0) {
        deleteAtStart(head);
        return;
    }
    Node *temp = *head;
    int i = 0;
    while (temp != NULL && i < index) {
        temp = temp->next;
        i++;
    }
    if (temp == NULL) {
        printf("Index out of range\n");
        return;
    }
    temp->prev->next = temp->next;
    if (temp->next != NULL)
        temp->next->prev = temp->prev;
    free(temp);
}


void printList(Node *head) {
    printf("List: ");
    while (head != NULL) {
        printf("%d ", head->data);
        head = head->next;
    }
    printf("\n");
}

int main() {
    Node *head = NULL;

    
    insertAtStart(&head, 10);
    insertAtEnd(&head, 20);
    insertAtIndex(&head, 15, 1); 

    
    printList(head);

    
    deleteAtStart(&head);
    deleteAtIndex(&head, 1); 
    deleteAtEnd(&head);

    
    printList(head);

    return 0;
}
