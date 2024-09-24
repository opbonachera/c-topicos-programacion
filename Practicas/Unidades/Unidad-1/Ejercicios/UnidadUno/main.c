#include <stdio.h>
#include <stdlib.h>

#include "ejercicios.h"

int main()
{

    VectorGenerico vInt;
    size_t tamElem = sizeof(int);


    vectorCrear(&vInt, tamElem);
    vectorCargar(&vInt, 5);

    vectorMostrar(&vInt, printInt);
    printf("\n");
    ordenarBurbujeo(&vInt, compararInt);

    vectorMostrar(&vInt, printInt);

    vectorDestruir(&vInt);

    return 0;
}
