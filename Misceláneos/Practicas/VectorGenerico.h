#ifndef VECTOR_GENERICO_INCLUDED
#define VECTOR_GENERICO_INCLUDED

#define OK 0
#define ERROR_DE_MEMORIA 1


#define FACTOR_REDIMENSION 1.5
#define CANT_ELEMENTOS 5

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct
{
    size_t ce;
    size_t cap;
    size_t tamElemento;
    int*   vec;
}VectorGenerico;

int inicializarVector(VectorGenerico* Vector);
int inicializarValoresEnteros(VectorGenerico* Vector);
int imprimirVectorEnteros(VectorGenerico* vector);
int destruirVector(VectorGenerico* Vector);


#endif // VECTOR_GENERICO_INCLUDED
