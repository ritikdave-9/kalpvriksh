#include <cstddef>
#include <stdio.h>
#include <stdlib.h>

typedef struct node {
  int data;
  struct node *next;
} node;

node *createNode(int data) {
  node *newnode = (node *)malloc(sizeof(node));

  newnode->data = data;
  newnode->next = NULL;

  return newnode;
}

node *createList() {
  node *head = NULL;
  node *current = NULL;

  while (1) {
    int n;
    scanf("%d", &n);

    if (n == -1) {
      return head;
    }

    node *newnode = createNode(n);

    if (!head) {
      head = newnode;
      current = newnode;

    } else {
      current->next = newnode;
      current = newnode;
    }
  }

  return head;
}

void printList(node *head) {
  node *temp = head;
  printf("\n");

  while (temp) {
    printf("%d -> ", temp->data);
    temp = temp->next;
  }

  printf("NULL\n");
}


node* merge(node* head1,node* head2){
    node* temp1 = head1;
    node* temp2 = head2;

    node* newHead = NULL;
    node* current = NULL;

    while(temp1&&temp2){

        if(temp1->data<temp2->data){

            if(!newHead){
                newHead = temp1;
                current = newHead;
                
            }
            else {
            current->next = temp1;
            current = current->next;
            }
            temp1 = temp1->next;
        }
        else {
            if(!newHead){
                newHead = temp2;
                current = newHead;
                
            }
            else {
            current->next = temp2;
            current = current->next;
            }
            temp2 = temp2->next;
        
        }

    
    }

    while (temp1) {
        current->next = temp1;
        temp1 = temp1->next;
        current = current->next;
    
    }
    while (temp2) {
        current->next = temp2;
        temp2 = temp2->next;
        current = current->next;
    
    }

    return newHead;
}


int main(){
    node* head1 = createList();
    node* head2 = createList();

    node* m =  merge(head1, head2);
    printList(m);
}