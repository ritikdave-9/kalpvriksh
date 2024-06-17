#include <stdio.h>
#include <stdlib.h>

#define SIZE 100

typedef struct treeNode {
    int data;
    struct treeNode *left;
    struct treeNode *right;
} treeNode;

treeNode* createTreeNode(int data) {
    treeNode* newNode = (treeNode*)malloc(sizeof(treeNode));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

typedef struct pair {
    int hd;
    treeNode* node;
} pair;

pair* createPair(int hd, treeNode* node) {
    pair* newPair = (pair*)malloc(sizeof(pair));
    newPair->hd = hd;
    newPair->node = node;
    return newPair;
}

typedef struct node {
    pair* data;
    struct node* next;
} node;

node* createNode(pair* data) {
    node* newNode = (node*)malloc(sizeof(node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

typedef struct Queue {
    node* front;
    node* end;
} Queue;

Queue* createQueue() {
    Queue* q = (Queue*)malloc(sizeof(Queue));
    q->end = NULL;
    q->front = NULL;
    return q;
}

void enQueue(Queue* q, pair* data) {
    node* newNode = createNode(data);
    if (q->front == NULL) {
        q->front = newNode;
        q->end = newNode;
        return;
    }
    q->end->next = newNode;
    q->end = newNode;
}

pair* deQueue(Queue* q) {
    if (q->front == NULL) {
        return NULL;
    }
    node* temp = q->front;
    pair* data = temp->data;
    q->front = temp->next;
    if (q->front == NULL) {
        q->end = NULL;
    }
    free(temp);
    return data;
}

typedef struct hashNode {
    int key;
    node* value;
    struct hashNode* next;
} hashNode;

hashNode* createHashNode(int key, node* value) {
    hashNode* new = (hashNode*)malloc(sizeof(hashNode));
    new->key = key;
    new->value = value;
    new->next = NULL;
    return new;
}

typedef struct Htable {
    hashNode* table[SIZE];
} Htable;

int hash(int key) {
    if (key < 0) {
        return (SIZE + key) % SIZE;
    } else {
        return key % SIZE;
    }
}

void insert_in_table(Htable* table, int key, node* value) {
    int index = hash(key);
    hashNode* current = table->table[index];
    if (!current) {
        table->table[index] = createHashNode(key, value);
        return;
    }
    while (current->next) {
        if (current->key == key) {
            current->value = value;
            return;
        }
        current = current->next;
    }
    if (current->key == key) {
        current->value = value;
    } else {
        current->next = createHashNode(key, value);
    }
}

node* get_hash_table(Htable* table, int key) {
    int index = hash(key);
    hashNode* current = table->table[index];
    while (current) {
        if (current->key == key) {
            return current->value;
        }
        current = current->next;
    }
    return NULL;
}

void printVerticalOrder(treeNode* root) {
    if (root == NULL) {
        return;
    }
    Queue* q = createQueue();
    Htable* ht = (Htable*)malloc(sizeof(Htable));
    for (int i = 0; i < SIZE; i++) {
        ht->table[i] = NULL;
    }

    enQueue(q, createPair(0, root));

    while (q->front != NULL) {
        pair* p = deQueue(q);
        int hd = p->hd;
        treeNode* node = p->node;

        node* currentNodeList = get_hash_table(ht, hd);
        if (currentNodeList == NULL) {
            currentNodeList = createNode(createPair(hd, node));
            insert_in_table(ht, hd, currentNodeList);
        } else {
            node* temp = currentNodeList;
            while (temp->next != NULL) {
                temp = temp->next;
            }
            temp->next = createNode(createPair(hd, node));
        }

        if (node->left != NULL) {
            enQueue(q, createPair(hd - 1, node->left));
        }
        if (node->right != NULL) {
            enQueue(q, createPair(hd + 1, node->right));
        }

        free(p);
    }

    for (int i = -SIZE / 2; i <= SIZE / 2; i++) {
        node* n = get_hash_table(ht, i);
        while (n != NULL) {
            printf("%d ", n->data->node->data);
            n = n->next;
        }
    }
    printf("\n");
}

int main() {
    treeNode* root = createTreeNode(1);
    root->left = createTreeNode(2);
    root->right = createTreeNode(3);
    root->left->left = createTreeNode(4);
    root->left->right = createTreeNode(5);
    root->right->left = createTreeNode(6);
    root->right->right = createTreeNode(7);

    printf("Vertical Order Traversal is:\n");
    printVerticalOrder(root);

    return 0;
}
