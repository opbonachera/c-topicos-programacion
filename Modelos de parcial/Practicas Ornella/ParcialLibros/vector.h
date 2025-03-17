#ifndef VECTOR_H_INCLUDED
#define VECTOR_H_INCLUDED

#include <stdlib.h>
#include <stdio.h>

typedef struct
{
    size_t cap;
    size_t ce;
    size_t tamElemento;
    void* v;
}Vector;

int inicializarVector(Vector* vector, size_t tamElemento, size_t ce);
int vectorCrearDeArchivo(Vector* vector, const char* nomArch, size_t tamElemento);
int guardarVectorArchivo(Vector* vector, const char* nomArch);
int destruirVector(Vector* vector);
int redimensionarVector(Vector* vector, int nuevaCap);


#endif // VECTOR_H_INCLUDED
