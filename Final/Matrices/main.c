#include <stdio.h>
#include <stdlib.h>
#include "matrices.h"

void generarArchMatriz(char nombreArch[100])
{
    FILE* arch = fopen(nombreArch, "wb");
    if(!arch)
        return;

    int n = 3;
    int matriz[3][3] = { {1,2,3}, {4,5,6}, {7,8,9} };
    char pipe = '|';

    fwrite(&n, sizeof(int), 1, arch);
    for(int i=0; i<= n-1; i++)
    {
        for(int j=0; j<= n-1; j++)
        {
            fwrite(&matriz[i][j], sizeof(int), 1, arch);
            if( j != n - 1) fwrite(&pipe, sizeof(char), 1, arch);
        }
    }

    fclose(arch);
}

void leerArchMatriz(const char* nombreArch)
{/*
    FILE* arch = fopen(nombreArch, "rb");
    if (!arch) {
        perror("Error opening file");
        return;
    }

    int n;
    int matriz[3][3] = {0};

    fread(&n, sizeof(int), 1, arch);
    printf("Orden de la matriz: [%d]\n", n);
    for(int i=0; i<=n-1; i++)
    {
        // Leer la linea
        for(int j=0; j<=n-1; j++)
        {
            // Leer el caracter
        }
    }*/
}

void imprimirInt(void* d, void* param)
{
    printf("%d | ", *(int*)d);
}

int main()
{
    /*int** mat1 = (int**)crearMatriz(2, 3, sizeof(int));
    int** mat2 = (int**)crearMatriz(3, 2, sizeof(int));

    int val = 1;

    // Inicializar mat1 (2x3)
    for(int i = 0; i < 2; i++)
    {
        for(int j = 0; j < 3; j++)
        {
            mat1[i][j] = val++;
        }
    }

    val = 1;

    // Inicializar mat2 (3x2)
    for(int i = 0; i < 3; i++)
    {
        for(int j = 0; j < 2; j++)
        {
            mat2[i][j] = val++;
        }
    }

    productoMatrices(mat1, mat2, 2, 3, 2);  // filasM1, columnasM1, columnasM2

    eliminarMatriz((void**)mat1, 2);
    eliminarMatriz((void**)mat2, 3);*/

    cargarMatrizArchivoTxtFijo("matriz.txt");
    return 0;
}
