#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../Vector/Vector.h"

#define CANT_PRODS 8
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


bool generarArchivo(const char* nomArch);
bool generarIndice(const char* nomArch, const char* nomIdx);
bool mostrarArchivo(const char* nomArch);
bool actualizarPrecioProductos(const char* nomArch, float porc);
int cmpIndProd(const void* e1, const void* e2);
bool actualizarPrecio1Producto(const char* nomArch, const char* nomIdx, int codigo, float porc);


int main()
{
    if(!generarArchivo("Productos.dat"))
    {
        puts("Error generando el archivo");
        return 1;
    }
    
    generarIndice("Productos.dat", "Productos.idx");

    mostrarArchivo("Productos.dat");

    bool actualizo = actualizarPrecioProductos("Productos.dat", 10);

    if(!actualizo)
    {
        puts("Error actualizando los precios.");
        return 2;
    }

    puts("Despues de actualizar:");
    mostrarArchivo("Productos.dat");

    actualizarPrecio1Producto("Productos.dat", "Productos.idx", 5, 10);

    puts("Despues de actualizar 1 prod:");
    mostrarArchivo("Productos.dat");


    return 0;
}


bool generarArchivo(const char* nomArch)
{
    Producto vProds[CANT_PRODS] =
    {
        {3, "Papa", 300.00, 40},
        {1, "Pera", 400.00, 50},
        {2, "Zanahoria", 200.00, 70},
        {1, "Manzana", 1000.00, 50},
        {8, "Banana", 2000.00, 60},
        {5, "Batata", 600.00, 30},
        {4, "Limon", 100.00, 80},
        {6, "Naranja", 1500.00, 90}
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
        fseek(archProds, -sizeof(Producto), SEEK_CUR); // SEEK_SET, SEEK_END
        fwrite(&prod, sizeof(Producto), 1, archProds);
        fseek(archProds, 0L, SEEK_CUR);
        fread(&prod, sizeof(Producto), 1, archProds);
    }

    fclose(archProds);

    return true;
}


int cmpIndProd(const void* e1, const void* e2)
{
    IndProducto* indP1 = e1;
    IndProducto* indP2 = e2;

    return indP1->codigo - indP2->codigo; 
}


bool actualizarPrecio1Producto(const char* nomArch, const char* nomIdx, int codigo, float porc)
{
    Vector vIndice;
    vectorCrearDeArchivo(&vIndice, sizeof())
}