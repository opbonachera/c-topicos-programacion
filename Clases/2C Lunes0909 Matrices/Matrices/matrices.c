#include "matrices.h"

int inicializarMatriz()
{
    /*int matriz[ORDEN][ORDEN];

    cargarMatriz(matriz, ORDEN);
    imprimirMatriz(matriz, ORDEN);

    int sumaDiagPrincipal = sumaDiagonalPrincipal(matriz, ORDEN);
    printf("La suma entre los elementos de a diagonal principal es igual a %d\n", sumaDiagPrincipal);

    int sumaDiagSecundaria= sumaDiagonalPrincipal(matriz, ORDEN);
    printf("La suma entre los elementos de a diagonal secundaria es igual a %d\n", sumaDiagSecundaria);
    */

    return OK;
}

void cargarMatriz(int mat[][ORDEN], size_t filas)
{
    int elem=1;
    for(int i=0; i<filas; i++)
    {
        for(int j=0; j<ORDEN; j++)
        {
            mat[i][j] = elem++;
        }
    }
}

void imprimirMatriz(int filas, int columnas, void** matriz)
{
    for(int i = 0; i < filas; i++)
    {
        for(int j = 0; j < columnas; j++)
        {
            // Cast the void** matrix elements to the appropriate type (e.g., int*)
            printf("  %d  ", ((int*)matriz[i])[j]);
        }
        printf("\n");
    }
}

int  sumaDiagonalPrincipal(int mat[][ORDEN], size_t filas)
{
    int suma=0;
    for(int i=0; i<ORDEN; i++)
        suma+=mat[i][i]; // Los indices en la diagonal principal son iguales para i y para j
    return suma;
}

int sumaDiagonalSecundaria(int mat[][ORDEN], size_t filas)
{
    int suma=0;
    for(int i=0, j=ORDEN-1; i++ ; j--)
        suma += mat[i][j];
    return suma;
}

int sumaTrianguloInferor(int mat[][ORDEN], size_t filas)
{
    int suma=0;
    for(int i=1; i<ORDEN; i++)
    {
        for(int j=0; j<i; j++)
        {
            suma+=mat[i][j];
        }
        printf("\n");
    }
    return suma;
}

int sumaTrianguloSuperior(int mat[][ORDEN], size_t filas)
{
    int suma=0;
    for(int i=0; i<=ORDEN - 2; i++)
    {
        for(int j=0; j<i; j++)
        {
            suma+=mat[i][j];
        }
        printf("\n");
    }
    return suma;
}

void** crearMatrizDinamica(size_t filas, size_t columnas, size_t tamElemento)
{
    void** matriz = malloc(filas * sizeof(void*));  // Correct size allocation

    if(!matriz)
        return NULL;

    // Alojamos memoria para cada una de las filas de la matriz
    void** ult = matriz + filas - 1;
    for(void** i = matriz; i <= ult; i++)
    {
        *i = malloc(columnas * tamElemento);

        if(!(*i))  // Correct check of the allocated memory
        {
            eliminarMatriz(matriz, i - matriz);
            return NULL;
        }
    }

     for(int i = 0; i < filas; i++)
    {
        for(int j = 0; j < columnas; j++)
        {
            ((int*)matriz[i])[j] = i * columnas + j + 1;
        }
    }

    return matriz;
}

void eliminarMatriz(void** matriz, size_t filas)
{
    void** ult = matriz + filas - 1;
    for(void** i = matriz; i <= ult; i++)
    {
        free(*i);
    }
    free(matriz);  // Don't forget to free the top-level pointer
}
