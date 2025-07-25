#ifndef ARCHIVOS_H_INCLUDED
#define ARCHIVOS_H_INCLUDED

#include "stdio.h"
#include "stddef.h"
#include "string.h"
#include "vector.h"

typedef struct {
    char codigo[20];
    char descripcion[50];
    float precio;
    int stock;
} Producto;

typedef struct {
    int codigo;
    char apellidoYNombre[200];
} Cliente;

typedef void(*TxtABin)(char* linea, void* reg);
typedef void(*ProcesarDuplicado)(FILE* arch, void* reg);

int archivoTxtABin(const char* nomArchTxt, const char* nomArchBin, TxtABin txtABin, size_t tamReg);
int fusionarArchivos(const char* nomArch1, const char* nomArch2, Cmp cmp, ProcesarDuplicado procesarDuplicado);
void crearProductosCorBin(const char* nombreArchivo);
void crearProductosChuTxt(const char* nombreArchivo);
void crearClientesCorBin(const char* nombreArchivo);
void crearClientesChuBin(const char* nombreArchivo);

#endif // ARCHIVOS_H_INCLUDED
