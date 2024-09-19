#ifndef VECTOR_GENERICO_INCLUDED
#define VECTOR_GENERICO_INCLUDED

#define OK 0
#define ERROR_DE_MEMORIA 1


#define FACTOR_REDIMENSION 1.5


#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    size_t ce;
    size_t cap;
    size_t tamElemento;
    void**  vec;
}VectorGenerico;

int inicializarVector(VectorGenerico* Vector);
int inicializarValoresVector(VectorGenerico* Vector);
int imprimirVectorEnteros(VectorGenerico* vector);
int destruirVector(VectorGenerico* Vector);


#endif // VECTOR_GENERICO_INCLUDED
