#include "archivos.h"


/* ---------------- PRODUCTOS ----------------------- */

int generarArchivoProductos(const char* nomArch)
{
    Producto vProds[CANT_PRODS] =
    {
        {112, "Higo", 300.00, 100},
        {3, "Banana", 400.00, 100},
        {2, "Pera", 200.00, 50},
        {9, "Banana", 400.00, 100},
        {0, "Banana", 400.00, 100},
        {45, "Banana", 400.00, 100},
        {4, "Banana", 400.00, 100},
        {65, "Manzana", 1000.00, 70},
        {44, "Durazno", 2000.00, 90}
    };

    FILE* archProds = fopen(nomArch, "wb");

    if(!archProds)
    {
        return ERROR;
    }

    fwrite(vProds, sizeof(Producto), CANT_PRODS, archProds);

    fclose(archProds);

    return OK;
}

int generarArchivoMovimientos(const char* nomArch)
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
        return ERROR;
    }

    fwrite(vMovs, sizeof(Movimiento), CANT_MOVS, archMovs);

    fclose(archMovs);

    return OK;
}

int generarIndice(const char* nomArch, const char* nomIdx)
{
    FILE* arch = fopen(nomArch, "rb");
    if(!arch)
        return ERROR;

    FILE* archIdx = fopen(nomIdx, "wb");
    if(!archIdx)
    {
        fclose(arch);
        return ERROR;
    }

    Producto prod;
    IndProducto ind;
    int nroReg=0;

    while(!feof(arch))
    {
        fread(&prod, sizeof(Producto), 1, arch);
        ind.nroReg=nroReg;
        ind.codigo=prod.codigo;
        fwrite(&ind, sizeof(IndProducto), 1, archIdx);
        nroReg++;
    }

    fclose(archIdx);
    fclose(arch);

    return OK;
}

int mostrarArchivo(const char* nomArch)
{
    FILE* archProds = fopen(nomArch, "rb");

    if(!archProds)
    {
        return OK;
    }

    Producto prod;

    fread(&prod, sizeof(Producto), 1, archProds);
    while(!feof(archProds))
    {
        printf("%2d, %-*s, %07.2f, %03d\n", prod.codigo, TAM_DESCR, prod.descripcion, prod.preUni, prod.stock);
        fread(&prod, sizeof(Producto), 1, archProds);
    }

    fclose(archProds);

    return OK;
}

int actualizarPrecioProductos(const char* nomArch, float porc)
{
    FILE* archProds = fopen(nomArch, "r+b");
    if(!archProds)
        return ERROR;

    Producto prod;
    float porcProd=porc/100+1;

    fread(&prod, sizeof(Producto), 1, archProds);
    while(!feof(archProds))
    {

        prod.preUni *= porcProd;
        fseek(archProds, -sizeof(Producto), SEEK_CUR);
        fwrite(&prod, sizeof(Producto), 1, archProds);
        fseek(archProds, 0L, SEEK_CUR);
        fread(&prod, sizeof(Producto), 1, archProds);
    }
    fclose(archProds);
    return OK;
}

int cmpIndProd(const void* e1, const void* e2)
{
    const IndProducto* indProd1 = e1;
    const IndProducto* indProd2 = e2;

    return indProd1->codigo - indProd2->codigo;
}

void imprimirIndice(void* elem, void* params)
{
    IndProducto* indBusq= elem;

    printf("Nro reg: [%d]|Id prod: [%d]\n", indBusq->nroReg, indBusq->codigo);
}

int actualizarPrecio1Producto(const char* nomArch, const char* nomIdx, int idProd, float porc)
{
    FILE* archProds = fopen(nomArch, "r+b");
    if(!archProds)
        return ERROR;

    FILE* archIdx = fopen(nomIdx, "rb");
    if(!archIdx)
    {
        fclose(archProds);
        return ERROR;
    }

    tVector vIndice;

    IndProducto indBusq;
    indBusq.codigo=idProd;

    Producto prod;

    vectorInicializar(&vIndice, sizeof(IndProducto));
    vectorDeArchivoBin(&vIndice, sizeof(IndProducto), "ind-prod.dat");

    //vectorRecorrer(&vIndice, NULL, imprimirIndice);

    if(vectorBuscar(&vIndice, cmpIndProd, &indBusq)==-1)
    {
        printf("No se encontro el producto de id [%d]\n", idProd);
        return ERROR;
    }


    //printf("Nro reg: [%d]|Id prod: [%d]\n", indBusq.nroReg, indBusq.codigo);

    fseek(archProds, indBusq.nroReg * sizeof(Producto), SEEK_SET);
    fread(&prod, sizeof(Producto), 1, archProds);
    prod.preUni *= (float)( porc / 100 + 1);
    fseek(archProds, -(long)sizeof(Producto), SEEK_CUR);
    fwrite(&prod, sizeof(Producto), 1, archProds);

    fclose(archIdx);
    fclose(archProds);

    return OK;
}

int vectorGrabarEnArchivoBin(tVector* v, const char* nombreArch)
{
    FILE* f = fopen(nombreArch, "wb");
    if(!f)
        return ERROR;

    fwrite(v->vec, v->tamElem, v->ce, f);

    fclose(f);
    return OK;
}

int ordenarArchivo(const char* nombreArch, size_t tamElem, Cmp cmp)
{
    tVector v;
    vectorInicializar(&v, tamElem);

    vectorDeArchivoBin(&v, tamElem, nombreArch);

    vectorOrdenar(&v, cmp,  QSORT);

    vectorGrabarEnArchivoBin(&v, nombreArch);

    return OK;
}
