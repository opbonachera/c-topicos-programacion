#include <stdio.h>
#include <stdlib.h>

#include "ordenamiento.h"



int main()
{
    int vector[SIZE] = {3, 8, 1, 7, 2, 10, 5, 4, 6, 9};

    ordenarBurbujeo(&vector);

    return 0;
}

int imprimirVector(int* vector)
{
    for(int i=0; i<SIZE;i++)
        printf(" |%d| ", vector[i]);
}
