#include <stdio.h>
#include <stdlib.h>

#include "matriz.h"
#include "vector.h"
#include "utils.h"

int main()
{

    generarArchivoStocks("Stocks.dat");

    printf("Depositos antes de la actualizacion: \n");
    mostrarArchivoStocks("Stocks.dat");

    tVector vectorCodDepositos;

    inicializarVector(&vectorCodDepositos, sizeof(char[11]));
    cargarVectorCodDepositos("Stocks.dat",&vectorCodDepositos);


    int** matriz = (int**)crearMatriz(vectorCodDepositos.ce,vectorCodDepositos.ce,sizeof(int));
    cargarMatrizDesdeArchivo("Movimientos.txt", matriz, &vectorCodDepositos);

    actualizarStocksDepositos("Stocks.dat", matriz, &vectorCodDepositos);

    eliminarMatriz((void**)matriz, vectorCodDepositos.ce);
    destruirVector(&vectorCodDepositos);

    printf("Depositos luego de la actualizacion: \n");
    mostrarArchivoStocks("Stocks.dat");

    return 0;
}
