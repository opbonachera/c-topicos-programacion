#include <stdio.h>
#include <stdlib.h>

#include "hmvector.h"

int main()
{
    Vector unVector;

    crearVector(&unVector);
    inicializarValores(&unVector);
    imprimirVector(&unVector);
    insertarElementoOrdenado(&unVector, 6);
    insertarElementoOrdenado(&unVector, 7);
    imprimirVector(&unVector);
    eliminarElementoOrdenado(&unVector, 2);
    imprimirVector(&unVector);
    destruirVector(&unVector);
    vectorOrdenarSeleccion(&unVector);

    return 0;
}
