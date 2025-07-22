#ifndef VECTOR_H_INCLUDED
#define VECTOR_H_INCLUDED

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CAP_INI 20

#define OK 1
#define ERROR 0
#define ERROR_MEMORIA 0
#define ERROR_ARCHIVO 0
#define ERROR_VECTOR_VACIO 0

typedef void(*Accion)(void*,void*);
typedef int(*Cmp)(const void*, const void*);

typedef struct
{
    void* vec;
    size_t tamElem;
    size_t ce;
    size_t cap;
}tVector;

void vectorInicializar(tVector* v, size_t tamElem);
void vectorDestruir(tVector* v);
void vectorVaciar(tVector* v);
int  vectorRedimensionar(tVector* v, size_t nuevaCap);

int vectorRecorrer(tVector* v, void* params, Accion accion);
int vectorInsElemOrdenado(tVector* v, void* elem, Cmp cmp);
int vectorInsAlFinal(tVector* v, void* elem);
int vectorEliminarDuplicados(tVector* v, Cmp cmp);
int vectorBuscar(tVector* v, Cmp cmp, void* elem);
int vectorEliminarElemOrdenado(tVector* v, void* elem, Cmp cmp);

void vectorOrdenarQsort(tVector* v, Cmp cmp);
void vectorOrdenarBurbujeo(tVector* v, Cmp cmp);
void vectorOrdenarInsercion(tVector* v, Cmp cmp);

#endif // VECTOR_H_INCLUDED
