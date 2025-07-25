#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "vector.h"
#include "archivos.h"


int main()
{
    generarArchivoProductos("productos.dat");
    generarArchivoMovimientos("movimientos.dat");
    generarIndice("productos.dat", "ind-prod.dat");
    mostrarArchivo("productos.dat");

    /*actualizarPrecioProductos("productos.dat", 100);
    printf("\n");
    mostrarArchivo("productos.dat");

    actualizarPrecio1Producto("productos.dat","ind-prod.dat", 4, 50);
    printf("\n");
    mostrarArchivo("productos.dat");*/

    ordenarArchivo("productos.dat", sizeof(Producto), cmpIndProd);
    printf("\n\n");
    mostrarArchivo("productos.dat");

    return 0;
}
