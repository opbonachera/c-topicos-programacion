#ifndef MATRIZ_H_INCLUDED
#define MATRIZ_H_INCLUDED

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef void(*Imprimir)(void* elemento);

void** inicializarMatriz(int n, int m, size_t tamElem);
void** imprimirMatriz(int n, int m, Imprimir imprimir);
void destruirMatriz(void** matriz, int n);

void transponerMatrizEnteros(int** matriz, int** transpuesta, int n, size_t tamElem);

int obtenerTraza(int** matriz, int n);
int obtenerDiagonalSecundaria(int** matriz, int orden, int m);

#endif
