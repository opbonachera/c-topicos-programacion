#include <stdio.h>
#include <stdlib.h>

#include "VectorGenerico.h"
#include "Ordenamiento.h"

int main()
{
    // Vector generico
    // Matriz generica
    VectorGenerico vector;
    int elemento = 11;

    inicializarVector(&vector);
    inicializarValoresEnteros(&vector);

    imprimirVectorEnteros(&vector);
    insertarEnteroOrdenado(&vector, &elemento);
    ordenarVectorEnterosInsercion(&vector);
    imprimirVectorEnteros(&vector);
}
