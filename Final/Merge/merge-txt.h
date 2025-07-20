#ifndef MERGETXT_H_INCLUDED
#define MERGETXT_H_INCLUDED

#define CANT_PRODS 5
#define CANT_MOVS 8
#define OK 1
#define ERROR_ARCHIVO 0
#define ERROR_MEMORIA 0
#define TAM_DESCR 20
#define TAM_LINEA 100

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int  generarArchivoProductosTxt(const char* nombreArchProds);
int  generarArchivoMovimientosTxt(const char* nombreArchMovimientos);
int  mostrarArchivoProductosTxt(const char* nombreArch);
int  mostrarArchivoMovimientosTxt(const char* nombreArch);
int  actualizarArchivoProductosTxt(const char* nombreArchProds,
                                   const char* nombreArchMovs,
                                   void(*movTxtABin)(char* linea, void* reg),
                                   void(*prodTxtABin)(char* linea, void* reg));
void procesarNuevoProductoTxt(void* reg, FILE* archMov, FILE* archProdTmp);
void movTxtABin(char* linea, void* regMov);
void prodTxtABin(char* linea, void* regMov);

#endif // MERGE-TXT_H_INCLUDED
