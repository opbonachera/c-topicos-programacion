#include <stdio.h>
#include <stdlib.h>

#include "allocation.h"

int vectorEnteros();
int vectorFloat();
int vectorChar();

int main()
{
    vectorChar();

    return 0;
}

int vectorChar()
{
    t_vector_generico vectorChar;
    inicializarVectorGenerico(&vectorChar, sizeof(char));

    char valoresChar[] = { 'a','b','c' };
    char elemento = 'f';

    int cantidadElementos = sizeof(valoresChar) / sizeof(char);

    asignarValoresVectorGenerico(&vectorChar, valoresChar, cantidadElementos);

    imprimirVectorChar(&vectorChar);

    aniadirElemento(&vectorChar, &elemento);

    imprimirVectorChar(&vectorChar);

    eliminarElementoPosicionDeterminada(&vectorChar, 2);

    imprimirVectorChar(&vectorChar);

    free(vectorChar.vec);
    return OK;
}

int vectorEnteros()
{
    t_vector_generico vectorEnteros;
    inicializarVectorGenerico(&vectorEnteros, sizeof(int));

    int valoresEnteros[] = {1, 2, 3, 4, 5};
    asignarValoresVectorGenerico(&vectorEnteros, valoresEnteros, 5);

    // Intentar agregar un sexto elemento (no debería permitirlo)
    int nuevoEntero = 6;
    if (aniadirElemento(&vectorEnteros, &nuevoEntero) == -1) {
        printf("No se pudo agregar el sexto elemento al vector de enteros.\n");
    }

    imprimirDetallesVectorGenerico(&vectorEnteros);
    free(vectorEnteros.vec);

    return OK;
}

int vectorFloat()
{
    t_vector_generico vectorFloats;
    inicializarVectorGenerico(&vectorFloats, sizeof(float));

    float valoresFloats[] = {1.1, 2.2, 3.3, 4.4, 5.5};
    asignarValoresVectorGenerico(&vectorFloats, valoresFloats, 5);

    // Intentar agregar un sexto elemento (no debería permitirlo)
    float nuevoFloat = 6.6;
    if (aniadirElemento(&vectorFloats, &nuevoFloat) == -1) {
        printf("No se pudo agregar el sexto elemento al vector de floats.\n");
    }

    imprimirDetallesVectorGenerico(&vectorFloats);
    free(vectorFloats.vec);

    return OK;
}

