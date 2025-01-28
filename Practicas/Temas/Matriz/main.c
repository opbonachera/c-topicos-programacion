#include "matriz.h"

#include <stdlib.h>
#include <stdio.h>

#define ORDEN 4

int main()
{
    int** matrizEnteros = (int**)inicializarMatriz(ORDEN, ORDEN, sizeof(int));
    int** transpuesta = (int**)inicializarMatriz(ORDEN, ORDEN, sizeof(int));

    for (int i = 0; i < ORDEN; i++)
    {
        for (int j = 0; j < ORDEN; j++)
        {
            matrizEnteros[i][j] = i * ORDEN + j + 1;
        }
    }

    for (int i = 0; i < ORDEN; i++)
    {
        for (int j = 0; j < ORDEN; j++)
        {
            printf("%d ", matrizEnteros[i][j]);
        }
        printf("\n");
    }

    transponerMatrizEnteros(matrizEnteros, transpuesta, ORDEN, sizeof(int));

    for (int i = 0; i < ORDEN; i++)
    {
        for (int j = 0; j < ORDEN; j++)
        {
            printf("%d ", transpuesta[i][j]);
        }
        printf("\n");
    }

    int traza = obtenerTraza(matrizEnteros, ORDEN);
    int diagonalSecundaria = obtenerDiagonalSecundaria(matrizEnteros, ORDEN, ORDEN);

    printf("La traza de la matriz es %d \n", traza);
    printf("La diagonal secundaria es %d \n", diagonalSecundaria);
    destruirMatriz((void**)matrizEnteros, ORDEN);

    return 0;
}
