#include "matriz.h"

void** inicializarMatriz(int n, int m, size_t tamElem)
{
    void** matriz = malloc(tamElem * n);
    void** ult = matriz + n - 1;

    if(!matriz)
    {
        printf("Error al reservar memorias.\n");
        return NULL;
    }

    for(void** p = matriz; p<= ult; p++)
    {
        *p = malloc(tamElem * m);

        if(!*p)
        {
            printf("Hubo un error al reservar memoria.\n");
            destruirMatriz(matriz, p - matriz);
            return NULL;
        }
    }

    return matriz;
}

void destruirMatriz(void** matriz, int n)
{
    void** ult = n + matriz - 1;

    for(void** p=matriz; p<= ult; p++)
    {
        free(*p);
    }

    free(matriz);
}

int obtenerTraza(int** matriz, int n)
{
    // Asumiendo que se trata de una matriz cuadrada
    int resultado = 0;
    for(int i = 0; i<n; i++)
    {
        resultado+=matriz[i][i];
    }
    return resultado;
}

int obtenerDiagonalSecundaria(int** matriz, int orden, int m)
{
    int resultado=0;
    for(int i=0, j=orden-1; i<orden; i++, j--)
    {
        resultado+=matriz[i][j];
    }
    return resultado;
}

int obtenerSumaTInf(int** matriz, int orden)
{
    int resultado=0;

    for(int i=1; i<orden; i++)
    {
        for(int j=0; j<i; j++)
        {
            resultado+=matriz[i][j];
        }
    }

    return resultado;
}

int obtenerSumaTSup(int** matriz, int orden)
{

    int resultado=0;
    for(int i=0; i<orden; i++)
    {
        for(int j=0; j>i; j++)
        {
            resultado+=matriz[i][j];
        }
    }
    return resultado;
}

void transponerMatrizEnteros(int** matriz, int** transpuesta, int n, size_t tamElem)
{
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            memcpy(&transpuesta[j][i], &matriz[i][j], tamElem);
        }
    }
}
