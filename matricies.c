#include <stdio.h>
#include <stdlib.h>
#include <limits.h> // for CHAR_MAX
#include <math.h>
#include <stdbool.h>

typedef double TYPE;

typedef struct mdarr
{
    int* shape;
    int* strides;
    int num_dim;
    int size;
    TYPE* data;
} mdarr;

void set_strides_c(mdarr* m, int* shape, int num_dim){
    m->strides[num_dim - 1] = 1;
    for(int i = num_dim - 2; i >= 0; i--){
        m->strides[i] = shape[i + 1] * m->strides[i + 1];
    }
}
void set_strides_f(mdarr* m, int* shape, int num_dim){
    m->strides[0] = 1;
    for(int i = 1; i < num_dim; i++){
        m->strides[i] = shape[i - 1] * m->strides[i - 1];
    }
}

void set_data(mdarr* m, TYPE* data, int length, int num_dim, int* strides){
    m->data = (TYPE*)malloc(length * sizeof(TYPE));
    for(int i = 0; i < length; i++){
        m->data[i] = data[i];
    }
}

mdarr* marr(int* shape, int num_dim, int size){
    mdarr* m = (mdarr*)malloc(sizeof(mdarr*));
    m->shape = shape;
    m->num_dim = num_dim;
    m->strides = (int*)malloc(num_dim * sizeof(int));
    set_strides_c(m, shape, num_dim);
    m->data = (TYPE*)malloc(size * sizeof(TYPE));
    return m;
}

mdarr* zeros(int* shape, int num_dim, int size){
    mdarr* m = (mdarr*)malloc(sizeof(mdarr*));
    m->shape = shape;
    m->num_dim = num_dim;
    m->strides = (int*)malloc(num_dim * sizeof(int));
    set_strides_c(m, shape, num_dim);
    m->data = (TYPE*)calloc(size, sizeof(TYPE));
    return m;
}

mdarr* copy(mdarr* m){
    mdarr* m_copy = marr(m->shape, m->num_dim, m->size);
    int size = m->size;
    for(int i = 0; i < size; i++){
        m_copy[i] = m[i];
    }
    return m_copy;
}

mdarr* add(mdarr** matrices, int num_of_mdarrs){
    int size = matrices[0]->size;
    mdarr* m = zeros(matrices[0]->shape, matrices[0]->num_dim, size);
    for(int i = 0; i < num_of_mdarrs; i++){
        for(int j = 0; j < size; j++){
            m->data[j] += matrices[i]->data[j];
        }
    }
    return m;
}

mdarr* scalar_prod(mdarr* m, TYPE scalar){
    for(int i = 0; i < m->size; i++){
        m->data[i] += m->data[i] * scalar;
    }
    return m;
}

void set(mdarr* m, int* target, TYPE value){
    int index = 0;
    for(int i = 0; i < m->num_dim; i++){
        index += target[i] * m->shape[i];
    }
    m->data[index] = value;
}
