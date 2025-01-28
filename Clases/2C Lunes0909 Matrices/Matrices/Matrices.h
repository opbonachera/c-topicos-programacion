#ifndef MATRICES_H_INCLUDED
#define MATRICES_H_INCLUDED

#define OK 0
#define ERROR 1
#define SIN_MEMORIA 2

#define ORDEN 4

#include <stdio.h>
#include <stdlib.h>

void    cargarMatriz(int** matriz, size_t filas, size_t columnas);
void    imprimirMatriz(int filas, int columnas, void** matriz);
int     sumaDiagonalPrincipal(int mat[][ORDEN], size_t filas);
int     sumaTrianguloInferor(int mat[][ORDEN], size_t filas);
void**  crearMatrizDinamica(size_t filas, size_t columnas, size_t tamElemento);
void    eliminarMatriz(void** matriz, size_t filas);

#endif // MATRICES_H_INCLUDED
