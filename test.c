#include <stdio.h>
#include <stdlib.h>
#include <limits.h> // for CHAR_MAX
#include <math.h>
#include <stdbool.h>
#include "matricies.c"

int main(void) 
{
    int shape[] = {4,5,6};
    int size = 30;
    int num_dim = 3;
    mdarr* m = marr(shape, num_dim, size);
    printf("%d\n", m->strides[0]);
    printf("%d\n", m->strides[1]);
    printf("%d\n", m->strides[2]);
    free(m);
    return 0;
}

