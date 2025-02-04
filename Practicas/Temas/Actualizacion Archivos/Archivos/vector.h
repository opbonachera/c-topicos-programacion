#ifndef VECTOR_H_INCLUDED
#define VECTOR_H_INCLUDED

#include "retorno.h"

int inicializarVector(Vector* vector, size_t ce, size_t tamElemento);
int destruirVector(Vector* vector);
int redimensionarVector(Vector* vector, size_t nuevaCap);
int mostrarVector(Vector* vector, Impr imprimirElemento);

int vectorCrearDeArchivo(Vector* v, const char* nomArch, size_t tamElem);
int grabarVector(Vector* vector, const char* nomArch);

int ordenarVectorInsercion(Vector* vector, Cmp cmpElemento);
int busquedaBinariaVector(Vector* vector, void* elemento, int limiteInf, int limiteSup, Cmp cmpElemento, Indice* indice);

#endif
