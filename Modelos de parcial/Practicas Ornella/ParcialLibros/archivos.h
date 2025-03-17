#ifndef ARCHIVOS_H_INCLUDED
#define ARCHIVOS_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef void (*Imprimir)(FILE* archivo);
typedef int  (*Comparar)(const void* elemento1, const void* elemento2);
typedef int  (*TxtABin) (char* linea, void* reg);

int leerArchivo(char* nombreArchivo, Imprimir imprimir);
int  archivoTextoABinario(const char* nomArchTxt, const char* nomArchBin, size_t tamReg, TxtABin txtABin);

int movimientoTxtVarABin(char* linea, void* reg);
void imprimirLibro(FILE* archivoLibros);
void imprimirMovimiento(FILE* archivoMovimiento);


bool esErrorFatal(int ret);
int compararCodigoLibro(void* e1, void* e2);
int compararCodigoMovimiento(const void* e1, const void* e2);
int actualizarArchivoLibros(const char* nomArchLibros, const char* nomArchMovimientos);

#endif // ARCHIVOS_H_INCLUDED
