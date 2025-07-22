#ifndef VECTOR_H_INCLUDED
#define VECTOR_H_INCLUDED

#include <stddef.h>
#include <string.h>
#include <stdlib.h>

#define CAP_INI 50

typedef struct
{
    void* vec;
    size_t tamElem;
    size_t cap;
    size_t ce;
}tVector;

void vectorInicializar(tVector* v, size_t tamElem);
void vectorRecorrer(tVector* v, void* params, void(*accion)(void*, void*));
int  vectorInsEnOrden(tVector* v, void* elem, int(*cmp)(const void*, const void*));
void vectorDestruir(tVector* v);
void vectorVaciar(tVector* v);
int vectorVacio(tVector* v);

#endif // VECTOR_H_INCLUDED
