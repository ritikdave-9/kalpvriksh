#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int data;
    struct node *next;
} Node;

Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

void insertAtStart(Node **headref, int data) {
    Node* newNode = createNode(data);
    newNode->next = *headref;
    *headref = newNode;
}

void insertAtEnd(Node** headRef, int data) {
    Node* newNode = createNode(data);
    if (*headRef == NULL) {
        *headRef = newNode;
        return;
    }
    Node* temp = *headRef;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = newNode;
}

void insertAtMiddle(Node** headref, int data, int position) {
    Node *newNode = createNode(data);
    if (*headref == NULL || position <= 1) {
        newNode->next = *headref;
        *headref = newNode;
        return;
    }
    int count = 1;
    Node* current = *headref;
    while (current->next != NULL && count < position - 1) {
        current = current->next;
        count++;
    }
    newNode->next = current->next;
    current->next = newNode;
}

void DeleteStart(Node **headref) {
    if (*headref == NULL) {
        printf("Empty list\n");
        return;
    }
    *headref = (*headref)->next;
    printf("Deleted from start\n");
}

void DeleteEnd(Node **headref) {
    if (*headref == NULL) {
        printf("Empty list\n");
        return;
    }
    Node* current = *headref;
    if (current->next == NULL) {
        *headref = NULL;
        free(current);
        printf("Deleted from end\n");
        return;
    }
    while (current->next->next != NULL) {
        current = current->next;
    }
    free(current->next);
    current->next = NULL;
    printf("Deleted from end\n");
}

void DeleteMid(Node **headref, int position) {
    if (*headref == NULL) {
        printf("Empty list\n");
        return;
    }
    Node* current = *headref;
    if (position <= 1) {
        *headref = current->next;
        free(current);
        printf("Deleted from middle\n");
        return;
    }
    int count = 1;
    while (current->next != NULL && count < position - 1) {
        current = current->next;
        count++;
    }
    if (current->next == NULL) {
        printf("Invalid position \n");
        return;
    }
    Node* temp = current->next;
    current->next = temp->next;
    free(temp);
    printf("Deleted from middle\n");
}

void printLinkedList(Node* head) {
    Node* temp = head;
    while (temp != NULL) {
        printf("%d -> ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
}

int ElementOnIndex(Node **headref, int index){
    Node * current = *headref;

    int count = 1;

    while(count<index&&current!=NULL){
        current = current->next;


    }
     if (current == NULL) {
        printf("out of range\n");
        return -1;
    }
    return current->data;

}

int main() {
    Node* head = NULL;

    
    insertAtStart(&head, 2);
   
    insertAtStart(&head, 1);

 insertAtEnd(&head, 4);
   
    insertAtEnd(&head, 5);
    
    insertAtMiddle(&head, 3, 3);
    
     printf("Linked List: ");
    
    printLinkedList(head);

    DeleteStart(&head);
   
    printf("After deletion from start: ");
    printLinkedList(head);

    int x = ElementOnIndex(&head,1);
    printf("%d\n",x);

    
    DeleteMid(&head, 3);
    printf("After deletion from midle:");
    printLinkedList(head);

    
    DeleteEnd(&head);
    printf("After deletion from end:");
    printLinkedList(head);

    return 0;
}
