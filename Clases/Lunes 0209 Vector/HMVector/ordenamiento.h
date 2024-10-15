#ifndef ORDENAMIENTO_H_INCLUDED
#define ORDENAMIENTO_H_INCLUDED

#include <stdio.h>
#include <string.h>

void    vectorOrdenarSeleccion(Vector* vector);
int     vectorEnterosOrdenarSeleccion(int vector[], int ce);
void    intercambiarElemento(void *a, void* b, size_t tamElemento);

#endif // ORDENAMIENTO_H_INCLUDED
