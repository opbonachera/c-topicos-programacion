#include "matriz.h"

void** crearMatriz(size_t filas, size_t columnas, size_t tamElem)
{
    void** matriz = malloc(filas * sizeof(void*));
    if(!matriz)
        return 0;

    void** ult = matriz + filas - 1;
    for(void** i=matriz; i<=ult; i++)
    {
        *i = malloc(columnas * tamElem);

        if(!*i)
        {
            eliminarMatriz(matriz, i - matriz);
            return 0;
        }
    }

    return matriz;
}

int    eliminarMatriz(void** matriz, size_t filas)
{
    void** ult = matriz + filas - 1;
    for(void** i=matriz; i<=ult; i++)
        free(*i);

    free(matriz);
    return 1;
}

void inicializarMatrizEnCero(int** matriz, size_t filas, size_t columnas)
{
    for(int i=0; i<filas; i++)
    {
        for(int j=0; j<filas; j++)
        {
            matriz[i][j]=0;
        }
    }
}

int    cargarMatrizDesdeArchivo(const char* nombreArch, int** matriz, tVector* vectorCodDepositos)
{
    FILE* arch = fopen(nombreArch, "rt");
    int cant;
    char codDepOrigen[11], codDepDestino[11];

    inicializarMatrizEnCero(matriz, 4, 4);

    while (fscanf(arch, " %s %s %d", codDepOrigen, codDepDestino, &cant) == 3)
    {
        int indiceDestino = obtenerIndiceElemVector(vectorCodDepositos, codDepDestino, cmpCodDepositos);
        int indiceOrigen  = obtenerIndiceElemVector(vectorCodDepositos, codDepOrigen, cmpCodDepositos);

        printf("Destino: [%d](%s) Origen [%d](%s)\n", indiceDestino, codDepDestino, indiceOrigen, codDepOrigen);

        if(indiceDestino != -1 && indiceOrigen != -1)
        {
            matriz[indiceDestino][indiceOrigen]+=cant;
        }
    }



    return 0;
}
