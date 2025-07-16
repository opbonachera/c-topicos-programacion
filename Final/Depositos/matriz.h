#ifndef MATRIZ_H_INCLUDED
#define MATRIZ_H_INCLUDED

#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "vector.h"
#include "utils.h"
#define TAM_LINEA 100

void** crearMatriz(size_t filas, size_t columnas, size_t tamElem);
int    eliminarMatriz(void** matriz, size_t filas);
int    cargarMatrizDesdeArchivo(const char* nombreArch, int** matriz, tVector* vectorCodDepositos);

#endif // MATRIZ_H_INCLUDED
