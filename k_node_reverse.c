#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
  int data;
  struct Node *next;
} Node;

Node *createNode(int data) {
  Node *new = (Node *)malloc(sizeof(Node));
  new->data = data;
  new->next = NULL;

  return new;
}

Node *createList() {
  Node *head = NULL;

  Node *temp = NULL;

  while (1) {
    int n;
    scanf("%d", &n);
    if (n == -1) {
      break;
    }
    if (!head) {
      head = createNode(n);
      temp = head;
    } else {
      temp->next = createNode(n);
      temp = temp->next;
    }
  }

  return head;
}

void printList(Node *head) {
  Node *temp = head;

  while (temp) {
    printf("%d->", temp->data);
    temp = temp->next;
  }
  printf("NULL\n");
}

typedef struct pairNode {

  Node *head;
  Node *tail;

} pairNode;

pairNode *createPairNode(Node *head, Node *tail) {
  pairNode *new = (pairNode *)malloc(sizeof(pairNode));
  new->head = head;
  new->tail = tail;
  return new;
}

pairNode *reverse(Node *head, int k) {
  Node *current = head;
  Node *prev = NULL;
  Node *next = NULL;
  int i = 0;

  while ( current&&i < k) {
    next = current->next;
    current->next = prev;
    prev = current;
    current = next;
    i++;
  }


  return createPairNode(prev, current);
}

Node* Kreverse(Node* head, int k ){

    Node* newhead = NULL;
    Node* currtail = NULL;

    while(head){
            pairNode* temp = reverse(head, k);

            if(!newhead){
                newhead = temp->head;
            }

            else{
                currtail->next = temp->head;
            }
            currtail = head;
            head = temp->tail;

        
    }

    return   newhead;
}



int main() {
  Node *head = createList();
  printList(head);
  Node* head2 = Kreverse(head, 3);
  printList(head2);

}