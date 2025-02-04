#include <stdio.h>
#include <stdlib.h>

#include "archivos.h"
#include "estructuras.h"
#include  "vector.h"
int main()
{
    //leerArchivo("Libros.dat",imprimirLibro);

    archivoTextoABinario("Movimientos.txt", "Movimientos.dat", sizeof(MovLibro), movimientoTxtVarABin);

    Vector vLibros;

    vectorCrearDeArchivo(&vLibros, "Libros.dat", sizeof(Libro));
    ordenarVector(&vLibros, compararCodigoLibro);
    vectorGrabar(&vLibros,"Libros.dat");

    printf("Archivo antes de ordenar\n");

    Vector vMovimientos;

    leerArchivo("Movimientos.dat", imprimirMovimiento);
    vectorCrearDeArchivo(&vMovimientos, "Movimientos.dat", sizeof(MovLibro));
    ordenarVector(&vMovimientos, compararCodigoMovimiento);
    vectorGrabar(&vMovimientos, "Movimientos.dat");

    printf("Archivo luego de ordenar \n");
    leerArchivo("Movimientos.dat", imprimirMovimiento);
    leerArchivo("Libros.dat", imprimirLibro);

    actualizarArchivoLibros("Libros.dat", "Movimientos.dat");


    destruirVector(&vLibros);
    return 0;  // Success
}
