#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


typedef struct
{
    int dia;
    int mes;
    int anio;
}
Fecha;


void ingresarFecha(Fecha* f);
bool esFechaValida(const Fecha* f);
Fecha sumarDiasAFecha(const Fecha* fecha, int dias);
void mostrarFecha(const Fecha* fecha);
int ingresarEnteroPositivo();
int cantDiasMes(int mes, int anio);
bool esAnioBisiesto(int anio);

int diferenciaEntreFechas(const Fecha* f1, const Fecha* f2);
int diaDelAnio(const Fecha* f); // 256 -> Día del Programador
Fecha diaDelAnioAFecha(int dia, int anio);
int diaDeLaSemana(const Fecha* f);
Fecha restarDiasAFecha(const Fecha* fecha, int dias);


int main()
{
    Fecha fecha;
    ingresarFecha(&fecha);
    
    int dias = ingresarEnteroPositivo();

    Fecha fSuma = sumarDiasAFecha(&fecha, dias);
    
    mostrarFecha(&fSuma);

    return 0;
}


// 12/8/2024
void ingresarFecha(Fecha* fecha)
{
    puts("Ingrese una fecha (D/M/A):");
    scanf("%d/%d/%d", &fecha->dia, &fecha->mes, &fecha->anio);
    
    while(!esFechaValida(fecha))
    {
        puts("Error: Fecha invalida. Ingresela de nuevo (D/M/A):");
        scanf("%d/%d/%d", &fecha->dia, &fecha->mes, &fecha->anio);
    }
}


bool esFechaValida(const Fecha* f)
{
    return f->anio > 1600 && f->mes >= 1 && f->mes <= 12 && f->dia >= 1 && f->dia <= cantDiasMes(f->mes, f->anio);
}


Fecha sumarDiasAFecha(const Fecha* fecha, int dias)
{
    Fecha fSuma = *fecha;
    fSuma.dia += dias;
    int cdm;

    while(fSuma.dia > (cdm = cantDiasMes(fSuma.mes, fSuma.anio)))
    {
        fSuma.dia -= cdm;
        fSuma.mes++;

        if(fSuma.mes > 12)
        {
            fSuma.mes = 1;
            fSuma.anio++;
        }
    }

    return fSuma;
}


void mostrarFecha(const Fecha* fecha)
{
    printf("%02d/%02d/%d", fecha->dia, fecha->mes, fecha->anio);
}


int ingresarEnteroPositivo()
{
    int entero;
    puts("Ingrese un entero positivo:");
    scanf("%d", &entero);

    while(entero < 0)
    {
        puts("Error: Valor negativo. Ingreselo de nuevo:");
        scanf("%d", &entero);
    }

    return entero;
}


int cantDiasMes(int mes, int anio)
{
    int cdm[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    if(mes == 2 && esAnioBisiesto(anio))
        return 29;

    return cdm[mes];
}


bool esAnioBisiesto(int anio)
{
    return anio % 4 == 0 && (anio % 100 != 0 || anio % 400 == 0);
}
