#include "merge.h"

bool generarArchivoProductos(const char* nomArch)
{
    FILE* archivo = fopen(nomArch, "wb");
    if(!archivo)
    {
        return ERROR_APERTURA_ARCHIVO;
    }

    Producto vProductos[CANT_PRODS] =
    {
        {0, "Higo", 300.00, 100},
        {4, "Banana", 400.00, 100},
        {7, "Pera", 200.00, 50},
        {9, "Manzana", 1000.00, 70},
        {14, "Durazno", 2000.00, 90}
    };

    fwrite(&vProductos, sizeof(Producto), sizeof(vProductos) / sizeof(Producto), archivo);

    fclose(archivo);

    return true;
}

bool generarArchivoMovimientos(const char* nomArch)
{
    FILE* archivo = fopen(nomArch, "wb");
    if(!archivo)
    {
        return ERROR_APERTURA_ARCHIVO;
    }

    Movimiento vMovimientos[CANT_MOVS] =
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

    fwrite(&vMovimientos, sizeof(Movimiento), sizeof(vMovimientos) / sizeof(Movimiento), archivo);
    fclose(archivo);
    return true;
}

bool mostrarArchivoMovimientos(const char* nomArch)
{
    FILE* archivo = fopen(nomArch, "rb");
    Movimiento movimiento;

    fread(&movimiento, sizeof(Movimiento), 1, archivo);
    while(!feof(archivo))
    {
        printf("Codigo: %d |  Cantidad: %d \n", movimiento.codigo, movimiento.cant);
        fread(&movimiento, sizeof(Movimiento), 1, archivo);
    }

    fclose(archivo);
    return true;
}
bool mostrarArchivoProductos(const char* nomArch)
{
    FILE* archivo = fopen(nomArch, "rb");
    if(!archivo)
    {
        return ERROR_APERTURA_ARCHIVO;
    }

    Producto producto;
    fread(&producto, sizeof(Producto), 1, archivo);
    while(!feof(archivo))
    {
        printf("Codigo: %d | Descripcion: %s | Precio Unitario: %f | Stock: %d\n", producto.codigo, producto.descripcion, producto.preUni, producto.stock);
        fread(&producto, sizeof(Producto), 1, archivo);
    }

    fclose(archivo);

    return true;
}

int cmpIndProd(const void* e1, const void* e2)
{
    return (Producto*)e1 - (Producto*)e2;
}

bool actualizarStockProductos(const char* nomArchProds, const char* nomArchMovs)
{
    FILE* archProd = fopen(nomArchProds, "rb");
    if (!archProd) {
        return false;
    }

    FILE* archMov = fopen(nomArchMovs, "rb");
    if (!archMov) {
        fclose(archProd); // Close previously opened file
        return false;
    }

    FILE* archProdTmp = fopen("Productos.tmp", "wb");
    if (!archProdTmp) {
        fclose(archProd);
        fclose(archMov);
        return false;
    }

    Producto prod;
    Movimiento mov;
    int comp;

    fread(&prod, sizeof(Producto), 1, archProd);
    fread(&mov, sizeof(Movimiento), 1, archMov);

    while (!feof(archProd) && !feof(archMov)) {
        comp = prod.codigo - mov.codigo;

        if (comp == 0) {
            prod.stock += mov.cant;
            fread(&mov, sizeof(Movimiento), 1, archMov);
        }

        if (comp < 0) {
            fwrite(&prod, sizeof(Producto), 1, archProdTmp);
            fread(&prod, sizeof(Producto), 1, archProd);
        }

        if (comp > 0) {
            //procesarProductoNuevo(&mov, archMov, archProdTmp);
        }
    }

    while (!feof(archProd)) {
        fwrite(&prod, sizeof(Producto), 1, archProdTmp);
        fread(&prod, sizeof(Producto), 1, archProd);
    }

    while (!feof(archMov)) {
        // procesarProductoNuevo(&mov, archMov, archProdTmp);
    }

    fclose(archProd);
    fclose(archMov);
    fclose(archProdTmp);

    remove(nomArchProds);
    rename("Productos.tmp", nomArchProds);

    return true;
}
