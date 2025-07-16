#include <stdio.h>
#include <stdlib.h>

#include "matriz.h"
#include "vector.h"
#include "utils.h"

int main()
{
    tVector vectorCodDepositos;

    inicializarVector(&vectorCodDepositos, sizeof(char[11]));

    cargarVectorCodDepositos("Stocks.dat",&vectorCodDepositos);
    recorrerVector(&vectorCodDepositos, NULL, imprimirCodDeposito);



    Stock stock;
    printf("\n\n\nIndice destino: [%d]\n", obtenerIndiceElemVector(&vectorCodDepositos,&stock, cmpCodDepositos));

    int** matriz = (int**)crearMatriz(4,4,sizeof(int));
    cargarMatrizDesdeArchivo("Movimientos.txt",matriz,&vectorCodDepositos);

    destruirVector(&vectorCodDepositos);
    return 0;
}
