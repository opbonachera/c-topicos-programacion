#ifndef ARCHIVOS_H_INCLUDED
#define ARCHIVOS_H_INCLUDED

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#define OK 0
#define ERROR_RESERVA_MEMORIA 1

typedef struct
{
    void*  v;
    size_t cap;
    size_t ce;
    size_t tamElemento;
}Vector;

typedef void (*Cmp)(void* e1, void* e2);

bool inicializarVector(Vector* vector, size_t cap, size_t tamElemento);
bool destruirVector(Vector* vector);
bool vectorDeArchivo(Vector* vector, size_t tamElemento, const char* nombreArchivo);

int buscarElemento(Vector* vector, void* elemento, Cmp cmp);
int buscarVectorOrdenado(Vector* vector, void* elemento, Cmp cmp);

#endif