#ifndef ARCHIVOS_H_INCLUDED
#define ARCHIVOS_H_INCLUDED

#include "retorno.h"

int cmpCodigoProducto(const void* prod1, const void* prod2);
int generarArchivoProductos(const char* nomArch);
int mostrarArchivo(const char* nomArch);
int ordenarArchivo(const char* nomArch, Cmp cmpElemento);
int actualizarPrecio1Producto(const char* nomArch, const char* nomArchIndice, int codigo, float porcentaje);
int actualizarPrecioProductos(const char* nomArch, float porcentaje);

#endif
