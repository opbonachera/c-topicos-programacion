#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "../Vector/Vector.h"
#include "../TDAFecha/Fecha.h"

#define CANT_PRODS 5
#define CANT_MOVS 8
#define TAM_DESCR 15
#define TAM_APYN 30
#define TAM_LINEA 500

#define ERR_ARCHIVO 1
#define ERR_MEMORIA 2
#define ERR_LINEA_LARGA 3


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


typedef struct
{
    int dni;
    char apyn[TAM_APYN + 1];
    char sexo;
    Fecha fIngr;
    float sueldo;
}
Empleado;


typedef void (*BinATxt)(const void* reg, FILE* archTxt);
typedef int (*TxtABin)(char* linea, void* reg);


bool generarArchivoProductos(const char* nomArch);
bool generarArchivoMovimientos(const char* nomArch);
bool generarIndice(const char* nomArch, const char* nomIdx);
bool mostrarArchivo(const char* nomArch);
bool actualizarPrecioProductos(const char* nomArch, float porc);
int cmpIndProd(const void* e1, const void* e2);
bool actualizarPrecio1Producto(const char* nomArch, const char* nomIdx, int codigo, float porc);
bool actualizarStockProductos(const char* nomArchProds, const char* nomArchMovs);
void procesarProductoNuevo();
bool generarArchivoEmpleadosBin(const char* nomArch);
void mostrarArchivoEmpleadosBin(const char* nomArch);
int archivoBinATxt(const char* nomArchBin, const char* nomArchTxt, size_t tamReg, BinATxt BinATxt);
void empleadoBinATxtVar(const void* reg, FILE* archTxt);
void empleadoBinATxtFijo(const void* reg, FILE* archTxt);
int empleadoTxtVarABin(char* linea, void* reg);
int empleadoTxtFijoABin(char* linea, void* reg);
int archivoTxtABin(const char* nomArchTxt, const char* nomArchBin, size_t tamReg, TxtABin txtABin);
bool esErrorFatal(int ret);


int main()
{
    // if(!generarArchivoProductos("Productos.dat"))
    // {
    //     puts("Error generando el archivo");
    //     return 1;
    // }

    // // generarIndice("Productos.dat", "Productos.idx");

    // mostrarArchivo("Productos.dat");

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

    // generarArchivoMovimientos("Movimientos.dat");

    // actualizarStockProductos("Productos.dat", "Movimientos.dat");

    // puts("Despues de actualizar stock:");
    // mostrarArchivo("Productos.dat");


    // generarArchivoEmpleadosBin("Empleados.dat");
    // mostrarArchivoEmpleadosBin("Empleados.dat");

    archivoBinATxt("Empleados.dat", "EmpleadosVar.txt", sizeof(Empleado), empleadoBinATxtVar);
    archivoBinATxt("Empleados.dat", "EmpleadosFijo.txt", sizeof(Empleado), empleadoBinATxtFijo);

    archivoTxtABin("EmpleadosVar.txt", "Empleados.dat", sizeof(Empleado), empleadoTxtVarABin);
    puts("Bin desde Txt Var:");
    mostrarArchivoEmpleadosBin("Empleados.dat");

    archivoTxtABin("EmpleadosFijo.txt", "Empleados.dat", sizeof(Empleado), empleadoTxtFijoABin);
    puts("Bin desde Txt Fijo:");
    mostrarArchivoEmpleadosBin("Empleados.dat");


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
    vectorCrear(&
    , sizeof(IndProducto));

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


bool generarArchivoEmpleadosBin(const char* nomArch)
{
    Empleado vEmps[] =
    {
        {12345678, "Juan Perez", 'M', {1, 1, 2000}, 300000},
        {23456789, "Ana Lopez", 'F', {2, 2, 2001}, 350000},
        {34567890, "Pedro Gomez", 'M', {3, 3, 2002}, 400000},
        {45678901, "Maria Rodriguez", 'F', {4, 4, 2003}, 450000},
        {56789012, "Carlos Sanchez", 'M', {5, 5, 2004}, 500000}
    };

    FILE* archEmps = fopen(nomArch, "wb");

    if(!archEmps)
    {
        return false;
    }

    fwrite(vEmps, sizeof(Empleado), 5, archEmps);

    fclose(archEmps);

    return true;
}


void mostrarArchivoEmpleadosBin(const char* nomArch)
{
    FILE* archEmps = fopen(nomArch, "rb");

    if(!archEmps)
    {
        return;
    }

    Empleado emp;

    fread(&emp, sizeof(Empleado), 1, archEmps);
    while(!feof(archEmps))
    {
        printf("%8d, %-*s, %c, %02d/%02d/%04d, %09.2f\n", emp.dni, TAM_APYN, emp.apyn, emp.sexo, emp.fIngr.dia, emp.fIngr.mes, emp.fIngr.anio, emp.sueldo);
        fread(&emp, sizeof(Empleado), 1, archEmps);
    }

    fclose(archEmps);
}


int archivoBinATxt(const char* nomArchBin, const char* nomArchTxt, size_t tamReg, BinATxt binATxt)
{
    FILE* archBin = fopen(nomArchBin, "rb");

    if(!archBin)
    {
        return ERR_ARCHIVO;
    }

    FILE* archTxt = fopen(nomArchTxt, "wt");

    if(!archTxt)
    {
        fclose(archBin);
        return ERR_ARCHIVO;
    }

    void* reg = malloc(tamReg);

    if(!reg)
    {
        fclose(archBin);
        fclose(archTxt);
        return ERR_MEMORIA;
    }

    fread(reg, tamReg, 1, archBin);
    while(!feof(archBin))
    {
        binATxt(reg, archTxt);
        fread(reg, tamReg, 1, archBin);
    }

    free(reg);

    fclose(archBin);
    fclose(archTxt);

    return TODO_OK;
}


void empleadoBinATxtVar(const void* reg, FILE* archTxt)
{
    const Empleado* empl = reg;
    fprintf(archTxt, "%d|%s|%c|%d/%d/%d|%.2f\n", empl->dni, empl->apyn, empl->sexo, empl->fIngr.dia, empl->fIngr.mes, empl->fIngr.anio, empl->sueldo);
}


void empleadoBinATxtFijo(const void* reg, FILE* archTxt)
{
    const Empleado* empl = reg;
    fprintf(archTxt, "%08d%-*s%c%02d%02d%4d%09.2f\n", empl->dni, TAM_APYN, empl->apyn, empl->sexo, empl->fIngr.dia, empl->fIngr.mes, empl->fIngr.anio, empl->sueldo);
}


int archivoTxtABin(const char* nomArchTxt, const char* nomArchBin, size_t tamReg, TxtABin txtABin)
{
    FILE* archTxt = fopen(nomArchTxt, "rt");

    if(!archTxt)
    {
        return ERR_ARCHIVO;
    }

    FILE* archBin = fopen(nomArchBin, "wb");

    if(!archBin)
    {
        fclose(archTxt);
        return ERR_ARCHIVO;
    }

    void* reg = malloc(tamReg);

    if(!reg)
    {
        fclose(archBin);
        fclose(archTxt);
        return ERR_MEMORIA;
    }

    int ret = TODO_OK;
    char linea[TAM_LINEA];

    fgets(linea, TAM_LINEA, archTxt);
    while(!feof(archTxt) && !esErrorFatal(ret))
    {
        ret = txtABin(linea, reg);
        
        if(ret == TODO_OK)
        {
            fwrite(reg, tamReg, 1, archBin);
        }

        fgets(linea, TAM_LINEA, archTxt);
    }

    fclose(archBin);
    fclose(archTxt);
    free(reg);

    return TODO_OK;
}


int empleadoTxtVarABin(char* linea, void* reg)
{
    Empleado* empl = reg;

    char* act = strchr(linea, '\n');

    if(!act)
    {
        return ERR_LINEA_LARGA;
    }

    *act = '\0';
    act = strrchr(linea, '|');
    sscanf(act + 1, "%f", &empl->sueldo);

    *act = '\0';
    act = strrchr(linea, '|');
    sscanf(act + 1, "%d/%d/%d", &empl->fIngr.dia, &empl->fIngr.mes, &empl->fIngr.anio);

    *act = '\0';
    act = strrchr(linea, '|');
    empl->sexo = *(act + 1);

    *act = '\0';
    act = strrchr(linea, '|');
    strcpy(empl->apyn, act + 1);

    *act = '\0';
    sscanf(linea, "%d", &empl->dni);

    return TODO_OK;
}


int empleadoTxtFijoABin(char* linea, void* reg)
{
    Empleado* empl = reg;

    char* act = strchr(linea, '\n');

    if(!act)
    {
        return ERR_LINEA_LARGA;
    }

    *act = '\0';
    act -= 9;
    sscanf(act, "%f", &empl->sueldo);

    *act = '\0';
    act -= 8;
    sscanf(act, "%2d%2d%4d", &empl->fIngr.dia, &empl->fIngr.mes, &empl->fIngr.anio);

    *act = '\0';
    act--;
    empl->sexo = *act;

    *act = '\0';
    act -= TAM_APYN;
    strcpy(empl->apyn, act);

    *act = '\0';
    sscanf(linea, "%d", &empl->dni);
    
    return TODO_OK;
}



bool esErrorFatal(int ret)
{
    if(ret == ERR_LINEA_LARGA)
    {
        return true;
    }

    return false;
}