#include "utils.h"

int cmpCodDepositos(const void* c1, const void* c2)
{
    Stock* s1 = c1;
    Stock* s2 = c2;

    //printf("Comparando (%s) con (%s)\n", s1->codDeposito, s2->codDeposito);
    //printf("[%d]\n", strcmp(s1->codDeposito, s2->codDeposito));

    return strcmp(s1->codDeposito, s2->codDeposito);
}

void imprimirCodDeposito(void* dato, void* params)
{
    Stock* s1 = dato;
    printf("(%s)\n", s1->codDeposito);
}

int cargarVectorCodDepositos(const char* nombreArch, tVector* v)
{
    FILE* arch = fopen(nombreArch, "rb");
    if(!arch)
        return 0;

    Stock stock;

    while (fread(&stock, sizeof(Stock), 1, arch))
    {
        printf("Voy a insertar (%s)\n", stock.codDeposito);
        insertarElemOrdenadoVector(v, stock.codDeposito, cmpCodDepositos);
    }


    fclose(arch);
    return 1;
}
