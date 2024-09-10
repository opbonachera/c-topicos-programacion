#include <stdio.h>
#include <stdlib.h>

#include "matrices.h"

int main()
{

    int **matriz = (int**)crearMatrizDinamica(ORDEN, ORDEN, sizeof(int));
    if(!matriz)
    {
        return SIN_MEMORIA;
    }

    imprimirMatriz(ORDEN, ORDEN, matriz);

    return 0;
}
