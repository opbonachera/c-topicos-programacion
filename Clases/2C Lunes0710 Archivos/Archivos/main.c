#include <stdio.h>
#include <stdlib.h>

#include "archivos.h"

int main()
{
    generarArchivoMovimientos("movimientos.dat");
    generarArchivoProductos("productos.dat");

    printf("---Antes de la actualizacion---\n");
    leerArchivo("productos.dat", imprimirProducto);
    leerArchivo("movimientos.dat", imprimirMovimientos);

    actualizarArchivoProductos("productos.dat", "movimientos.dat");

    printf("---Despues de la actualizacion---\n");
    leerArchivo("productos.dat", imprimirProducto);

    generarIndice("productos.dat", "productos.idx", generarIndiceProducto);
    leerArchivo("productos.idx", imprimirIndice);

    return 0;
}
