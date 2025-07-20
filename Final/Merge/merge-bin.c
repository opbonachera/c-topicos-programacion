#include "merge-bin.h"

int  generarArchivoProductos(const char* nombreArchProds)
{
    Producto vProds[CANT_PRODS] =
    {
        {0, "Higo", 300.00, 100},
        {4, "Banana", 400.00, 100},
        {7, "Pera", 200.00, 50},
        {9, "Manzana", 1000.00, 70},
        {14, "Durazno", 2000.00, 90}
    };

    FILE* archProds = fopen(nombreArchProds, "wb");

    if(!archProds)
    {
        return ERROR_ARCHIVO;
    }

    fwrite(vProds, sizeof(Producto), CANT_PRODS, archProds);

    fclose(archProds);

    return OK;
}

int  generarArchivoMovimientos(const char* nombreArchMovimientos)
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

    FILE* archMovs = fopen(nombreArchMovimientos, "wb");

    if(!archMovs)
    {
        return ERROR_ARCHIVO;
    }

    fwrite(vMovs, sizeof(Movimiento), CANT_MOVS, archMovs);

    fclose(archMovs);

    return OK;
}

int mostrarArchivoProductos(const char* nombreArch)
{
    FILE* arch = fopen(nombreArch, "rb");
    if(!arch)
        return ERROR_ARCHIVO;

    Producto prodTmp;

    while(fread(&prodTmp, sizeof(Producto),1,arch))
    {
        printf("[%d]|(%s)|[%.2f]|[%d]\n",prodTmp.codigo, prodTmp.descripcion, prodTmp.preUni, prodTmp.stock);
    }

    fclose(arch);
    return OK;
}

int mostrarArchivoMovimientos(const char* nombreArch)
{
    FILE* arch = fopen(nombreArch, "rb");
    if(!arch)
        return ERROR_ARCHIVO;

    Movimiento movTmp;

    while(fread(&movTmp, sizeof(Movimiento),1,arch))
    {
        printf("[%d][%d]\n", movTmp.codigo, movTmp.cant);
    }

    fclose(arch);
    return OK;
}

int actualizarArchivoProductos(const char* nombreArchProds, const char* nombreArchMovs)
{
    FILE* archProds=fopen(nombreArchProds,"rb");
    if(!archProds)
        return ERROR_ARCHIVO;

    FILE* archMovs=fopen(nombreArchMovs,"rb");
    if(!archMovs)
    {
        fclose(archProds);
        return ERROR_ARCHIVO;
    }

    FILE* archProdTmp = fopen("productos.tmp","wb");
    if(!archProdTmp)
    {
        fclose(archMovs);
        fclose(archProds);
        return ERROR_ARCHIVO;
    }

    Movimiento movTmp;
    Producto  prodTmp;
    int cmp;

    fread(&movTmp,  sizeof(Movimiento), 1, archMovs);
    fread(&prodTmp, sizeof(Producto), 1, archProds);
    while(!feof(archMovs) && !feof(archProds))
    {
        cmp = prodTmp.codigo - movTmp.codigo;

        if(cmp==0)
        {
            prodTmp.stock+=movTmp.cant;
            fread(&movTmp, sizeof(Movimiento), 1, archMovs);
        }

        if(cmp<0)
        {
            fwrite(&prodTmp, sizeof(Producto), 1, archProdTmp);
            fread (&prodTmp, sizeof(Producto),  1, archProds);
        }

        if(cmp>0)
        {
            procesarNuevoProducto(&movTmp, archMovs, archProdTmp);
        }
    }

    while(!feof(archProds))
    {
        fwrite(&prodTmp, sizeof(Producto), 1, archProdTmp);
        fread (&prodTmp, sizeof(Producto),  1, archProds);
    }

    while(!feof(archMovs))
    {
        procesarNuevoProducto(&movTmp, archMovs, archProdTmp);
    }

    fclose(archMovs);
    fclose(archProds);
    fclose(archProdTmp);

    remove(nombreArchProds);
    rename("productos.tmp", nombreArchProds);

    return OK;
}

int  procesarNuevoProducto(void* mov, FILE* archMovs, FILE* archProdsTmp)
{
    Producto prodNuevo;
    Movimiento* m = mov;

    prodNuevo.codigo=m->codigo;
    prodNuevo.stock=m->cant;
    prodNuevo.descripcion[0]='\0';
    prodNuevo.preUni=0.0;

    while(!feof(archMovs) && prodNuevo.codigo==m->codigo)
    {
        prodNuevo.stock+=m->cant;
        fread(m, sizeof(Movimiento), 1, archMovs);
    }

    fwrite(&prodNuevo, sizeof(Producto), 1, archProdsTmp);
    return OK;
}

