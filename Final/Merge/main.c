#include <stdio.h>
#include <stdlib.h>

#include "merge-txt.h"

int main()
{
    /*generarArchivoProductos("productos.dat");
    mostrarArchivoProductos("productos.dat");

    generarArchivoMovimientos("movimientos.dat");

    printf("Productos antes de actualizar\n");
    mostrarArchivoMovimientos("movimientos.dat");

    actualizarArchivoProductos("productos.dat","movimientos.dat");

    printf("Productos luego de actualizar\n");
    mostrarArchivoProductos("productos.dat");*/

    generarArchivoProductosTxt("productos.txt");
    generarArchivoMovimientosTxt("movimientos.txt");

    mostrarArchivoProductosTxt("productos.txt");
    mostrarArchivoMovimientosTxt("movimientos.txt");
    printf("\n");
    actualizarArchivoProductosTxt("productos.txt", "movimientos.txt", movTxtABin, prodTxtABin);
    printf("\n");
    mostrarArchivoProductosTxt("productos.txt");
    mostrarArchivoMovimientosTxt("movimientos.txt");

    return 0;
}
