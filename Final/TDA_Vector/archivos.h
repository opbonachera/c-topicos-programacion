#ifndef ARCHIVOS_H_INCLUDED
#define ARCHIVOS_H_INCLUDED

#include <stdio.h>
#include "vector.h"

#define OK 1
#define ERROR 0

#define CANT_PRODS 9
#define CANT_MOVS 8
#define TAM_DESCR 15
#define TAM_APYN 30
#define TAM_LINEA 500

typedef struct
{
    int codigo;
    char descripcion[TAM_DESCR + 1];
    float preUni;
    int stock;
}
Producto;
typedef struct
{
    int codigo;
    unsigned nroReg;
}
IndProducto;

typedef struct
{
    int codigo;
    int cant;
}
Movimiento;

int generarArchivoProductos(const char* nomArch);
int generarArchivoMovimientos(const char* nomArch);
int mostrarArchivo(const char* nomArch);
int generarIndice(const char* nomArch, const char* nomIdx);
int actualizarPrecioProductos(const char* nomArch, float porc);
int actualizarPrecio1Producto(const char* nomArch, const char* nomIdx, int idProd, float porc);
int cmpIndProd(const void* e1, const void* e2);
int ordenarArchivo(const char* nombreArch, size_t tamElem, Cmp cmp);

#endif // ARCHIVOS_H_INCLUDED
