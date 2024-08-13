#ifndef TDA_H_INCLUDED
#define TDA_H_INCLUDED

#include <stdbool.h>

typedef struct
{
    int dia;
    int mes;
    int anio;
}
Fecha;

Fecha ingresarFecha         ();
Fecha crearFecha            ();
Fecha sumarDias             (Fecha fecha, int dias);

bool esFechaValida          (Fecha fecha);
bool enteroEstaDentroDeRango(int entero, int limiteInferior, int limiteSuperior);
bool esAnioBisiesto         (int anio);

int   cantDiasMes           (int mes, int anio);
int   ingresarEnteroPositivo();
int   mostrarFecha          (Fecha fecha);
int   validarPositivo       ();



#endif // TDA_H_INCLUDED
