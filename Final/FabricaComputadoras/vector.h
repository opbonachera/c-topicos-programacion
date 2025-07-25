#ifndef VECTOR_H_INCLUDED
#define VECTOR_H_INCLUDED

#include "stdio.h"
#include "stddef.h"
#include "string.h"
#include "stdlib.h"

#define CAP_INI 50

#define OK 1
#define ERROR_MEMORIA 0
#define ERROR_ARCHIVO 0
#define ERROR 0

typedef struct
{
    void* vec;
    size_t tamElem;
    size_t cap;
    size_t ce;
}tVector;

typedef int(*Cmp)(const void*, const void*);
typedef void(*Actualizar)(void*, void*);
typedef void (*Imp)(void*);

void vectorDeArchivo(tVector* v, const char* nomArch, int cap_ini, size_t tamElem);
void vectorDestruir(tVector* v);
void vectorRecorrer(tVector* v, Imp imp);
int vectorRedimensionar(tVector* v, size_t nuevaCap);
int vectorGrabar(tVector* v, const char* nomArch);
int vectorOrdenar(tVector* v, int inicio, int fin, Cmp cmp);
int vectorEliminarDuplicados(tVector* v, Cmp cmp, Actualizar actualizar);
void intercambiar(void* e1, void* e2, size_t tamElem);

#endif // VECTOR_H_INCLUDED
