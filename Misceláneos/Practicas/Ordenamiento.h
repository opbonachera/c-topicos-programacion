#ifndef ORDENAMIENTO_H_INCLUDED
#define ORDENAMIENTO_H_INCLUDED

#include <stdlib.h>
#include "VectorGenerico.h"

void intercambiarElemento(void *a, void* b, size_t tamElemento);
int  ordenarVectorEnterosBurbujeo(VectorGenerico* vector);
int  buscarMenor(int* vector, int desde, int hasta);
int  ordenarVectorSeleccion(VectorGenerico* vector);
int  ordenarVectorEnterosBurbujeoOptimizado2(VectorGenerico* vector);

#endif // ORDENAMIENTO_H_INCLUDED
