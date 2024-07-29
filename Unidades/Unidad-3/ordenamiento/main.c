#include <stdio.h>
#include <stdlib.h>

#include "ordenamiento.h"

int main()
{
    int vec[10] = {1,8,9,2,3,4,6,5,7,10};

    printf("Vector desordenado: \n");
    printVector(vec, 10);

    printf("\n");

    burbujeoInt(vec, 10);
    printf("Vector ordenado: \n");
    printVector(vec, 10);

    return 0;
}
