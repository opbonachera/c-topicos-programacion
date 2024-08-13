#include <stdio.h>
#include <stdlib.h>

#include "tda.h"

int main()
{
    Fecha fecha = ingresarFecha();

    int dias = ingresarEnteroPositivo();

    Fecha fsuma = sumarDias(fecha, dias);

    mostrarFecha(fsuma);

    return 0;
}
