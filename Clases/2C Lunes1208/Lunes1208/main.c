#include <stdio.h>
#include <stdlib.h>

#include "tda.h"

int main()
{
    /*Fecha fecha;
    ingresarFecha(&fecha);

    int dias = ingresarEnteroPositivo();

    Fecha fsuma = sumarDiasAFecha(&fecha, dias);
    mostrarFecha(&fsuma);
    */

    Fecha f1;
    ingresarFecha(&f1);

    Fecha f2;
    ingresarFecha(&f2);

    int difEntreFechas = diferenciaEntreFechas(&f1, &f2);

    printf("La diferencia entre las fechas ingresadas en dias es de: %d dia(s) \n", difEntreFechas);

    return 0;
}
