#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

void correctness();
void performance();

int main(){
    printf("0 -- correctness testing\n1 -- performance testing\n2 -- quit\n");

    int choice;
    scanf("%d", &choice);

    if(choice == 0){
        correctness();
    } else if (choice == 1){
        performance();
    }

    return 0;
}

void printarr(int *a, int n){
    for(int i = 0; i < n; i++){
        printf("%d ", *(a+i));
    }
    printf("\n");
}

void swap(int *p1, int *p2){
    int temp = *p2;
    *p2 = *p1;
    *p1 = temp;
}

void selection_sort(int *a)
{
    // your implementation
    int right = 9;
    int left = 0;
    int i, j, k;
    int n = right - left + 1;
    for (i = 0; i < n; ++i) {
        k = i;
        for(j = i+1; j < n ; ++j) {
            if (*(a+j) < *(a+k)) {
                k = j;
            }
        }
        if (i != k) {
            //swap the values at a+k and a+i
            swap(a+k, a+i);
        }
    }
}

void quick_sort(int *a, int left, int right){

    // your implementation
    int key,i,j,k;
    if( left < right ) {
        k = (left+right)/2;
        key = *(a+k); // use *(a+k) as the pivot
        // split a[left...right] that element at j is equal to key
        // elements from left to j-1 are less or equal to key
        // elements from j+1 to right are bigger than key

        i = left-1;
        j = right+1;
        int loop = 1;
        while(loop){
            do{
                i++;
            } while(*(a+i) < key);

            do{
                j--;
            } while(*(a+j) > key);

            if(i>= j){
                loop = 0;
            } else {
                //printf("%d %d", *(a+i), *(a+j));
                swap(a+i, a+j);
            }
        }

        quick_sort(a, left, j);
        quick_sort(a, j+1, right);
    }
}

void correctness(){
    int n = 10;

    srand(time(NULL));
    int* a;
    a = (int*)malloc(n*sizeof(int));
    for (int i = 0; i < n; i++){
        int random_number = rand() % 100 + 1;
        a[i] = random_number;
    }

    printf("Randomly generated array of length 10 is\n");
    printarr(a, n);

    int* b;
    b = (int*)malloc(n*sizeof(int));
    memcpy(b, a, n*sizeof(int));
    
    selection_sort(b);
    printf("sorted by selection sort:\n");
    printarr(b, n);

    //reset arr
    memcpy(b, a, n*sizeof(int));

    quick_sort(b, 0, n-1);
    printf("sorted by quick sort:\n");
    printarr(b, n);

    int sum = 0;
    for(int i = 0; i < n; i++){
        sum += a[i];
    }
    printf("Average is:%.2f\n", (float)sum/(float)n);
}

void performance(){
    int n = 50000;

    srand(time(NULL));
    int* a;
    a = (int*)malloc(n*sizeof(int));
    for (int i = 0; i < n; i++){
        int random_number = rand() % 50000 + 1;
        a[i] = random_number;
    }

    int* b;
    b = (int*)malloc(n*sizeof(int));
    memcpy(b, a, n*sizeof(int));


    clock_t start, end;
    double time1, time2;

    start = clock();
    selection_sort(b);
    end = clock();
    time1 = (double)(end - start) / CLOCKS_PER_SEC;
    printf("It takes %f seconds to sort the array by selection sort.\n", time1);

    //reset arr
    
    memcpy(b, a, n*sizeof(int));

    start = clock();
    quick_sort(b, 0, n-1);
    end = clock();
    time2 = (double)(end - start) / CLOCKS_PER_SEC;
    printf("It takes %f seconds to sort the array by quick sort.\n", time2);

    //BRO NOW IM FEELIN HELLA RETARDED BECAUSE QUICK IS NOW SLOWER THAN SELECT WHAAAT HAHAHA           ..fuck
    //im gonna kms
}