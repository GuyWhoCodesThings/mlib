#include <stdio.h>
#include <stdlib.h>
#include <limits.h> // for CHAR_MAX
#include <time.h>
#include <stdbool.h>


typedef double TYPE;
#define MAX_VAL 1
#define MIN_VAL -1

typedef struct matrix
{
    int row;
    int col;
	bool transposed;
    TYPE* data;
} matrix;

matrix* createMatrix(int row, int col, bool transposed){

	matrix* m = malloc(sizeof(matrix*));
	m->row = row;
	m->col = col;
	m->transposed = transposed;
	m->data = calloc(row * col, sizeof(TYPE));
	return m;
}
matrix* toMatrix(TYPE* array, int row, int col, bool transposed){
	matrix* m = createMatrix(row, col, transposed);
	for(int i = 0; i < row * col; i++){
		m->data[i] = array[i];
	}
	return m;
}

void show(matrix* m){
	int row = m->row;
	int col = m->col;
	if(m->transposed ^ 1){
		for(int i = 0; i < row; i++){
			printf("[");
			for(int j = 0; j < col; j++){
				printf("%f,", m->data[i * col + j]);
			}
			printf("]\n");
		}
	} else {
		for(int i = 0; i < col; i++){
			printf("[");
			for(int j = 0; j < row; j++){
				printf("%f,", m->data[j * col + i]);
			}
			printf("]\n");
		}
	}
}
// yxd yxd
// [0,1,2]  [0,1]
// [3,4,5]  [2,3]
//			[4,5]


matrix* dot(matrix* m, matrix* n){

	if(n->transposed && !m->transposed){
		matrix* res = createMatrix(m->row, n->row, false);
		for(int k = 0; k < m->row * n->col; k++){
			res->data[k / m->col] += m->data[k] * n->data[k];
		}
		return res;
	}
	return NULL;
	//xTy = yTx
	
}
