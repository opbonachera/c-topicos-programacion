#include <stdlib.h>
#include <stdio.h>

#include "archivos.h"

int main()
{
    // if(!generarArchivoProductos("Productos.dat"))
    // {
    //     puts("Error generando el archivo");
    //     return 1;
    // }

    generarArchivoEmpleadosBin("Empleados.dat");
    mostrarArchivoEmpleadosBin("Empleados.dat");

    archivoBinATxt("Empleados.dat", "EmpleadosFijo.txt", sizeof(Empleado), empleadoBinATxtFijo);
    archivoBinATxt("Empleados.dat", "EmpleadosVari.txt", sizeof(Empleado), empleadoBinATxtVar);

    archivoTxtABin("EmpleadosFijo.txt", "EmpleadosFijo.dat", sizeof(Empleado), empleadoTxtFijoABin);
    archivoTxtABin("EmpleadosVari.txt", "EmpleadosVari.dat", sizeof(Empleado), empleadoTxtVarABin);

    mostrarArchivoEmpleadosBin("EmpleadosFijo.txt");

    return 0;
}
