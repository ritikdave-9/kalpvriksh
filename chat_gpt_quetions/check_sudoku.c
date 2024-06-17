#include<stdio.h>
#include<stdlib.h>


int table[10] = {0};

void reset(int *arr){
    for(int i = 0;i<9;i++){
        arr[i] = 0;
    }
}

int checkValid(int board[9][9]){

    for(int i = 0;i<9;i++){
        for(int j = 0;j<9;j++){
        table[board[i][j]] = 1;
        }

        for(int k = 1;k<10;k++){
            if(table[k]==0){
                printf("invalid");
                return 0;
                
            }
        }
    reset(table);

        
    }
    

    for(int i = 0;i<9;i++){
        for(int j = 0;j<9;j++){

            table[board[j][i]] = 1;


        }

         for(int k = 1;k<10;k++){
            if(table[k]==0){
                printf("invalid");
                return 0;
                
            }
        }

        reset(table);

    }
   
    
    for(int i = 0;i<9;i+=3){
        for(int j = i;j<i+3;j++){
            table[board[i][j]] = 1;
        }
        for(int k = 1;k<10;k++){
            if(table[i]==0){
                printf("invalid");
                return 0;
                
            }
        }

        reset(table);
    }

    return 1;

}

int main(){
     int board[9][9] = {
        {5, 3, 4, 6, 7, 8, 9, 1, 2},
        {6, 7, 2, 1, 9, 5, 3, 4, 8},
        {1, 9, 8, 3, 4, 2, 5, 6, 7},
        {8, 5, 9, 7, 6, 1, 4, 2, 3},
        {4, 2, 6, 8, 5, 3, 7, 9, 1},
        {7, 1, 3, 9, 2, 4, 8, 5, 6},
        {9, 6, 1, 5, 3, 7, 2, 8, 4},
        {2, 8, 7, 4, 1, 9, 6, 3, 5},
        {3, 4, 5, 2, 8, 6, 1, 7, 9}
    };

    



    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            printf("%d ", board[i][j]);
        }
        printf("\n");
    }

            printf("%d",checkValid(table));


    return 0;
    
    

}


