#include "matrices.h"

int sumaMatrizDP(int orden, int** matriz)
{
    int sumaDp = 0;

    for(int i=0; i<orden; i++)
        sumaDp += matriz[i][i];

    return sumaDp;
}

int sumaMatrizDiagSecundaria(int orden, int** matriz)
{
    int sumaDs=0;
    int i, j;

    for(i=0, j=orden-1; i<=orden-1; i++, j--)
        sumaDs += matriz[i][j];

    return sumaDs;
}

int sumaMatrizTriangSup(int orden, int** matriz)
{
    int sumaTs = 0;

    for(int i=0, limJ=orden-2; i<=orden - 2; i++, limJ--)
    {
        for(int j=0; j<= limJ; j++)
        {
            sumaTs += matriz[i][j];
        }
    }
    return sumaTs;
}

void** crearMatriz(size_t filas, size_t columnas, size_t tamElem)
{
    void** matriz = malloc(filas * sizeof(void*));

    if(!matriz)
        return NULL;

    void** ult = matriz + filas - 1; // SOLO posible con doble puntero a void. Porque se sabe el tamaño del elemento al que apunta (void*)
    for(void** i = matriz; i<=ult; i++)
    {
        *i = malloc(tamElem * columnas);
        /*int filasADest = i - matriz;
        printf("Filas a dest: [%d]\n", filasADest);*/
        if(!*i)
        {
            eliminarMatriz(matriz, i-matriz);
            return NULL;
        }
    }

    return matriz;
}

int eliminarMatriz(void** matriz, size_t filas)
{
    void** ult = matriz + filas - 1;

    for(void** i=matriz; i<=ult; i++)
    {
        free(*i);
    }

    free(matriz);
    return 1;
}

int cargarMatrizEnteros(int orden, int** matriz)
{
    int val = 1;
    for (int i = 0; i < orden; i++)
        for (int j = 0; j < orden; j++)
            matriz[i][j] = val++;

    return 1;
}


void recorrerMatriz(int orden, void** matriz, size_t tamElem, void* param, void(*accion)(void*, void*))
{
    for (int i = 0; i < orden; i++)
    {
        void* fila = matriz[i];
        for (int j = 0; j < orden; j++)
        {
            void* elem = (void*)((char*)fila + j * tamElem);
            accion(elem, param);
        }
        printf("\n");
    }
}
