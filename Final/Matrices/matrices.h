#ifndef MATRICES_H_INCLUDED
#define MATRICES_H_INCLUDED

#include "stddef.h"
#include "stdlib.h"
#include "time.h"
#include "stdio.h"
#include "string.h"

/* CREACION
 DE MATRICES*/
void** crearMatriz(size_t filas, size_t columnas, size_t tamElem);
int    eliminarMatriz(void** matriz, size_t filas);
int    cargarMatrizEnteros(int orden, int** matriz);
void   recorrerMatriz(int orden, void** matriz, size_t tamElem, void* param, void(*accion)(void*, void*));

/* OPERACIONES */
int sumaMatrizDP(int orden, int** matriz);
int sumaMatrizTriangSup(int orden, int** matriz);
int sumaMatrizDiagSecundaria(int orden, int** matriz);
int productoMatrices(int** matriz1, int** matriz2, int filasM1, int columnasM1, int columnasM2);

/* OTROS */
void cargarMatrizArchivoTxtFijo(const char* nombreArch);

#endif // MATRICES_H_INCLUDED
