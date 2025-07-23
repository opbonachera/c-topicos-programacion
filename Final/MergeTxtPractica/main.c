#include <stdio.h>
#include <stdlib.h>

#include "merge.h"

int main()
{
    generarArchivoMovimientosTxt("movimientos.txt");
    generarArchivoProductosTxt("productos.txt");

    printf("\tMovimientos\n");
    mostrarArchivoMovimientosTxt("movimientos.txt");

    printf("\tProductos\n");
    mostrarArchivoProductosTxt("productos.txt");


    actualizarStockProductos("productos.txt", "movimientos.txt", movTxtABin, prdTxtABin);
    printf("\n\tProductos actualizados\n");
    mostrarArchivoProductosTxt("productos.txt");

    return 0;
}
