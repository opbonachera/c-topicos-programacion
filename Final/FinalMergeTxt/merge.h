#ifndef MERGE_H_INCLUDED
#define MERGE_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h>
#include <string.h>
#define OK 1
#define ERROR 0
typedef struct
{
    int legajo;
    char suc[4];
    char codCargo[4];
}tCargo;

typedef int(*LineaAEst)(char* linea, void* reg);
typedef int(*Cmp)(const void* e1, const void* e2);

int  consolidarArchivoCargos(const char* nombreArchCargosOld,
                             const char* nombreArchCargosNuevo,
                             LineaAEst lineaCargoAEst,
                             Cmp cmpLegajos,
                             Cmp cmpCodCargo);
int  lineaCargoAEst(char* linea, void* reg);
int  procesarCargoConError(FILE* archErrores, void* reg);
int  cmpCodCargo(const void* e1, const void* e2);
int  cmpCodLegajo(const void* e1, const void* e2);
int  obtenerTamMaxLinea(FILE* arch);

#endif // MERGE_H_INCLUDED
