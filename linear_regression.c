#include <stdio.h>
#include <stdlib.h>
#include <limits.h> // for CHAR_MAX
#include <math.h>
#include <stdbool.h>
#include "ops.c"

TYPE* randArray(int size, int min, int max){
    srand(time(NULL));
    TYPE* array = malloc(size * sizeof(TYPE));
    for(int i = 0; i < size; i++){
        array[i] = (rand() % (max - min + 1)) + min; 
    }
    return array;
}

int main(void) 
{
    TYPE* test = randArray(500000, 0, 2);
    matrix* m = toMatrix(test, 1000, 500, false);
    matrix* mt = toMatrix(test, 1000, 500, true);
    
    
    clock_t start, end;
    start = clock();
    matrix* prod = dot(m, mt);
    end = clock();
    printf("The duration in seconds since the program was launched: %f\n", ((double)(end-start))/CLOCKS_PER_SEC);
    //show(prod);

    free(m);
    free(mt);
    free(prod);

    return 0;
}

