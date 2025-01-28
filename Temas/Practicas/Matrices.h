#ifndef MATRICES_INCLUDED_H
#define MATRICES_INCLUDED_H

#include <stdio.h>
#include <stdlib.h>

#define ORDEN 4

#define OK 0
#define ERROR_DE_MEMORIA 1
#define SIN_MEMORIA 4

void**  crearMatriz(size_t orden, size_t tamElemento);
void    cargarMatriz(int** matriz, size_t orden);

#endif // MATRICES_INCLUDED_H
