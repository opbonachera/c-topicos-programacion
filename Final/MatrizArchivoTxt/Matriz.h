#ifndef MATRIZ_H_INCLUDED
#define MATRIZ_H_INCLUDED

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define ERROR_LINEA_LARGA 0

void** crearMatriz(size_t filas, size_t columnas, size_t tamElem);
void    eliminarMatriz(void** matriz, size_t filas);
int**    cargarMatrizIntDesdeArchivoTxt(const char* nombreArch);

#endif // MATRIZ_H_INCLUDED
