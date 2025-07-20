#include "merge-txt.h"

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
    int cant;
}
Movimiento;


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

int  actualizarArchivoProductosTxt(const char* nombreArchProds,
                                   const char* nombreArchMovs,
                                   void(*movTxtABin)(char* linea, void* reg),
                                   void(*prodTxtABin)(char* linea, void* reg))
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

    void* regMov  = malloc(sizeof(Movimiento));
    if(!regMov)
        return ERROR_MEMORIA;

    void* regProd = malloc(sizeof(Producto));
    if(!regProd)
    {
        free(regMov);
        return ERROR_MEMORIA;
    }

    char lineaMov[TAM_LINEA];
    char lineaProd[TAM_LINEA];
    int cmp;
    while(fgets(lineaMov, TAM_LINEA, archMovs) && fgets(lineaProd, TAM_LINEA, archProds) )
    {
        movTxtABin (lineaMov, regMov);
        prodTxtABin(lineaProd, regProd);

        Movimiento* movimiento = regMov;
        Producto* producto = regProd;

        cmp = producto->codigo - movimiento->codigo;

        if(cmp==0)
        {
            producto->stock+=movimiento->cant;
            fgets(lineaMov, TAM_LINEA, archMovs);
        }

        if(cmp<0)
        {
            fprintf(archProdTmp, "%d|%s|%.2f|%d\n", producto->codigo, producto->descripcion, producto->preUni, producto->stock);
            fgets(lineaProd, TAM_LINEA, archProds);
        }

        if(cmp>0)
        {
            // Procesar producto nuevo
            //procesarNuevoProductoTxt(regMov, archMovs, archProdTmp);

        }
    }

    while(fgets(lineaMov, TAM_LINEA, archMovs))
    {
        procesarNuevoProductoTxt(regMov, archMovs, archProdTmp);
    }

    while(fgets(lineaProd, TAM_LINEA, archProds))
    {
        prodTxtABin(lineaProd, regProd);
        Producto* producto = regProd;
        fprintf(archProdTmp, "%d|%s|%.2f|%d\n", producto->codigo, producto->descripcion, producto->preUni, producto->stock);
    }

    fclose(archProdTmp);
    fclose(archMovs);
    fclose(archProds);

    remove("productos.tmp");
    rename("productos.tmp", nombreArchProds);

    return OK;
}

void movTxtABin(char* linea, void* regMov)
{
    Movimiento* mov = regMov;

    char* act = strrchr(linea, '\n');
    //  if not act return linea larga
    *act='\0';

    act = strrchr(linea, '|');
    mov->cant=atoi(act+1);
    *act='\0';

    mov->codigo=atoi(linea);
    *act='\0';
}

void prodTxtABin(char* linea, void* regProd)
{
    Producto* prod = regProd;
    char* act = strrchr(linea, '\n');
    // if not act return llinea larga
    *act = '\0';

    act = strrchr(linea, '|');
    prod->stock=atoi(act+1);
    *act='\0';

    act = strrchr(linea, '|');
    prod->preUni=atoi(act+1);
    *act='\0';

    act = strrchr(linea, '|');
    strcpy(prod->descripcion, act + 1);
    *act='\0';

    prod->codigo=atoi(linea);

}

void procesarNuevoProductoTxt(void* reg, FILE* archMov, FILE* archProdTmp)
{
    Movimiento* mov = reg;
    Producto prodNuevo;

    prodNuevo.descripcion[0] = '\0';
    prodNuevo.preUni = 0;
    prodNuevo.codigo = mov->codigo;
    prodNuevo.stock = mov->cant;

    char linea[TAM_LINEA];
    while (fgets(linea, TAM_LINEA, archMov))
    {
        movTxtABin(linea, mov);
        if (mov->codigo == prodNuevo.codigo)
        {
            prodNuevo.stock += mov->cant;
        }

    }

    fprintf(archProdTmp, "%d|%s|%.2f|%d\n",
            prodNuevo.codigo,
            prodNuevo.descripcion,
            prodNuevo.preUni,
            prodNuevo.stock);
}
