#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "vectores.h"
#include "matrices.h"

int cadenas();
int vectores();

int main()
{
    int matriz[3][3] = {{1,2,3},{4,5,6},{7,8,9}};
    int m=3, n=3, i;
//
//    int *q[m];
//    for(i=0; i<m; i++)
//    {
//        // Creamos un vector de punteros donde en cada posicion almacenamos la primera posicion de cada fila
//        q[i] = &matriz[i][0];
//    }



    imprimirMatriz(q,m,n);

    return 0;
}

int cadenas(){}

//int vectores()
//{
//    int vec[10];
//    int ce = sizeof(vec) / sizeof(int);
//
//    initVec(&vec, ce);
//    imprimirVec(&vec, ce);
//
//    eliminarPrimeraAparicion(&vec, 9, ce);
//    printf("Array modificado\n\n");
//    imprimirVec(&vec, ce);
//    return 0;
//}
