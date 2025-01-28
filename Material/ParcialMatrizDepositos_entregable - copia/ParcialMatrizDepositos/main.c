/***************************************************************************************
******************************* Complete sus datos *************************************
****************************************************************************************
* Apellido, Nombres: Panasiuk Fabio
*
* DNI: 45.064.113
*
****************************************************************************************/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../Matriz/Matriz.h"
#include "../Vector/Vector.h"
#include "../SolucionMatrizDepositos/SolucionMatrizDepositos.h"

#define ARG_STOCKS 1
#define ARG_MOVIMIENTOS 2


int actualizarDepositos_ALU(const char* nombreStocks, const char* nombreMovimientos);
void** matrizCrear_ALU(int fil, int col, size_t tamElem);
void matrizDestruir_ALU(void** mat, int fil);
int crearVectorCodigosDepositos_ALU(const char* nombreStocks, Vector* codigosDepositos);
void actualizarStock_ALU(void* actualizado, const void* actualizador);
void actualizarVacio_ALU(void* actualizado, const void* actualizador);
int vectorTamano_ALU(const Vector* vec);
void* vectorObtenerElem_ALU(Vector* vec, int indice);
int procesarMatrizMovimientosDepositosActualizandoStocks_ALU(int** matMovDeps, const Vector* codigosDepositos, const char* nombreStocks);

int main(int argc, char* argv[])
{
	generarStocks(argv[ARG_STOCKS]);
	generarMovimientos(argv[ARG_MOVIMIENTOS]);

	puts("Stocks antes de actualizar:");
	mostrarStocks(argv[ARG_STOCKS]);

/*********************************************************************************************************************/
//	actualizarDepositos_ALU(argv[ARG_STOCKS], argv[ARG_MOVIMIENTOS]);
/************* Descomente la función de arriba y comente la de abajo para ejecutar su código. ************************/
	//actualizarDepositos(argv[ARG_STOCKS], argv[ARG_MOVIMIENTOS]);
/*********************************************************************************************************************/

	puts("\nStocks despues de actualizar:");
	mostrarStocks(argv[ARG_STOCKS]);
	mostrarMovimientos(argv[ARG_MOVIMIENTOS]);

	return 0;
}


