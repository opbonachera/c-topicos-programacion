#include "archivos.h"
#include "retorno.h"
#include "vector.h"
#include "indice.h"

int generarArchivoProductos(const char* nomArch)
{
    Producto vProds[CANT_PRODS] =
    {
        {0, "Higo", 300.00, 100},
        {5, "Banana", 400.00, 100},
        {3, "Pera", 200.00, 50},
        {4, "Manzana", 1000.00, 70},
        {2, "Durazno", 2000.00, 90}
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

int mostrarArchivo(const char* nomArch)
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
        printf("Codigo: %d | Precio Unitario: %.2f | Stock: %d \n", producto.codigo, producto.preUni, producto.stock);
        fread(&producto, sizeof(Producto), 1, archivo);
    }

    fclose(archivo);
    return OK;
}

int ordenarArchivo(const char* nomArch, Cmp cmpElemento)
{
    Vector vector;

    vectorCrearDeArchivo(&vector, nomArch, sizeof(Producto));
    ordenarVectorInsercion(&vector,cmpElemento);
    grabarVector(&vector, nomArch);

    return OK;
}

int cmpCodigoProducto(const void* prod1, const void* prod2)
{
    const Producto* p1 = prod1;
    const Producto* p2 = prod2;

    return p1->codigo - p2->codigo;
}

int actualizarPrecio1Producto(const char* nomArch, const char* nomArchIndice, int codigo, float porcentaje)
{
    Vector vIndice;

    if(vectorCrearDeArchivo(&vIndice, nomArchIndice, sizeof(Indice)) != OK)
    {
        return ERROR_APERTURA_ARCHIVO;
    }



    return OK;
}
int actualizarPrecioProductos(const char* nomArch, float porcentaje);
