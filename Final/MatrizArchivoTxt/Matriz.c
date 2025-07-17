#include "matriz.h"

void** crearMatriz(size_t filas, size_t columnas, size_t tamElem)
{
    void** matriz = malloc(filas * sizeof(void*));
    if(!matriz)
        return NULL;

    void** ult = matriz + filas - 1;
    for(void** i=matriz; i<=ult; i++)
    {
        *i = malloc(columnas * tamElem);

        if(!*i)
        {
            eliminarMatriz(matriz - filas, filas);
            return NULL;
        }

    }

    return matriz;
}

void    eliminarMatriz(void** matriz, size_t filas)
{
    void** ult = matriz + filas - 1;
    for(void** i=matriz; i<=ult; i++)
    {
        free(*i);
    }
    free(matriz);
}

int** cargarMatrizIntDesdeArchivoTxt(const char* nombreArch)
{
    FILE* f = fopen(nombreArch, "r");
    if (!f)
    {
        printf("No se pudo abrir el archivo\n");
        return NULL;
    }

    int n;
    if (fscanf(f, "%d\n", &n) != 1)
    {
        fclose(f);
        printf("No se pudo leer el tamaño\n");
        return NULL;
    }

    int** mat = (int**)crearMatriz(n, n, sizeof(int));
    if (!mat)
    {
        fclose(f);
        printf("Error al reservar la matriz\n");
        return NULL;
    }

    char linea[100];
    for (int i = 0; i < n; i++)
    {
        fgets(linea, sizeof(linea), f);

        char* act = strchr(linea, '\n');
        if (!act)
            return ERROR_LINEA_LARGA;
        *act = '\0';

        act=strtok(linea, "|");
        for (int j = 0; j < n; j++)
        {
            if (!act)
                return 0;

            int valor = atoi(act);

            mat[i][j]=valor;
            act=strtok(NULL, "|");
        }
    }

    for(int i=0; i<n; i++)
    {
        for(int j=0; j<n; j++)
        {
            if( i>j && i+j>n-1)
            {
                printf("[%d]\n", mat[i][j]);
            }
        }
    }


    fclose(f);
    return mat;
}




