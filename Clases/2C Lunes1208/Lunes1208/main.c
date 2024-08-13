#include <stdio.h>
#include <stdlib.h>

#include "tda.h"

int main()
{
    Fecha fecha;
    ingresarFecha(&fecha);

    int dias = ingresarEnteroPositivo();

    Fecha fsuma = sumarDiasAFecha(&fecha, dias);

    mostrarFecha(&fsuma);

    return 0;
}
