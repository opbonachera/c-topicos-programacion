#include <stdio.h>
#include <stdlib.h>

#include "matriz.h"

int main()
{
    int matriz[TAM][TAM] =
    {
        {1,2,3,4},
        {1,2,3,4},
        {1,2,3,4},
        {1,2,3,4}
    };

    mostrarMatriz(TAM, matriz);

    return 0;
}

void mostrarMatriz(int orden, int m[orden][orden])
{
    int i, j;

    for(i = 0; i < orden; i++)
    {
        for(j = 0; j < orden; j++)
        {
            printf("%d ", m[i][j]); // Print each element of the matrix
        }
        printf("\n");
    }
}

int sumarDiagonalPrincipal(int orden, int m[orden][orden])
{
    int i, suma=0;

    for(i = 0; i < orden; i++)
    {
        suma+=0;
    }

    return suma;
}

int sumarDiagonalSecundaria(int orden, int m[orden][orden])
{
    int i, j, suma=0;

    for(i = 0; i < orden; i++)
    {
        for(j=0;j<orden;j++)
        {
            suma+=m[i][orden - 1 - i];
        }
    }

    return suma;
}

/*int sumarTriangSupDiagSecu(int orden, int m[orden][orden])
{

}*/

void **matrizCrear(size_t tamElem, size_t filas, size_t columnas)
{
    void **mat = malloc(sizeof(void*) * filas);

    if(!mat)
        return NULL;

    void **ult = mat + filas - 1;
    for(void **i=mat; i<=ult; i++)
    {
        *i = malloc(tamElem * columnas);
        if(!*i) // Si no se puede asignar memoria para algun elemento liberamos toda la memoria reservada
        {
            free(*i);
            i--;
        }
        free(mat);
        return NULL;
    }
}
