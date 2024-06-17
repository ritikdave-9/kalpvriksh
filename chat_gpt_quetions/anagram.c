#include<stdio.h>
#include<stdlib.h>

#include<string.h>

typedef struct Node{
    int key;
    char* array[20];
    int index;
    struct Node * next;

}Node;


#define size 100

Node * createNode(int key){
    Node*newnode = (Node*)malloc(sizeof(Node));
    newnode->key = key;
    newnode->index = 0;
    for(int i = 0;i<20;i++){
        newnode->array[i]=NULL;
    }


    newnode->next = NULL;
    return newnode;
}

int charsum(char* str){
    int sum = 0;

    while(*str!='\0'){
        sum+=*str;
        str++;
    }
    return sum;
}

typedef struct map{
    Node * table[size];
}map;



map* createmap(){
    map *newmap = (map*)malloc(sizeof(map));
    for(int i = 0;i<size;i++){
        newmap->table[i] = NULL ;
     }

           return newmap;

}

int hash(int key){
    int index = key%size;
    return index;
}

void put(map* mp , int key, char* value){

    int index = hash(key);

    Node*current = mp->table[index];
    if(!current){
        mp->table[index] = createNode(key);
        mp->table[index]->array[mp->table[index]->index] = strdup(value);
        mp->table[index]->index++;
        return ;
    }
    Node*prev = NULL;

    while(current){
        if(current->key == key){
            current->array[current->index] = strdup(value);
            current->index++;
            return;
        }
        prev = current;
        current = current->next;
    }

    prev->next = createNode(key);
    prev->next->array[prev->next->index] = strdup(value);
    (prev->next->index)++;
    return ;
    
}

void printMap(map*mp){
    int i = 0;
    while(i<size){
        Node* current = mp->table[i];
        while(current){
            int j = 0;
            while(j<current->index){
                printf("%s,",current->array[j]);
                j++;
            }
            current = current->next;
            printf("\n");
        }
        i++;
    }
}

// int get(map* mp,int key){
//     int index = hash(key);
//     Node *current = mp->table[index];

//     while(current){
//         if(current->key == key){
//             return current->value;
//         }
//         current = current->next;
//     }
//     return -1;
// }

void anagram(char ** arr ){

    int i = 0;

    char * temp = *arr;
    map *mp = createmap();

    while(arr[i]){
        int key = charsum(arr[i]);
        put(mp,key,arr[i]);
        i++;
        
    }
    printMap(mp);



    
}

int main(){
    map*mp = createmap();
    char* str[] = {"hello","llohe","ok","ko","kko","oko","olleh",NULL};
    anagram(str);
}

