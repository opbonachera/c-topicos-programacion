#ifndef ORDENAMIENTO_H_INCLUDED
#define ORDENAMIENTO_H_INCLUDED

#include <stdlib.h>
#include "VectorGenerico.h"

void intercambiarElemento(void *a, void* b, size_t tamElemento);
int ordenarVectorEnterosBurbujeo(VectorGenerico* vector);

#endif // ORDENAMIENTO_H_INCLUDED
