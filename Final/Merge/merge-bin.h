#ifndef MERGE_H_INCLUDED
#define MERGE_H_INCLUDED

#include <stdio.h>

#define CANT_PRODS 5
#define CANT_MOVS 8
#define OK 1
#define ERROR_ARCHIVO 0
#define TAM_DESCR 20


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

int  generarArchivoProductos(const char* nombreArchProds);
int  generarArchivoMovimientos(const char* nombreArchMovimientos);
int  mostrarArchivoProductos(const char* nombreArch);
int  mostrarArchivoMovimientos(const char* nombreArch);
int  actualizarArchivoProductos(const char* nombreArchProds, const char* nombreArchMovs);
int  procesarNuevoProducto(void* mov, FILE* archMovs, FILE* archProdsTmp);
int  cmpProducto(const void*, const void*);

#endif // MERGE_H_INCLUDED
