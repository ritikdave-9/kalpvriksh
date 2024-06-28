#include<stdio.h>
#include<stdlib.h>

#define size 100

typedef struct hashnode
{
    int key;
    int value;
    struct hashnode* next;
}hashnode;

hashnode* createHashNode(int key, int value){
    hashnode* newhnode = (hashnode*)malloc(sizeof(hashnode));
    newhnode->key = key;
    newhnode->value = value;
    newhnode->next =    NULL;
    return newhnode;
}

typedef struct hashTable{
    hashnode * table[size];

}hashTable;

hashTable* createTable(){
    hashTable* newtable = (hashTable*)malloc(sizeof(hashTable));
    for(int i = 0;i<size;i++){
        newtable->table[i]=NULL;
    }

    return newtable;
}

int hash(int key){
    return key% size;
}

void insertTable(hashTable* table, int key, int value){

    int index = hash(key);

    hashnode* current = table->table[index];

    if(!current){
        table->table[index] = createHashNode(key,value);
        return;
    }
    hashnode* prev = NULL;

    while(current){
        if(current->key==key){
            current->value = value;
            return ;
        }
        prev = current;
        current = current->next;
    }

    prev->next = createHashNode(key,value);



}

int getTable(hashTable* table, int key){
    int index = hash(key);
    hashnode* current = table->table[index];

    while (current)
    {
        if(current->key==key){
            return current->value;
        }
        current = current->next;
    }

    return 0;
    
}




typedef struct node{
    int coff;
    int power;
    struct node* next;
}node;

node* createNode(int coff, int power){
    node* newnode = (node*)malloc(sizeof(node));
    newnode->coff = coff;
    newnode->power = power;
    newnode->next = NULL;
    return newnode;
}

void deleteTable(hashTable* table){
    for(int i = 0;i<size;i++){
        hashnode* current = table->table[i];

        while(current){
            hashnode* temp = current;
            current = current->next;
            free(temp);
            
            
        }
    }
}

node* createList(){
    node* head = NULL;
    node* current = NULL;
    int i = 1;

    while(1){
        int coff;
        int power;
        printf("enter coefficient and power for Node %d and -1 -1 To stop insertion : ",i);
        scanf("%d%d",&coff,&power);

        if(coff==-1){
            break;
        }
        node* newnode  = createNode(coff,power);
        if(!head){
            head = newnode;
            current = newnode;
        }
        else{
            current->next = newnode;
            current = newnode;
        }
    }

    return head;

}

void printList(node* head){
    node* current = head;
        printf("\n");

    while(current){
        printf("%d, %d -> ",current->coff,current->power);
        current = current->next;
    }
    printf("NULL\n");
}

node* evaluate(node* head1,node* head2){
    node* temp1 = head1;
    node* temp2 = head2;

    hashTable* table = createTable();

    node* newHead = NULL;
    node* current = NULL;

    while (temp1)
    {
        insertTable(table,temp1->power,(getTable(table,temp1->power)+temp1->coff));
        temp1 = temp1->next;
        
    }

    while (temp2)
    {
        insertTable(table,temp2->power,(getTable(table,temp2->power)+temp2->coff));
        temp2 = temp2->next;
    }


    for(int i = 100;i>=0;i--){
        int coff = getTable(table,i);
        if(coff){
            node* newnode = createNode(coff,i);

            if(!newHead){
                newHead = newnode;
                current = newHead;

            }
            else{
                current->next = newnode;
                current = current->next;
            }
        }
    }

    deleteTable(table);

    return newHead;


    

    
    

}

int main(){
    printf("\nenter list 1\n\n");

    node* head1= createList();
    printList(head1);
     printf("\nenter list 2\n\n");

    node* head2= createList();
    printList(head2);

    
    printf("\nThe solution is :\n");

    node* ans = evaluate(head1,head2);
    printList(ans);

}
