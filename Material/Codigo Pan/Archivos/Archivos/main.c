#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../Vector/Vector.h"

#define CANT_PRODS 5
#define CANT_MOVS 8
#define TAM_DESCR 15


typedef struct
{
    int codigo;
    char descripcion[TAM_DESCR + 1];
    float preUni;
    int stock;
}
Producto;


typedef struct
{
    int codigo;
    unsigned nroReg;
}
IndProducto;


typedef struct
{
    int codigo;
    int cant;
}
Movimiento;


bool generarArchivoProductos(const char* nomArch);
bool generarArchivoMovimientos(const char* nomArch);
bool generarIndice(const char* nomArch, const char* nomIdx);
bool mostrarArchivo(const char* nomArch);
bool actualizarPrecioProductos(const char* nomArch, float porc);
int cmpIndProd(const void* e1, const void* e2);
bool actualizarPrecio1Producto(const char* nomArch, const char* nomIdx, int codigo, float porc);
bool actualizarStockProductos(const char* nomArchProds, const char* nomArchMovs);
void procesarProductoNuevo();


int main()
{
    if(!generarArchivoProductos("Productos.dat"))
    {
        puts("Error generando el archivo");
        return 1;
    }

    // generarIndice("Productos.dat", "Productos.idx");

    mostrarArchivo("Productos.dat");

    // bool actualizo = actualizarPrecioProductos("Productos.dat", 10);

    // if(!actualizo)
    // {
    //     puts("Error actualizando los precios.");
    //     return 2;
    // }

    // puts("Despues de actualizar:");
    // mostrarArchivo("Productos.dat");

    // actualizarPrecio1Producto("Productos.dat", "Productos.idx", 5, 10);

    // puts("Despues de actualizar 1 prod:");
    // mostrarArchivo("Productos.dat");

    generarArchivoMovimientos("Movimientos.dat");

    actualizarStockProductos("Productos.dat", "Movimientos.dat");

    puts("Despues de actualizar stock:");
    mostrarArchivo("Productos.dat");

    return 0;
}


bool generarArchivoProductos(const char* nomArch)
{
    Producto vProds[CANT_PRODS] =
    {
        {0, "Higo", 300.00, 100},
        {4, "Banana", 400.00, 100},
        {7, "Pera", 200.00, 50},
        {9, "Manzana", 1000.00, 70},
        {14, "Durazno", 2000.00, 90}
        // {16, "Sandia", 600.00, 90}
    };

    FILE* archProds = fopen(nomArch, "wb");

    if(!archProds)
    {
        return false;
    }

    fwrite(vProds, sizeof(Producto), CANT_PRODS, archProds);

    fclose(archProds);

    return true;
}


bool generarArchivoMovimientos(const char* nomArch)
{
    Movimiento vMovs[CANT_MOVS] =
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

    FILE* archMovs = fopen(nomArch, "wb");

    if(!archMovs)
    {
        return false;
    }

    fwrite(vMovs, sizeof(Movimiento), CANT_MOVS, archMovs);

    fclose(archMovs);

    return true;
}


bool generarIndice(const char* nomArch, const char* nomIdx)
{
    Vector vIndice;
    vectorCrear(&vIndice, sizeof(IndProducto));

    FILE* archProds = fopen(nomArch, "rb");

    if(!archProds)
    {
        return false;
    }

    Producto prod;
    IndProducto indProd;
    int nroReg = 0;

    fread(&prod, sizeof(Producto), 1, archProds);
    while(!feof(archProds))
    {
        indProd.codigo = prod.codigo;
        indProd.nroReg = nroReg++;
        vectorOrdInsertar(&vIndice, &indProd, cmpIndProd, NULL);
        fread(&prod, sizeof(Producto), 1, archProds);
    }

    fclose(archProds);

    vectorGrabar(&vIndice, nomIdx);

    vectorEliminar(&vIndice);

    return true;
}


bool mostrarArchivo(const char* nomArch)
{
    FILE* archProds = fopen(nomArch, "rb");

    if(!archProds)
    {
        return false;
    }

    Producto prod;

    fread(&prod, sizeof(Producto), 1, archProds);
    while(!feof(archProds))
    {
        printf("%2d, %-*s, %07.2f, %03d\n", prod.codigo, TAM_DESCR, prod.descripcion, prod.preUni, prod.stock);
        fread(&prod, sizeof(Producto), 1, archProds);
    }

    fclose(archProds);

    return true;
}


bool actualizarPrecioProductos(const char* nomArch, float porc)
{
    FILE* archProds = fopen(nomArch, "r+b");

    if(!archProds)
    {
        return false;
    }

    float porcProd = porc / 100 + 1;

    Producto prod;

    fread(&prod, sizeof(Producto), 1, archProds);
    while(!feof(archProds))
    {
        prod.preUni *= porcProd;
        fseek(archProds, -(long)sizeof(Producto), SEEK_CUR); // SEEK_SET, SEEK_END
        fwrite(&prod, sizeof(Producto), 1, archProds);
        fseek(archProds, 0L, SEEK_CUR);
        fread(&prod, sizeof(Producto), 1, archProds);
    }

    fclose(archProds);

    return true;
}


int cmpIndProd(const void* e1, const void* e2)
{
    const IndProducto* indP1 = e1;
    const IndProducto* indP2 = e2;

    return indP1->codigo - indP2->codigo;
}


bool actualizarPrecio1Producto(const char* nomArch, const char* nomIdx, int codigo, float porc)
{
    Vector vIndice;
    if(!vectorCrearDeArchivo(&vIndice, sizeof(IndProducto), nomIdx))
    {
        return false;
    }

    IndProducto indProd;
    indProd.codigo = codigo;

    if(vectorOrdBuscar(&vIndice, &indProd, cmpIndProd) == -1)
    {
        return false;
    }

    FILE* archProd = fopen(nomArch, "r+b");

    if(!archProd)
    {
        return false;
    }

    Producto prod;
    float porcProd = porc / 100 + 1;

    fseek(archProd, indProd.nroReg * sizeof(Producto), SEEK_SET);
    fread(&prod, sizeof(Producto), 1, archProd);
    prod.preUni *= porcProd;
    fseek(archProd, -(long)sizeof(Producto), SEEK_CUR);
    fwrite(&prod, sizeof(Producto), 1, archProd);

    fclose(archProd);

    return true;
}


bool actualizarStockProductos(const char* nomArchProds, const char* nomArchMovs)
{
    FILE* archProd = fopen(nomArchProds, "rb");

    if(!archProd)
    {
        return false;
    }

    FILE* archMov = fopen(nomArchMovs, "rb");

    if(!archMov)
    {
        return false;
    }

    FILE* archProdTmp = fopen("Productos.tmp", "wb");

    if(!archProdTmp)
    {
        return false;
    }

    Producto prod;
    Movimiento mov;
    int comp;

    fread(&prod, sizeof(Producto), 1, archProd);
    fread(&mov, sizeof(Movimiento), 1, archMov);
    
    while(!feof(archProd) && !feof(archMov))
    {
        comp = prod.codigo - mov.codigo;

        // Prod con su mov
        if(comp == 0)
        {
            prod.stock += mov.cant;
            fread(&mov, sizeof(Movimiento), 1, archMov);
        }

        // Prod sin (más) movs
        if(comp < 0)
        {
            fwrite(&prod, sizeof(Producto), 1, archProdTmp);
            fread(&prod, sizeof(Producto), 1, archProd);
        }

        // Prod nuevo
        if(comp > 0)
        {
            procesarProductoNuevo(&mov, archMov, archProdTmp);
        }
    }

    // Prod sin (más) movs
    while(!feof(archProd))
    {
        fwrite(&prod, sizeof(Producto), 1, archProdTmp);
        fread(&prod, sizeof(Producto), 1, archProd);
    }

    // Prod nuevo
    while(!feof(archMov))
    {
        procesarProductoNuevo(&mov, archMov, archProdTmp);
    }

    fclose(archProd);
    fclose(archMov);
    fclose(archProdTmp);

    remove(nomArchProds);
    rename("Productos.tmp", nomArchProds);

    return true;
}


void procesarProductoNuevo(Movimiento* mov, FILE* archMov, FILE* archProdTmp)
{
    Producto prodNuevo;
    
    prodNuevo.descripcion[0] = '\0';
    prodNuevo.preUni = 0;
    prodNuevo.codigo = mov->codigo;
    prodNuevo.stock = mov->cant;

    fread(mov, sizeof(Movimiento), 1, archMov);
    while(!feof(archMov) && mov->codigo == prodNuevo.codigo)
    {
        prodNuevo.stock += mov->cant;
        fread(mov, sizeof(Movimiento), 1, archMov);
    }

    fwrite(&prodNuevo, sizeof(Producto), 1, archProdTmp);
}