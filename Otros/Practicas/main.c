#include <stdio.h>
#include <stdlib.h>

#include "VectorGenerico.h"

int main()
{
    // Vector generico
    // Matriz generica

    VectorGenerico v;

    inicializarVector(&v);
    inicializarValoresEnteros(&v);
    imprimirVectorEnteros(&v);

    int elemento = 2;
    insertarElementoOrdenado(&v, &elemento);

    return 0;
}
