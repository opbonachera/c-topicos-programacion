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

int diferenciaEntreFechas(const Fecha* f1, const Fecha* f2)
{
    int dias=0;
    int fechaMayor, difEntreMeses = 0, difEntreAnios=0, difEntreDias=0;

    if(!compararFechas(f1,f2))
        return 0; // Son iguales

    fechaMayor = compararFechas(f1, f2); // devuelve <0 si f1 es menor que f2 y n>0 si f1 es mayor que f2


    difEntreAnios = fechaMayor > 0 ?    f1->anio -  f2->anio : f2->anio -  f1->anio;
    difEntreMeses = fechaMayor > 0 ?    f1->mes  -  f2->mes  : f2->mes  -  f1->mes;
    difEntreDias  = fechaMayor > 0 ?    f1->dia  -  f2->dia  : f2->dia  -  f1->dia;

        /*printf("Diferencia entre anios: %d\n", difEntreAnios);
        printf("Diferencia entre meses: %d\n", difEntreMeses);
        printf("Diferencia entre DIAS: %d \n", difEntreDias);*/

    if(difEntreAnios>0)
        dias += calcularDiaAnio(difEntreAnios);

    if(difEntreMeses>0)
        dias += calcularDiasMes(difEntreMeses);

    if(difEntreDias>0)
        dias += difEntreDias;


    return dias;
}

int calcularDiaAnio(int anios)
{
    // Devuelve la cantidad de dias entre [anio1;anio2]
    int i, sumatoria=0;

    for(i=0; i<anios; i++)
        sumatoria+= esAnioBisiesto(i) ? 366 : 365 ;

    return sumatoria;
}

int calcularDiasMes(int mes)
{
    int i, sumatoria=0;

    for(i=1;i<mes+1;i++)
        sumatoria += cantDiasMes(i,2024);

    return sumatoria;
}

int compararFechas(const Fecha* f1, const Fecha* f2) {
    // Comparar años
    if (f1->anio != f2->anio) {
        return f1->anio - f2->anio;
    }

    // Comparar meses (si los años son iguales)
    if (f1->mes != f2->mes) {
        return f1->mes - f2->mes;
    }

    // Comparar días (si los meses son iguales)
    return f1->dia - f2->dia;
}


int diaDeLaSemana (const Fecha* f)
{

}


int mostrarDia(int dia)
{
    switch(dia)
    {
    case 0:
        printf("Domingo");
        break;
    case 1:
        printf("Lunes");
        break;
    case 2:
        printf("Martes");
        break;
    case 3:
        printf("Miércoles");
        break;
    case 4:
        printf("Jueves");
        break;
    case 5:
        printf("Viernes");
        break;
    case 6:
        printf("Sábado");
        break;
    default:
        printf("Día inválido");
        break;
    }
    return 0;
}


bool esAnioBisiesto(int anio)
{
    return anio % 4 == 0 && (anio % 100 != 0 && anio % 400 == 0);
}


