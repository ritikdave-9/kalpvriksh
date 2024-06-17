#include<stdio.h>
#include<stdlib.h>


typedef struct Node{
    int key;
    int value;
    struct Node * next;
}Node;

Node*createNode(int key, int value){
    Node*newnode = (Node*)malloc(sizeof(Node));
    newnode->key = key;
    newnode->value = value;
    newnode->next =NULL;
    return newnode;

}
#define size 100
typedef struct map
{
    Node* table[size];
}map;
int hash(int key){
    return key%size;
}
void put(map* mp, int key, int value){

    int index = hash(key);

    Node*current = mp->table[index];

    if(!current){    
        mp->table[index] = createNode(key,value);
        return ;
    }
    Node* prev = NULL;
    while(current){
        if(current->key == key){
            current->value = value;
            return ;
        }
        prev = current;
        current = current->next;

    }
    prev->next = createNode(key,value);

}

int get(map*mp,int key){
    int index  = hash(key);
    Node*current = mp->table[index];
    while (current)
    {
        if(current->key==key){
            return current->value;
        }
        current = current->next;
    }

    return -1;
    
}

int * twosum(int *arr,int k,int n){
    int *ans = (int*)malloc(sizeof(int)*2);
    map* mp = (map*)malloc(sizeof(map));
    for(int i = 0;i<size;i++){
        mp->table[i] = NULL;
    }
    for(int i = 0;i<n;i++){
        int x = get(mp,arr[i]);

        if(x!=-1){
            put(mp,arr[i],x+1);
        }
        else{
            put(mp,arr[i],1);
        }
        
    }

    for(int i = 0;i<n;i++){
        int x = get(mp,k-arr[i]);
        if(x!=-1){
            if(arr[i]==k-arr[i]&&x==1){
                return NULL;

            }
            ans[0] = arr[i];
            ans[1] = k-arr[i];
            return ans;
            
        }
    }

    return NULL;


}

int main(){
    int arr[] = {1,2,3,5,6};
    int k = 8;
    int *pair = twosum(arr,10,6);

    if(pair!=NULL){
    printf("%d, %d",pair[0],pair[1]);

    }
    else{
        printf("%d",-1);
    }


}


