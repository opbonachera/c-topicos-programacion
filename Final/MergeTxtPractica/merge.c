#include "merge.h"

int  generarArchivoProductosTxt(const char* nombreArchProds)
{
    FILE* arch=fopen(nombreArchProds, "w+");
    if(!arch)
        return ERROR_ARCHIVO;

    Producto vProds[CANT_PRODS] =
    {
        {0, "Higo", 300.00, 100},
        {4, "Banana", 400.00, 100},
        {7, "Pera", 200.00, 50},
        {9, "Manzana", 1000.00, 70},
        {14, "Durazno", 2000.00, 90}
    };

    for(int i=0; i<CANT_PRODS; i++)
    {
        fprintf(arch, "%d|%s|%.2f|%d\n", vProds[i].codigo, vProds[i].descripcion, vProds[i].preUni, vProds[i].stock);
    }

    fclose(arch);
    return OK;
}

int  generarArchivoMovimientosTxt(const char* nombreArchMovimientos)
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

    FILE* archMovs = fopen(nombreArchMovimientos, "w+");

    if(!archMovs)
    {
        return ERROR_ARCHIVO;
    }

    for(int i=0; i<CANT_MOVS; i++)
    {
        fprintf(archMovs, "%d|%d\n", vMovs[i].codigo, vMovs[i].cant);
    }

    fclose(archMovs);

    return OK;
}

int mostrarArchivoProductosTxt(const char* nombreArch)
{
    FILE* arch = fopen(nombreArch, "r");
    if(!arch)
        return ERROR_ARCHIVO;

    char linea[100];
    while(fgets(linea, 100, arch))
    {
        char* nl = strchr(linea, '\n');
        if(nl) *nl = '\0';
        printf("(%s)\n", linea);
    }

    fclose(arch);

    return OK;
}


int  mostrarArchivoMovimientosTxt(const char* nombreArch)
{
    FILE* arch = fopen(nombreArch, "r");
    if(!arch)
        return ERROR_ARCHIVO;

    char linea[100];
    while(fgets(linea, 100, arch))
    {
        char* nl = strchr(linea, '\n');
        if(nl) *nl = '\0';
        printf("(%s)\n", linea);
    }

    fclose(arch);

    return OK;
}

int actualizarStockProductos(const char* nombreArchProds, const char* nombreArchMovs, TxtABin movTxtABin, TxtABin prdTxtABin)
{
    FILE* archProds=fopen(nombreArchProds,"r");
    if(!archProds)
        return ERROR_ARCHIVO;

    FILE* archMovs=fopen(nombreArchMovs,"r");
    if(!archMovs)
    {
        fclose(archProds);
        return ERROR_ARCHIVO;
    }

    FILE* archProdTmp = fopen("productos.tmp","w");
    if(!archProdTmp)
    {
        fclose(archMovs);
        fclose(archProds);
        return ERROR_ARCHIVO;
    }

    void* regMov = malloc(sizeof(Movimiento));
    if(!regMov)
        return ERROR_MEMORIA;

    void* regPrd = malloc(sizeof(Producto));
    if(!regPrd)
        return ERROR_MEMORIA;

    char lineaMovs[TAM_LINEA];
    char lineaProds[TAM_LINEA];

    fgets(lineaMovs, TAM_LINEA, archMovs);
    fgets(lineaProds, TAM_LINEA, archProds);

    while(!feof(archMovs) && !feof(archProds))
    {

        movTxtABin(lineaMovs, regMov);
        prdTxtABin(lineaProds, regPrd);

        Movimiento* movimiento = regMov;
        Producto*   producto = regPrd;

        int cmp = producto->codigo - movimiento->codigo;


        if(cmp==0)
        {
            producto->stock+=movimiento->cant;
            fgets(lineaMovs, TAM_LINEA, archMovs);
        }

        if(cmp<0)
        {
            fprintf(archProdTmp, "%d|%s|%.2f|%d\n", producto->codigo, producto->descripcion, producto->preUni, producto->stock);
            fgets(lineaProds, TAM_LINEA, archProds);
        }

        if(cmp>0)
        {
            procesarNuevoProducto(movimiento, archMovs, archProdTmp, movTxtABin);
        }
    }

    while(!feof(archProds))
    {
        fgets(lineaProds, TAM_LINEA, archProds);
        prdTxtABin(lineaProds, regPrd);
        Producto*   producto = regPrd;
        fprintf(archProdTmp, "%d|%s|%.2f|%d\n", producto->codigo, producto->descripcion, producto->preUni, producto->stock);
    }

    while(!feof(archMovs))
    {
        movTxtABin(lineaMovs, regMov);
        Movimiento* movimiento = regMov;
        procesarNuevoProducto(movimiento, archMovs, archProdTmp, movTxtABin);

    }

    fclose(archMovs);
    fclose(archProds);
    fclose(archProdTmp);

    remove(nombreArchProds);
    rename("productos.tmp",nombreArchProds);

    return OK;
}

int movTxtABin(char* linea, void* reg)
{
    char* act=strchr(linea, '\n');
    if(!act)
        return ERROR_LINEA_LARGA;
    *act = '\0';

    Movimiento* movimiento = reg;

    act=strrchr(linea, '|');
    movimiento->cant=atoi(act+1);
    *act='\0';

    movimiento->codigo=atoi(linea);

    return OK;
}

int prdTxtABin(char* linea, void* reg)
{
    char* act=strchr(linea, '\n');
    if(!act)
        return ERROR_LINEA_LARGA;
    *act = '\0';

    Producto* producto = reg;

    act=strrchr(linea, '|');
    producto->stock=atoi(act + 1);
    if(act) *act='\0';

    act=strrchr(linea, '|');
    producto->preUni=atof(act + 1);
    if(act) *act='\0';

    act=strrchr(linea, '|');
    strcpy(producto->descripcion, act + 1);
    if(act) *act='\0';

    producto->codigo=atoi(linea);


    return OK;
}

int procesarNuevoProducto(Movimiento* movimiento, FILE* archMovs, FILE* archProdTmp, TxtABin movTxtABin)
{
    Producto productoNuevo;

    productoNuevo.stock=movimiento->cant;
    productoNuevo.codigo=movimiento->codigo;
    productoNuevo.descripcion[0]='\0';
    productoNuevo.preUni=0;

    char lineaMovs[TAM_LINEA];
    fgets(lineaMovs, TAM_LINEA, archMovs);
    movTxtABin(lineaMovs, movimiento);
    while(!feof(archMovs) && productoNuevo.codigo == movimiento->codigo)
    {
        productoNuevo.stock+=movimiento->cant;
        fgets(lineaMovs, TAM_LINEA, archMovs);
        movTxtABin(lineaMovs, movimiento);
    }

    fprintf(archProdTmp, "%d|%s|%.2f|%d\n", productoNuevo.codigo, productoNuevo.descripcion, productoNuevo.preUni, productoNuevo.stock);

    return OK;
}
