#include "archivos.h"
#include "indice.h"
#include "vector.h"
#include "retorno.h"

int cmpEntero(const void* e1, const void* e2);
void busquedaBinaria(Vector* vector, int limiteInferior, int limiteSuperior, void* elemento, Cmp cmp, void* resultado);

int main()
{
    /*generarArchivoProductos("Productos.dat");
    mostrarArchivo("Productos.dat");


    ordenarArchivo("Productos.dat", cmpCodigoProducto);

    printf("\n");
    mostrarArchivo("Productos.dat");

    generarIndice("Productos.dat", "ProductosIndice.dat");
    mostrarIndice("ProductosIndice.dat");

    actualizarPrecio1Producto("Productos.dat", "ProductosIndice.dat", 2, 0.5);*/

    Vector vector;

    inicializarVector(&vector, 5, sizeof(int));

    int* ult = (int*)(vector.v + (vector.ce - 1) * vector.tamElemento);

    for (int* p = (int*)vector.v, i = 0; p <= ult && i < vector.ce; p++, i++)
    {
        *p = i+1;
    }


    for (int i = 0; i < vector.ce; i++)
    {
        printf("%d ", ((int*)vector.v)[i]);
    }
    printf("\n");

    int resultado;
    int* eABuscar = malloc(sizeof(int));
    *eABuscar = 87;

    busquedaBinaria(&vector, 0, vector.ce - 1, eABuscar, cmpEntero, &resultado);

    printf("Resultado es %d\n", resultado);

    return 0;
}

int cmpEntero(const void* e1, const void* e2)
{
    return (*(int*)e1 - *(int*)e2);
}


