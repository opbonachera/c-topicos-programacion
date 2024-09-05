#ifndef TDA_H_INCLUDED
#define TDA_H_INCLUDED

#include <stdbool.h>

#define DOMINGO 0
#define LUNES 1
#define MARTES 2
#define MIERCOLES 3
#define JUEVES 4
#define VIERNES 5
#define SABADO 6

typedef struct
{
    int dia;
    int mes;
    int anio;
}
Fecha;

// Funciones de modificacion de fecha
void  ingresarFecha         (Fecha* fecha);
Fecha sumarDiasAFecha       (const Fecha* fecha, int dias);
Fecha restarDiasAFecha      (const Fecha* fecha, int dias);

// Funciones de informacion de fecha
int   cantDiasMes           (int mes, int anio);
int   mostrarFecha          (const Fecha* fecha);
int   mostrarDia            (int dia);
int   diaDelAnio            (const Fecha* f); // Calcula cuantos dias pasaron desde el 1 de enereo
int   diferenciaEntreFechas (const Fecha* f1, const Fecha* f2); // Devuelve entero con la diferencia en dias entre ambas fechas
int   diaDeLaSemana         (const Fecha* f); // Determinar a que dia de la semana le corresponde cada fecha. 0: domingo, 1:lunes, 2: martes ...
Fecha diaDelAnioAFecha      (int dia, int anio);

// Funciones de validacion de fecha
bool esFechaValida          (const Fecha* fecha);
bool esAnioBisiesto         (int anio);

// Funciones de validacion de datos
int   validarPositivo       ();
int   ingresarEnteroPositivo();


#endif // TDA_H_INCLUDED
