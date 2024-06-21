#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

typedef struct node {
  int data;
  struct node *next;
} node;

node *createNode(int data) {
  node *new = (node *)malloc(sizeof(node));

  new->data = data;
  new->next = NULL;

  return new;
}

node *createList() {
  node *head = NULL;
  node *temp = NULL;

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

void printList(node *head) {
  node *temp = head;

  while (temp) {
    printf("%d->", temp->data);
    temp = temp->next;
  }
  printf("NULL\n");
}

#define size 100
int hash(int data) { return data % size; }

typedef struct Hnode {
  int key;
  int value;
  struct Hnode *next;
} Hnode;

typedef struct table {
  Hnode *table[size];

} Htable;

Htable *createTable() {
  Htable *newtable = (Htable *)calloc(1, sizeof(Htable));



  return newtable;
}

Hnode *createHnode(int key, int value) {
  Hnode *new = (Hnode *)malloc(sizeof(Hnode));

  new->key = key;
  new->value = value;
  new->next = NULL;
  return new;
}

void insert(Htable *table, int key, int value) {
  int index = hash(key);
  Hnode *current = table->table[index];

  if (!current) {
    table->table[index] = createHnode(key, value);
    return;
  }

  Hnode *prev = NULL;

  while (current) {
    if (current->key == key) {
      current->value = value;
      return;
    }
    prev = current;
    current = current->next;
  }

  prev->next = createHnode(key, value);

  return;
}

int get(Htable *table, int key) {

  int index = hash(key);

  Hnode *current = table->table[index];

  while (current) {
    if (current->key == key) {
      return current->value;
    }
    current = current->next;
  }

  return 0;
}

node *intersection(node *head1, node *head2) {

  node *temp1 = head1;
  node *temp2 = head2;

  node *newHead = NULL;
  node *tempHead = NULL;

  Htable *table = createTable();

  while (temp1) {

    insert(table, temp1->data, 1);

    temp1 = temp1->next;
  }

  while (temp2) {
    if (get(table, temp2->data) != 0) {
      if (!newHead) {
        newHead = createNode(temp2->data);
        tempHead = newHead;
      } else {
        tempHead->next = createNode(temp2->data);
        tempHead = tempHead->next;
      }
    }
    temp2 = temp2->next;
  }

  return newHead;
}

node *unionList(node *head1, node *head2) {

  node *temp1 = head1;
  node *temp2 = head2;

  node *inter = intersection(head1, head2);

  Htable *table = createTable();

  node *newhead = NULL;
  node *tempHead = NULL;
  while (inter) {
    insert(table, inter->data, 1);
    inter = inter->next;
  }

  while (temp1) {
    if (!newhead) {
      newhead = createNode(temp1->data);
      tempHead = newhead;
    } else {
      tempHead->next = createNode(temp1->data);
      tempHead = tempHead->next;
    }
    temp1 = temp1->next;
  }


  while (temp2) {
    if (get(table, temp2->data) == 0) {

        tempHead->next = createNode(temp2->data);
        tempHead = tempHead->next;

      
    }
    temp2 = temp2->next;
  }

  return newhead;
}

int main() {
  node *head1 = createList();
  printList(head1);
  node *head2 = createList();

  printList(head2);

  node *inter = intersection(head1, head2);

  printList(inter);

  node* uni = unionList(head1, head2);
  printList(uni);
}