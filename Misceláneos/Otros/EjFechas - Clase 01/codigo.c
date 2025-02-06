#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>

struct Fecha
{
    int Dia;
    int Mes;
    int Anio;
};

void LeerFecha(struct Fecha);
int EsBisiesto(int);
int ValidarFecha(struct Fecha);
int ValidarDato(int, int, int);
int DiasPorMes();

int main(){
    struct Fecha sF;

    printf("Este programa valida si la fecha ingresada es valida o no. \n");
    printf("Ingrese el dia. \n");
    scanf("%d",&sF.Dia);

    printf("Ingrese el mes. \n");
    scanf("%d",&sF.Mes);

    printf("Ingrese el anio. \n");
    scanf("%d",&sF.Anio);

    LeerFecha(sF);
    ValidarFecha(sF);

    return 0;
}


int ValidarFecha(struct Fecha sF)
{
    int UltDia = DiasPorMes(sF.Mes);
    int Dia = ValidarDato(sF.Dia, 1, UltDia);
    int Mes = ValidarDato(sF.Mes, 1, 12);
    int Anio = ValidarDato(sF.Anio, 0, 2024);
    int EsBis = EsBisiesto(sF.Anio);

    if( !Dia || !Mes || !Anio ){
        printf("La fecha es invalida. \n");
        return 1;
    }

    if(!EsBis && Mes == 02 && Dia == 29){
        printf("La fecha es invalida \n");
        return 1;
    }

    printf("La fecha es valida. \n");

}

int DiasPorMes(int mes) {
    switch(mes) {
        case 1: // Enero
        case 3: // Marzo
        case 5: // Mayo
        case 7: // Julio
        case 8: // Agosto
        case 10: // Octubre
        case 12: // Diciembre
            return 31;
            break;
        case 4:
        case 6:
        case 9:
        case 11:
            return 30;
            break;
        case 2:
            return 29;
            break;
        default:
            return 0; // Valor para indicar un mes no válido
    }
}

int ValidarDato(int Dato, int LimInf, int LimSup){ return (Dato >= LimInf && Dato<= LimSup) ? Dato : 0 ; }

void LeerFecha(struct Fecha sF){ printf("Se ingreso la fecha: %d/%d/%d \n", sF.Dia, sF.Mes, sF.Anio); }

int EsBisiesto(int anio){ return (anio % 4 == 0) ? 1 : 0; }

