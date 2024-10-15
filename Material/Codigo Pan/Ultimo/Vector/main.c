#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "../TDAFecha/Fecha.h"
#include "Vector.h"


typedef struct
{
    int dni;
    char apyn[101];
    Fecha fNac;
}
Persona;


int cmpInt(const void* e1, const void* e2);
int cmpPersDni(const void* e1, const void* e2);
int cmpPersApyn(const void* e1, const void* e2);
int cmpPersFNac(const void* e1, const void* e2);
void imprimirInt(int pos, const void* e);
void imprimirPers(int pos, const void* e);
int cmpFechas(const Fecha* f1, const Fecha* f2);


int main()
{
    Vector v;
    vectorCrear(&v, sizeof(Persona));

    Persona pers = {40333444, "Juan Perez", {12, 3, 1986}};
    vectorInsertarAlFinal(&v, &pers);

    pers.dni = 30222111;
    strcpy(pers.apyn, "Maria Gutierrez");
    pers.fNac.dia = 11;
    pers.fNac.mes = 4;
    pers.fNac.anio = 1990;
    vectorInsertarAlFinal(&v, &pers);

    pers.dni = 20555777;
    strcpy(pers.apyn, "Veronica Gonzalez");
    pers.fNac.dia = 14;
    pers.fNac.mes = 8;
    pers.fNac.anio = 1998;
    vectorInsertarAlFinal(&v, &pers);



    // for(int i = 1; i <= 16; i++)
    // {
    //     vectorOrdInsertar(&v, i);
    // }
    
    // vectorMostrar(&v);

    // for(int i = 16; i > 0; i--)
    // {
    //     vectorOrdEliminarElem(&v, &i);
    // }
    
    // cargarVectorRandom(&v, 10000000);

    puts("Antes de ordenar:");
    vectorMostrar(&v, imprimirPers);

    time_t iniT = time(NULL);
    vectorOrdenar(&v, cmpPersFNac, INSERCION);
    // qsort(v.vec, v.ce, sizeof(int), cmpInt);
    time_t finT = time(NULL);

    puts("\nDespues de ordenar:");
    vectorMostrar(&v, imprimirPers);

    vectorOrdenar(&v, cmpPersDni, INSERCION);
    puts("\nDespues de ordenar 2:");
    vectorMostrar(&v, imprimirPers);

    printf("Tiempo de ejecucion: %ld\n", (long)(finT - iniT));

    vectorEliminar(&v);

    return 0;
}


int cmpInt(const void* e1, const void* e2)
{
    const int* int1 = e1;
    const int* int2 = e2;

    return *int1 - *int2;
}


int cmpPersDni(const void* e1, const void* e2)
{
    const Persona* p1 = e1;
    const Persona* p2 = e2;

    return p1->dni - p2->dni;
}


int cmpPersApyn(const void* e1, const void* e2)
{
    const Persona* p1 = e1;
    const Persona* p2 = e2;

    return strcmp(p1->apyn, p2->apyn);
}


int cmpPersFNac(const void* e1, const void* e2)
{
    const Persona* p1 = e1;
    const Persona* p2 = e2;

    return cmpFechas(&p1->fNac, &p2->fNac);
}


void imprimirInt(int pos, const void* e)
{
    const int* entero = e;
    printf("[%d]: %d\n", pos, *entero);
}


void imprimirPers(int pos, const void* e)
{
    const Persona* pers = e;
    printf("[%d]: DNI: %d, APYN: %s, FNAC: %d/%d/%d\n", pos, pers->dni, pers->apyn, pers->fNac.dia, pers->fNac.mes, pers->fNac.anio);
}


int cmpFechas(const Fecha* f1, const Fecha* f2)
{
    return (f1->anio * 10000 + f1->mes * 100 + f1->dia) - (f2->anio * 10000 + f2->mes * 100 + f2->dia);
}
