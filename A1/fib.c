#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){

    if(argc > 2){
        printf("Too many arguments supplied.\n");
        return -1;
    } 
    if(argc <= 1){
        printf("One argument expected.\n");
        return -1;
    } 

    int fib_n = atoi(argv[1]);

    int prev1 = 0;
    int prev2 = 1;
    int curr = 0;
    for(int i = 0; i <= fib_n; i++){
        if(i<=1){
            curr = i;
        } else {
            curr = prev1 + prev2;
            prev1 = prev2;
            prev2 = curr;
        }
        printf("%12ld", curr);
        if((i+1)%5==0){
            printf("\n");
        }
    }

    return 0;
}