#include <stdio.h>
#include <stdlib.h>

#include "allocation.h"

int main()
{
    /*t_vector_generico vectorEnteros;
    t_vector_generico *punteroVectorEnteros = &vectorEnteros;

    inicializarVectorGenerico(punteroVectorEnteros, sizeof(int));
    imprimirDetallesVectorGenerico(punteroVectorEnteros);
    asignarValoresVectorGenerico(punteroVectorEnteros);
    imprimirValoresVectorGenerico(punteroVectorEnteros);
    aniadirElemento();
    imprimirValoresVectorGenerico(punteroVectorEnteros);*/
    t_vector_generico vectorEnteros;
    inicializarVectorGenerico(&vectorEnteros, sizeof(int));

    int valoresEnteros[] = {1, 2, 3, 4, 5};
    asignarValoresVectorGenerico(&vectorEnteros, valoresEnteros, 5);

    // Intentar agregar un sexto elemento (no debería permitirlo)
    int nuevoEntero = 6;
    if (agregarElemento(&vectorEnteros, &nuevoEntero) == -1) {
        printf("No se pudo agregar el sexto elemento al vector de enteros.\n");
    }

    imprimirDetallesVectorGenerico(&vectorEnteros);
    imprimirVectorEnteros(&vectorEnteros);

    t_vector_generico vectorFloats;
    inicializarVectorGenerico(&vectorFloats, sizeof(float));

    float valoresFloats[] = {1.1, 2.2, 3.3, 4.4, 5.5};
    asignarValoresVectorGenerico(&vectorFloats, valoresFloats, 5);

    // Intentar agregar un sexto elemento (no debería permitirlo)
    float nuevoFloat = 6.6;
    if (agregarElemento(&vectorFloats, &nuevoFloat) == -1) {
        printf("No se pudo agregar el sexto elemento al vector de floats.\n");
    }

    imprimirDetallesVectorGenerico(&vectorFloats);
    imprimirVectorFloats(&vectorFloats);

    // Liberar la memoria asignada
    free(vectorEnteros.vec);
    free(vectorFloats.vec);

    return 0;
}
