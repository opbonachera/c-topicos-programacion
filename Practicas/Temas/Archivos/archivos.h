#ifndef ARCHIVOS_H_INCLUDED
#define ARCHIVOS_H_INCLUDED

#define TAM_APYN 30
#define TAM_LINEA 500

#define OK 0
#define ERROR_APERTURA_ARCHIVO 1
#define ERROR_RESERVA_MEMORIA 2
#define ERROR_LINEA_LARGA 3

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
typedef struct
{
    int dia;
    int mes;
    int anio;
}
Fecha;


typedef struct
{
    int dni;
    char apyn[TAM_APYN + 1];
    char sexo;
    Fecha fIngr;
    float sueldo;
}
Empleado;

typedef void (*BinATxt)(const void* reg, FILE* archTxt);
typedef int  (*TxtABin)(char* linea, void* reg);

bool generarArchivoEmpleadosBin(const char* nomArch);
void mostrarArchivoEmpleadosBin(const char* nomArch);

int archivoBinATxt(const char* nomArchBin, const char* nomArchTxt, size_t tamReg, BinATxt BinATxt);
int archivoTxtABin(const char* nomArchTxt, const char* nomArchBin, size_t tamReg, TxtABin txtABin);

void empleadoBinATxtVar(const void* reg, FILE* archTxt);
void empleadoBinATxtFijo(const void* reg, FILE* archTxt);

int empleadoTxtVarABin(char* linea, void* reg);
int empleadoTxtFijoABin(char* linea, void* reg);




bool esErrorFatal(int ret);

#endif
