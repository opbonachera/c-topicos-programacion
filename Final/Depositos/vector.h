#ifndef VECTOR_H_INCLUDED
#define VECTOR_H_INCLUDED

#define CAP_INI 50

#include <stdlib.h>
#include <string.h>
#include <stddef.h>

typedef struct
{
    void* vec;
    size_t tamElem;
    size_t ce;
    size_t cap;
}tVector;

typedef int (*Cmp)(void*, void*);
typedef void (*Accion)(void*, void*);

void inicializarVector(tVector* v, size_t tamElem);
void crearVectorDeArchivo(tVector* v, const char* nombreArch);
int  insertarElemOrdenadoVector(tVector* v, void* elem, Cmp cmp);
int  destruirVector(tVector* v);
int  obtenerIndiceElemVector(tVector* v, void* elem, Cmp cmp);
int  recorrerVector(tVector* v, void* param, Accion accion);

#endif // VECTOR_H_INCLUDED
