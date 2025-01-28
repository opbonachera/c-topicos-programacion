#ifndef MERGE_H_INCLUDED
#define MERGE_H_INCLUDED

#define CANT_PRODS 5
#define CANT_MOVS 8
#define TAM_DESCR 50

#define OK 0
#define ERROR_APERTURA_ARCHIVO 1
#define ERROR_RESERVA_MEMORIA 2

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

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


bool generarArchivoProductos(const char* nomArch);
bool generarArchivoMovimientos(const char* nomArch);
bool generarIndice(const char* nomArch, const char* nomIdx);
bool mostrarArchivoProductos(const char* nomArch);
bool actualizarPrecioProductos(const char* nomArch, float porc);
int cmpIndProd(const void* e1, const void* e2);
bool actualizarPrecio1Producto(const char* nomArch, const char* nomIdx, int codigo, float porc);
bool actualizarStockProductos(const char* nomArchProds, const char* nomArchMovs);
void procesarProductoNuevo(Movimiento* movimiento, FILE* archivoMovimientos, FILE* archivoTemporal);

#endif // MERGE_H_INCLUDED
