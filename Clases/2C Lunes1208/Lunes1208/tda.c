#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "tda.h"

void ingresarFecha(Fecha* fecha)
{
    printf("Ingrese una fecha (DD/MM/AAAA)");
    scanf("%d/%d/%d", &fecha->dia, &fecha->mes, &fecha->anio);

    while(!esFechaValida(fecha))
    {
        printf("Fecha invalida. Ingrese nuevamente: ");
        scanf("%d/%d/%d", &fecha->dia, &fecha->mes, &fecha->anio);
    }
}

Fecha sumarDiasAFecha(const Fecha* fecha, int dias)
{
    Fecha fsuma = *fecha;
    fsuma.dia += dias;
    int cdm;

    while(fsuma.dia> (cdm = cantDiasMes(fsuma.mes, fsuma.anio)))
    {
        fsuma.dia -= cdm;
        fsuma.mes++;

        if(fsuma.mes>12)
        {
            fsuma.mes = 1;
            fsuma.anio++;
        }
    }

    return fsuma;
}

Fecha restarDiasAFecha(const Fecha* fecha, int dias)
{
    // Si se le restan dias de mas, el dia va a quedar negativo
    // en ese caso deberiamos restarle 1 al mes y la cantidad de dias ??

    Fecha fresta = *fecha;
    fresta.dia -= dias;


    return fresta;
}
// Valida teniendo en cuenta las fechas del calendario gregoriano
// Devuelve true si es valida o false si es invalida
bool esFechaValida(const Fecha* fecha)
{
    return ((fecha->dia > 1 && fecha->dia <30) && (fecha->mes>1 && fecha->mes<12) && fecha->anio>1600);
}


int mostrarFecha(const Fecha* fecha)
{
    printf("--- Muestra de fecha ---\n");
    printf("%02d/%02d/%d\n", fecha->dia, fecha->mes,fecha->anio);

    return 0;
}

int ingresarEnteroPositivo()
{
    int entero;

    printf("Ingrese un entero positivo: \n");
    scanf("%d", &entero);

    while(entero<0)
    {
        printf("Error: valor negativo. Ingrese nuevamente: ");
        scanf("%d",&entero);
    }

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


