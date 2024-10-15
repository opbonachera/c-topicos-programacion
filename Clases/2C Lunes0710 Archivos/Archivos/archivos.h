#ifndef ARCHIVOS_H_INCLUDED
#define ARCHIVOS_H_INCLUDED

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#define OK true
#define ERROR_GENERACION_ARCHIVO 1
#define ERROR_LECTURA_ARCHIVO 2

#define CANT_MOVIMIENTOS 8
#define CANT_PRODUCTOS   5
#define TAM_DESCR 15

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
IndiceProducto;

typedef struct
{
    int codigo;
    int cant;
}
Movimiento;


typedef void (*Imprimir)(FILE* archivo);
typedef void (*GenerarIndice)(FILE* archivo, FILE* archivoIndice);

bool generarArchivoMovimientos(char* nombreArchivo);
bool generarArchivoProductos(char* nombreArchivo);
bool generarIndice(char* nombreArchivo, char* nombreArchivoIndice, GenerarIndice generarIndice);
bool leerArchivo(char* nombreArchivo, Imprimir imprimir);
bool actualizarArchivoProductos(char* nombreArchivoProductos, char* nombreArchivoMovimientos);

void procesarProductoNuevo(Movimiento* movimiento, FILE* archivoMovimientos, FILE* archivoTemporal);
void imprimirProducto(FILE* archivo);
void imprimirIndice(FILE* archivo);
void imprimirMovimientos(FILE* archivo);
void generarIndiceProducto(FILE* archivo, FILE* archivoIndice);

#endif
