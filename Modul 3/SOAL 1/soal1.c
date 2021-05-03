#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

#define MAX 500

int sortArg[100];
int count;
int status;

int multiply(int x, int res[], int res_size) {
    int carry = 0;  // Initialize carry
 
    // One by one multiply n with individual digits of res[]
    for (int i = 0; i < res_size; i++) {
        int prod = res[i] * x + carry;
 
        // Store last digit of 'prod' in res[] 
        res[i] = prod % 10; 
 
        // Put rest in carry
        carry  = prod / 10;   
    }
 
    // Put carry in res and increase result size
    while (carry) {
        res[res_size] = carry % 10;
        carry = carry / 10;
        res_size++;
    }
    return res_size;
}

void* faktorial(void *arg) {
    int res[MAX];
    int res_size = 1;
    int x = sortArg[count];
    res[0] = 1;

    for (int y = 2; y <= x; y++) {
        res_size = multiply(y, res, res_size);
    }

    printf("%d! = ", sortArg[count]);

    for (int i = res_size - 1; i >= 0; i--) {
        printf("%d", res[i]);
    }

    puts("");
}

int compare (const void * a, const void * b) {
    return ( *(int*)a - *(int*)b );
}

int main(int argc, char *argv[]) {

    pthread_t tid[argc];
    int x[argc + 1];

    for (int i = 0; i < argc - 1; i++) {
        x[i] = atoi(argv[1 + i]);
    }
    
    qsort (x, argc - 1, sizeof(int), compare);
    
    for (int i = 0; i < argc - 1; i++) {
        sortArg[i] = x[i];
    }
    
    for (int i = 0; i < argc - 1; i++) {
        count = i;
 
        pthread_create(&(tid[i]), NULL, faktorial, NULL);
        pthread_join(tid[i], NULL);
    }
    
    return 0;
}