#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "tda.h"

Fecha ingresarFecha()
{
    Fecha fecha;

    printf("Ingrese una fecha (DD/MM/AAAA): ");
    scanf("%d/%d/%d", &fecha.dia, &fecha.mes, &fecha.anio);

    while (!esFechaValida(fecha)) {
        printf("La fecha es inválida. Ingrese nuevamente (DD/MM/AA):\n");
        scanf("%d/%d/%d", &fecha.dia, &fecha.mes, &fecha.anio);
    }

    return fecha;
}

Fecha crearFecha()
{

    Fecha fecha;
    return fecha;
}

Fecha sumarDias(Fecha fecha, int dias)
{
    return fecha;
}

// Valida teniendo en cuenta las fechas del calendario gregoriano
// Devuelve true si es valida o false si es invalida
bool esFechaValida(Fecha fecha)
{
    return ((fecha.dia > 1 && fecha.dia <30) && (fecha.mes>1 && fecha.mes<12) && fecha.anio>1600);
}


int mostrarFecha(Fecha fecha)
{
    return 0;
}

int ingresarEnteroPositivo()
{
    int entero;
    printf("Ingrese un entero positivo: \n");
    scanf("%d", &entero);
    return entero;
}

int cantDiasMes(int mes, int anio)
{
    int cdm[13] = {0, 31, 28, 31, 30, 31, 32, 30, 31, 30, 31};
    // Agregamos un elemento al vector para que los meses empiecen en el indice 1

    if(mes == 2 && esAnioBisiesto(anio))
        return 29;

    return cdm[mes]; // retornamos la cantidad de dias correspondiente al mes indicado
}

bool esAnioBisiesto(int anio)
{
    return anio % 4 == 0 && (anio % 100 != 0 && anio % 400 == 0);
}
/*
int validarPositivo() {
    int entero;
    int result;

    do {
        printf("Ingrese un entero positivo: ");
        result = scanf("%d", &entero);

        while(getchar() != '\n');


        if (result != 1) {
            printf("Entrada no válida. Por favor, ingrese un número entero.\n");
        } else if (entero < 0) {
            printf("El número debe ser positivo.\n");
        }

    } while (result != 1 || entero < 0);

    return entero;
}


int validarRango(int limite_inferior, int limite_superior, int entero)
{
    int resultado = 0;

    if(resultado>limite_inferior && resultado<limite_superior)
    {
        resultado = 1;
    }
    return resultado;
}

*/
