#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int max(int n){
    int ones = 0;
    int zero = 0;

    while(n){
        if(n&1){
            ones++;

        }
        else {
        zero++;
        }
    n>>=1;
    }

    int ans = 0;

    while(ones){
        ans<<=1;
        ans|=1;
        ones--;
    }
    while (zero) {
        ans<<=1;
        zero--;
    
    }

    return ans;

    

}

int main(){
    int n = 10;
    int m = max(n);
    printf("%d",m);
}
