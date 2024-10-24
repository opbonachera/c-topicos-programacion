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

    archivoBinATxt("Empleados.dat", "EmpleadosVar.txt", sizeof(Empleado), empleadoBinATxtVar);
    archivoBinATxt("Empleados.dat", "EmpleadosFijo.txt", sizeof(Empleado), empleadoBinATxtFijo);

    archivoTxtABin("EmpleadosVar.txt", "Empleados.dat", sizeof(Empleado), empleadoTxtVarABin);
    puts("Bin desde Txt Var:");
    mostrarArchivoEmpleadosBin("Empleados.dat");

    archivoTxtABin("EmpleadosFijo.txt", "Empleados.dat", sizeof(Empleado), empleadoTxtFijoABin);
    puts("Bin desde Txt Fijo:");
    mostrarArchivoEmpleadosBin("Empleados.dat");

    return 0;
}
