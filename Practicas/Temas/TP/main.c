#include <stdlib.h>
#include <stdio.h>

#include "funciones.h"

int main()
{
    //copiarImagen("unlam.bmp", "copia.bmp");
    int filas=3, columnas=3;
    int matrix[3][3] = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };
    int transposed[3][3];

    printf("Original matrix: \n");


    // comodin("unlam.bmp", "comodin.bmp");
    // espejarImagenVertical("unlam.bmp", "vertical.bmp");
    // pixelearImagen("unlam.bmp", "pixel.bmp");
    achicarImagen("unlam.bmp", "salida.bmp");
    for(int i=0; i<filas; i++)
    {
        for(int j=0; j<columnas; j++)
        {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }

    //Trasnspose matrix left

    for (int i = 0; i < columnas; i++) {
        for (int j = 0; j < filas; j++) {
            transposed[filas - j - 1][i] = matrix[i][j];
        }
    }


    // Rotate matrix 90 degrees right
    /*for (int i = 0; i < filas; i++)
    {
        for (int j = 0; j < columnas; j++)
        {
            transposed[j][filas - i - 1] = matrix[i][j];
        }
    }*/

    printf("Rotated matrix: \n");

    for (int i = 0; i < columnas; i++)
    {
        for (int j = 0; j < filas; j++)
        {
            printf("%d ", transposed[i][j]);
        }
        printf("\n");
    }

    modificarContraste("unlam.bmp", "contraste.bmp");

    return 0;
}
