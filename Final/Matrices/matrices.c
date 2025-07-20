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

int productoMatrices(int** matriz1, int** matriz2, int filasM1, int columnasM1, int columnasM2)
{
    int** matRes = (int**)crearMatriz(filasM1, columnasM2, sizeof(int));
    if(!matRes)
        return 0;

    for(int i = 0; i < filasM1; i++)
    {
        for(int j = 0; j < columnasM2; j++)
        {
            matRes[i][j] = 0;
            for(int k = 0; k < columnasM1; k++) // columnasM1 == filas de matriz2
            {
                matRes[i][j] += matriz1[i][k] * matriz2[k][j];
            }
        }
    }

    // Imprimir resultado
    for(int i = 0; i < filasM1; i++)
    {
        for(int j = 0; j < columnasM2; j++)
        {
            printf("[%d] ", matRes[i][j]);
        }
        printf("\n");
    }

    eliminarMatriz((void**)matRes, filasM1);
    return 1;
}

void cargarMatrizArchivoTxtFijo(const char* nombreArch)
{

    FILE* arch = fopen(nombreArch, "r");
    if(!arch)
        return;

    char linea[100];
    fgets(linea, 100, arch);

    char* act = strrchr(linea, '\n');
    if(act) *act='\0';

    int n=atoi(linea);

    int** matriz=(int**)crearMatriz(n, n, sizeof(int));

    while(fgets(linea, 100, arch))
    {
        char* act = strrchr(linea, '\n');
        if(act) *act='\0';
        printf("(%s)\n", linea);

        for(int i=0; i<n; i++)
        {
            char* sep = strrchr(linea, '|');

            for(int j=0; j<n; j++)
            {
                matriz[i][j]=atoi(sep+1);
            }
        }
    }
}
