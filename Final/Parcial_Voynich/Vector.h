#ifndef VECTOR_H_INCLUDED
#define VECTOR_H_INCLUDED

#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define CAP_INI 50

#define OK 1
typedef struct
{
    void* vec;
    size_t ce;
    size_t cap;
    size_t tamElem;
}tVector;

void vectorInicializar(tVector* v, size_t tamElem);
void vectorDestruir(tVector* v);
int  vectorInsertarElemOrdenado(tVector* v, void* dato, int(*cmp)(const void*, const void*));
int  vectorBusquedaBinaria(tVector* v, void* dato, int(*cmp)(const void*, const void*));
void vectorRecorrer(tVector* v, void* params, void(*accion)(void*, void*));
void* obtenerElementoEnIndiceVector(tVector* v, int indice);

#endif // VECTOR_H_INCLUDED
