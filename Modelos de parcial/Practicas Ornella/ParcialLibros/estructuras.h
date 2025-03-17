#ifndef ESTRUCTURAS_H_INCLUDED
#define ESTRUCTURAS_H_INCLUDED

#define OK 0
#define ERROR_LECTURA_ARCHIVO 1
#define ERROR_LINEA_LARGA 2
#define ERROR_RESERVA_MEMORIA 3

typedef struct
{
	char codigoSocio[11];
	char codigoLibro[7];
	int cantidad; ///Positivo: m�s devoluciones, Negativo: m�s pr�stamos, Cero: Misma cant. de pr�st. que dev.
}
MovLibro; ///El tipo de los elementos de la lista.


typedef struct
{
	char codigo[7];
	char nombre[101];
	int cantidad; ///STOCK
}
Libro;


typedef struct
{
	char codigo[7];
	long nroReg;
}
IndLibro;


#endif // ESTRUCTURAS_H_INCLUDED
