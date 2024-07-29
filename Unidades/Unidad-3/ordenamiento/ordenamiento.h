#ifndef ORDENAMIENTO_H_INCLUDED
#define ORDENAMIENTO_H_INCLUDED

typedef int (*Cmp)(const void*,  const void*);
typedef struct
{
    void *base;
    int ce;
    size_t tamElem;
    int cap;
}t_lista;

void qsort(
           void *base,
           size_t nItems,
           size_t size,
           int int (*Cmp)(const void*,  const void*)
           );
int burbujeoInt(int *vec, const int ce);
int printVector(int* vec, const int ce);
int intercambiar(int* x, int* y);

#endif // ORDENAMIENTO_H
