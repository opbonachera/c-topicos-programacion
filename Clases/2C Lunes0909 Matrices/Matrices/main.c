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

    imprimirMatriz(3, 3, (void**)matriz);

    return 0;
}
