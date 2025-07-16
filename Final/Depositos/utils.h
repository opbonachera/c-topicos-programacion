#ifndef UTILS_H_INCLUDED
#define UTILS_H_INCLUDED
#include "vector.h"
#include "stdio.h"
typedef struct
{
	char codDeposito[11];
	int stock;
}
Stock;


typedef struct
{
	char depOrigen[11];
	char depDestino[11];
	int cantidad;
}
Movimiento;


typedef struct
{
	char codDeposito[11];
}
CodigoDeposito;

int cmpCodDepositos(void* c1, void* c2);
void  imprimirChar(void* dato, void* params);
void imprimirCodDeposito(void* dato, void* params);
int   cargarVectorCodDepositos(const char* nombreArch, tVector* v);
int   actualizarStocksDepositos(const char* nombreArchStocks, int** matrizMovimientos, tVector* vectorCodDepostios);
void generarArchivoStocks(const char* nombreArchStocks);
void mostrarArchivoStocks(const char* nombreArchStock);

#endif // UTILS_H_INCLUDED
