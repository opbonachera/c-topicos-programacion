#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "Vector.h"

int cmpInt(const void* e1, const void* e2);
void imprimirInt(int pos, const void* e);


int main()
{
    Vector v;
    vectorCrear(&v, sizeof(int));

    // for(int i = 1; i <= 16; i++)
    // {
    //     vectorOrdInsertar(&v, i);
    // }
    
    // vectorMostrar(&v);

    // for(int i = 16; i > 0; i--)
    // {
    //     vectorOrdEliminarElem(&v, &i);
    // }
    
    cargarVectorRandom(&v, 10000000);

    // puts("Antes de ordenar:");
    // vectorMostrar(&v, imprimirInt);

    time_t iniT = time(NULL);
    vectorOrdenar(&v, cmpInt, INSERCION);
    // qsort(v.vec, v.ce, sizeof(int), cmpInt);
    time_t finT = time(NULL);

    // puts("\nDespues de ordenar:");
    // vectorMostrar(&v, imprimirInt);

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


void imprimirInt(int pos, const void* e)
{
    const int* entero = e;
    printf("[%d]: %d\n", pos, *entero);
}
