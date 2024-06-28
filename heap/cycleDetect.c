#include <asm-generic/errno.h>
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

int detectCycle(node* head){
    node* slow = head;
    node* fast = head;

    while (fast&&fast->next) {
        slow = slow->next;
        fast = fast->next->next;
        if(slow == fast){
            return 1;
        }
       
    
    }
    return 0;
}



int main(){
    node* head1 = createList();
   
}