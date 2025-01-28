#include <stdio.h>
#include <stdlib.h>

#include "vector.h"

int main()
{
    t_vector vect;

    inicializarVector(&vect);
    imprimirVector(&vect);

    insertarElementoVectorOrdenado(&vect, 6);
    imprimirVector(&vect);

    return 0;
}
