#include <stdio.h>
#include <stdlib.h>

#include "vector.h"
#include "constantes.h"

int main()
{
    Vector vector;
    int ce = 7;

    vectorInicializar(&vector, sizeof(int), ce);
    vectorAsignarEnterosAleatorio(&vector, 0, ce);
    vectorImprimirDetalles(&vector);

    printf("-----Vector pre ordenamiento-----\n");
    vectorImprimirContenido(&vector);
    vectorOrdenarBurbujeo(&vector, cmpEntero);
    printf("-----Vector post ordenamiento-----\n");
    vectorImprimirContenido(&vector);
    vectorDestruir   (&vector);

    return 0;
}
