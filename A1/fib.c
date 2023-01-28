#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
    if(fib_n == 0 && strcmp(argv[1], "0")!=0) return -1;

    if(fib_n < 0 || fib_n > 40){
        printf("Invalid Argument (0<=n<=40)\n");
        return -1;
    }
    
    long int prev1 = 0;
    long int prev2 = 1;
    long int curr = 0;
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

    if((fib_n+1)%5!=0){
        printf("\n");
    }

    return 0;
}