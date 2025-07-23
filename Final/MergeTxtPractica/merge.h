#ifndef MERGE_H_INCLUDED
#define MERGE_H_INCLUDED

#define CANT_PRODS 5
#define CANT_MOVS 8
#define TAM_DESCR 20
#define TAM_LINEA 100
#define ERROR 0

#define OK 1
#define ERROR_ARCHIVO 0
#define ERROR_MEMORIA 0
#define ERROR_LINEA_LARGA 0
#define ERROR_ARGUMENTO 0
#define ERROR_FORMATO 0
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

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
    int cant;
}
Movimiento;

typedef int (*Cmp)(const void*, const void*);
typedef void(*Accion)(void*, void*);
typedef int (*TxtABin)(char* linea, void* reg);

int  mostrarArchivoMovimientosTxt(const char* nombreArch);
int  mostrarArchivoProductosTxt(const char* nombreArch);
int  generarArchivoMovimientosTxt(const char* nombreArchMovimientos);
int  generarArchivoProductosTxt(const char* nombreArchProds);

int procesarNuevoProducto(Movimiento* movimiento, FILE* archMovs, FILE* archProdTmp, TxtABin movTxtABin);
int movTxtABin(char* linea, void* reg);
int prdTxtABin(char* linea, void* reg);
int actualizarStockProductos(const char* nombreArchProds, const char* nombreArchMovs, TxtABin movTxtABin, TxtABin prdTxtABin);

#endif // MERGE_H_INCLUDED
