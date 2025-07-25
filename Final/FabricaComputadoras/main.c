#include <stdio.h>
#include <stdlib.h>


#include "vector.h"
#include "archivos.h"

void imprimirCliente(void* elem)
{
    Cliente* c = elem;
    printf("(%s)[%d]\n", c->apellidoYNombre, c->codigo);
}

void imprimirProducto(void* elem)
{
    Producto* p = elem;
    printf("[%s](%s)(%.2f)[%d] \n", p->codigo, p->descripcion, p->precio, p->stock);
}

int cmpCodigoCliente(const void* e1, const void* e2)
{
    const Cliente* c1 = e1;
    const Cliente* c2 = e2;

    return c1->codigo - c2->codigo;
}

int cmpCodigoProducto(const void* e1, const void* e2)
{
    const Producto* p1 = e1;
    const Producto* p2 = e2;

    return strcmp(p1->codigo, p2->codigo);
}

void prodTxtABin(char* linea, void* reg);

int main()
{

    crearProductosChuTxt("productos-chu.txt");
    crearProductosCorBin("productos-cor.bin");
    crearClientesChuBin("clientes-chu.bin");
    crearClientesCorBin("clientes-cor.bin");

    archivoTxtABin("productos-chu.txt", "productos-chu.bin", prodTxtABin, sizeof(Producto));

    tVector vProductosChu;
    tVector vProductosCor;
    tVector vClientesChu;
    tVector vClientesCor;

    vectorDeArchivo(&vProductosCor, "productos-cor.bin", CAP_INI, sizeof(Producto));
    vectorDeArchivo(&vProductosChu, "productos-chu.bin", CAP_INI, sizeof(Producto));
    vectorDeArchivo(&vClientesChu, "clientes-chu.bin", CAP_INI, sizeof(Cliente));
    vectorDeArchivo(&vClientesCor, "clientes-cor.bin", CAP_INI, sizeof(Cliente));

    /*vectorRecorrer(&vClientesChu, imprimirCliente);
    vectorRecorrer(&vClientesCor, imprimirCliente);
    vectorRecorrer(&vProductosCor, imprimirProducto);
    vectorRecorrer(&vProductosChu, imprimirProducto);*/

    vectorOrdenar(&vProductosCor, 0, vProductosCor.ce - 1, cmpCodigoCliente);
    vectorOrdenar(&vClientesCor, 0, vClientesCor.ce - 1, cmpCodigoCliente);
    vectorOrdenar(&vClientesChu, 0, vClientesChu.ce - 1, cmpCodigoProducto);
    vectorOrdenar(&vProductosChu, 0, vProductosChu.ce - 1, cmpCodigoProducto);


    printf("\n");
    vectorRecorrer(&vClientesChu, imprimirCliente);
    printf("\n");
    vectorRecorrer(&vClientesCor, imprimirCliente);
    printf("\n");
    vectorRecorrer(&vProductosCor, imprimirProducto);
    printf("\n");
    vectorRecorrer(&vProductosChu, imprimirProducto);

    vectorEliminarDuplicados(&vClientesChu, cmpCodigoCliente, NULL);
    vectorEliminarDuplicados(&vClientesCor, cmpCodigoCliente, NULL);
    vectorEliminarDuplicados(&vProductosChu, cmpCodigoProducto, NULL);
    vectorEliminarDuplicados(&vProductosCor, cmpCodigoProducto, NULL);

    printf("\n");
    vectorRecorrer(&vClientesChu, imprimirCliente);
    printf("\n");
    vectorRecorrer(&vClientesCor, imprimirCliente);
    printf("\n");
    vectorRecorrer(&vProductosCor, imprimirProducto);
    printf("\n");
    vectorRecorrer(&vProductosChu, imprimirProducto);


    vectorDestruir(&vClientesChu);
    vectorDestruir(&vClientesCor);
    vectorDestruir(&vProductosChu);
    vectorDestruir(&vProductosCor);

    return 0;
}

void prodTxtABin(char* linea, void* reg)
{
    Producto* p = reg;

    char* act = strchr(linea, '\n');
    if(!act) return;
    *act='\0';

    act=strrchr(linea, '|');
    p->stock=atoi(act + 1);
    *act='\0';

    act=strrchr(linea, '|');
    p->precio=atof(act + 1);
    *act='\0';

    act=strrchr(linea, '|');
    strcpy(p->descripcion, act + 1);
    *act='\0';

    strcpy(p->codigo, linea);
}
