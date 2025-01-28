#include "archivos.h"

bool generarArchivoMovimientos(char* nombreArchivo)
{
    FILE* archivo = fopen(nombreArchivo, "wb");

    if(!archivo)
    {
        printf("Ocurrio un error al generar el archivo de movimientos.");
        return ERROR_GENERACION_ARCHIVO;
    }

    Movimiento vMovimientos[CANT_MOVIMIENTOS] =
    {
        {1, 20},
        {7, 20},
        {7, -10},
        {8, 40},
        {12, 60},
        {12, -10},
        {15, 80},
        {15, 40}
    };

    fwrite(&vMovimientos, sizeof(vMovimientos), 1, archivo);

    fclose(archivo);

    return true;
}

bool generarArchivoProductos(char* nombreArchivo)
{
    FILE* archivo = fopen(nombreArchivo, "wb");

    if(!archivo)
    {
        printf("Ocurrio un error al generar el archivo de movimientos.");
        return ERROR_GENERACION_ARCHIVO;
    }

    Producto vProductos[CANT_PRODUCTOS] =
    {
        {0, "Higo", 300.00, 100},
        {4, "Banana", 400.00, 100},
        {7, "Pera", 200.00, 50},
        {9, "Manzana", 1000.00, 70},
        {14, "Durazno", 2000.00, 90}
        // {16, "Sandia", 600.00, 90}
    };

    fwrite(&vProductos, sizeof(vProductos), 1, archivo);

    fclose(archivo);

    return true;
}

bool leerArchivo(char* nombreArchivo, Imprimir imprimir)
{
    FILE* archivo = fopen(nombreArchivo, "rb");

    if(!archivo)
    {
        printf("Ocurrio un error al leer el archivo.");
        return ERROR_LECTURA_ARCHIVO;
    }

    imprimir(archivo);

    fclose(archivo);

    return true;
}

void imprimirProducto(FILE* archivo)
{
    Producto prod;

    fread(&prod, sizeof(Producto), 1, archivo);
    while(!feof(archivo))
    {
        printf("%2d | %-*s | %07.2f | %03d\n", prod.codigo, TAM_DESCR, prod.descripcion, prod.preUni, prod.stock);
        fread(&prod, sizeof(Producto), 1, archivo);
    }
}

void imprimirMovimientos(FILE* archivo)
{

    Movimiento movimiento;

    fread(&movimiento, sizeof(Movimiento), 1, archivo);
    while(!feof(archivo))
    {
        printf("Codigo: %d | Cantidad: %d\n",movimiento.codigo, movimiento.cant);
        fread(&movimiento, sizeof(Movimiento), 1, archivo);
    }
}

bool actualizarArchivoProductos(char* nombreArchivoProductos, char* nombreArchivoMovimientos)
{
    FILE* archivoProductos = fopen(nombreArchivoProductos, "rb");
    FILE* archivoMovimientos = fopen(nombreArchivoMovimientos, "rb");
    FILE* archivoTemporal = fopen("productos.tmp","wb");

    if(!archivoProductos)
    {
        return false;
    }

    if(!archivoMovimientos)
    {
        return false;
    }

    if(!archivoTemporal)
    {
        return false;
    }

    Movimiento movimiento;
    Producto producto;
    int comp = 0;

    fread(&movimiento, sizeof(Movimiento), 1, archivoMovimientos);
    fread(&producto, sizeof(Producto), 1, archivoProductos);

    while(!feof(archivoProductos) && !feof(archivoMovimientos))
    {
        comp = producto.codigo - movimiento.codigo;

        if(comp==0)
        {
            producto.stock -= movimiento.cant;
            fread(&movimiento, sizeof(Movimiento), 1, archivoMovimientos);
        }

        if(comp<0)
        {
            fwrite(&producto, sizeof(Producto), 1, archivoTemporal);
            fread(&producto, sizeof(Producto), 1, archivoProductos);
        }

        if(comp>0)
        {
            procesarProductoNuevo(&movimiento, archivoMovimientos, archivoTemporal);
        }
    }

    while(!feof(archivoProductos)) // Productos sin movimientos
    {
        fwrite(&producto, sizeof(Producto), 1, archivoTemporal);
        fread(&producto, sizeof(Producto), 1, archivoProductos);
    }

    while(!feof(archivoMovimientos))
    {
        procesarProductoNuevo(&movimiento, archivoMovimientos, archivoTemporal);
    }

    fclose(archivoProductos);
    fclose(archivoMovimientos);
    fclose(archivoTemporal);

    remove(nombreArchivoProductos); // Borramos el archivo con el nombre de productos
    rename("Productos.tmp", nombreArchivoProductos); // Renombramos el archivo temporal al archivo original

    return true;
}

void procesarProductoNuevo(Movimiento* movimiento, FILE* archivoMovimientos, FILE* archivoTemporal)
{
    Producto productoNuevo;

    productoNuevo.codigo = movimiento->codigo;
    productoNuevo.descripcion[0] = '\0';
    productoNuevo.preUni = 0;

    fread(movimiento, sizeof(Movimiento), 1, archivoMovimientos);
    while(!feof(archivoMovimientos) && movimiento->codigo == productoNuevo.codigo)
    {
        productoNuevo.stock = movimiento->cant;
        fread(movimiento, sizeof(Movimiento), 1, archivoMovimientos);
    }

    fwrite(&productoNuevo, sizeof(Producto), 1, archivoTemporal);
}

bool generarIndice(char* nombreArchivo, char* nombreArchivoIndice, GenerarIndice generarIndice)
{
    FILE* archivo = fopen(nombreArchivo, "rb");
    FILE* archivoIndice = fopen(nombreArchivoIndice, "wb");

    if(!archivo)
    {
        printf("Ocurrio un error al leer el archivo de productos.\n");
        return ERROR_LECTURA_ARCHIVO;
    }

    if(!archivoIndice)
    {
        printf("Error al generar el archivo de indice.\n");
        return ERROR_GENERACION_ARCHIVO;
    }

    generarIndice(archivo, archivoIndice);

    fclose(archivo);
    fclose(archivoIndice);

    return true;
}

void generarIndiceProducto(FILE* archivo, FILE* archivoIndice)
{
    Producto producto;
    IndiceProducto indice;
    int nroReg = 0;

    fread(&producto, sizeof(Producto), 1, archivo);
    while(!feof(archivo))
    {
        indice.codigo = producto.codigo;
        indice.nroReg = nroReg++;
        fwrite(&indice, sizeof(IndiceProducto), 1, archivoIndice);
        fread(&producto, sizeof(Producto), 1, archivo);
    }

    printf("Cantidad de registros: %d\n", --nroReg);
}

void imprimirIndice(FILE* archivo)
{
    IndiceProducto indice;

    fread(&indice, sizeof(IndiceProducto), 1, archivo);
    while(!feof(archivo))
    {
        printf("Codigo: %d | Nro. de Registro: %d\n", indice.codigo, indice.nroReg);
        fread(&indice, sizeof(IndiceProducto), 1, archivo);
    }
}
