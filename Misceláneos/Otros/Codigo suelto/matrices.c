#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "matrices.h"

int imprimirMatriz(int* p[], int m, int n)
{
    int i, j;
    for(i=0; i<m; i++)
    {
        for(j=0; j<n; j++)
        {
            printf("%d\t", p[i][j]);
        }
        printf("\n");
    }
}
