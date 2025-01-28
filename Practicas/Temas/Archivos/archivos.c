#include "archivos.h"


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

    FILE* archivo = fopen(nomArch,"wb");

    if(!archivo)
    {
        return false;
    }

    fwrite(&vEmps, sizeof(Empleado), sizeof(vEmps) / sizeof(Empleado), archivo);
    fclose(archivo);

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

bool esErrorFatal(int ret)
{
    return (ret == ERROR_LINEA_LARGA) ? true : false;
}

int archivoBinATxt(const char* nomArchBin, const char* nomArchTxt, size_t tamReg, BinATxt binATxt)
{
    FILE* archivoBin = fopen(nomArchBin, "rb");

    if(!archivoBin)
    {
        return ERROR_APERTURA_ARCHIVO;
    }

    FILE* archivoTxt = fopen(nomArchTxt, "wb");
    if(!archivoTxt)
    {
        fclose(archivoBin);
        return ERROR_APERTURA_ARCHIVO;
    }

    void* reg = malloc(tamReg);

    fread(reg, tamReg, 1, archivoBin);
    while(!feof(archivoBin))
    {
        binATxt(reg, archivoTxt);
        fread(reg, tamReg, 1, archivoBin);
    }

    fclose(archivoBin);
    fclose(archivoTxt);

    return OK;
}

int archivoTxtABin(const char* nomArchTxt, const char* nomArchBin, size_t tamReg, TxtABin txtABin)
{
    FILE* archivoBin = fopen(nomArchBin, "rb");
    if(!archivoBin)
    {
        return ERROR_APERTURA_ARCHIVO;
    }

    FILE* archivoTxt = fopen(nomArchTxt, "wb");
    if(!archivoTxt)
    {
        fclose(archivoBin);
        return ERROR_APERTURA_ARCHIVO;
    }

    void* reg = malloc(tamReg);
    int ret = OK;
    char linea[TAM_LINEA];

    fgets(linea, TAM_LINEA, archivoTxt);
    while(!feof(archivoTxt) && !esErrorFatal(ret))
    {
        ret = txtABin(linea, reg);

        if(ret == OK)
        {
            fwrite(reg, tamReg, 1, archivoBin);
        }

        fgets(linea, TAM_LINEA, archivoTxt);
    }

    free(reg);

    fclose(archivoTxt);
    fclose(archivoBin);

    return OK;
}

void empleadoBinATxtVar(const void* reg, FILE* archTxt)
{
    Empleado* empleado = reg;
    fprintf(archTxt, "%d%2d%2d%4d%s%f", empleado->dni, empleado->fIngr.dia, empleado->fIngr.mes, empleado->fIngr.anio, empleado->apyn, empleado->sueldo);
}

void empleadoBinATxtFijo(const void* reg, FILE* archTxt)
{
    Empleado* empleado = reg;
    fprintf(archTxt, "%d|%2d%2d%4d|%s|%f", empleado->dni, empleado->fIngr.dia, empleado->fIngr.mes, empleado->fIngr.anio, empleado->apyn, empleado->sueldo);
}

int empleadoTxtVarABin(char* linea, void* reg)
{
    char* act = strchr(linea, '\n');
    Empleado* empleado = reg;

    if(!act)
    {
        return ERROR_LINEA_LARGA;
    }

    *act = '\0';
    act = strrchr(linea, '|');
    sscanf(act + 1, "%f", empleado->sueldo);

    *act = '\0';
    act = strrchr(linea, '|');
    sscanf(act + 1, "%2d%2d%4d", empleado->fIngr.dia, empleado->fIngr.mes, empleado->fIngr.anio);

    *act = '\0';
    act = strrchr(linea, '|');
    strcpy(empleado->sexo, act+1);

    *act = '\0';
    act =  strrchr(linea, '|');
    strcpy(empleado->apyn, act+1);

    *act = '\0';
    act = strrchr(linea, '|');
    sscanf(act + 1, "%d", empleado->dni);

    return OK;
}

int empleadoTxtFijoABin(char* linea, void* reg)
{
    char* act = strchr(linea, '\n');
    Empleado* empleado = reg;

    if(!act)
    {
        return ERROR_LINEA_LARGA;
    }

    *act='\0';
    act-=9;
    sscanf(act, "%f", empleado->sueldo);

    *act = '\0';
    act-=8;
    sscanf(act, "%2d%2d%4d", empleado->fIngr.dia, empleado->fIngr.mes, empleado->fIngr.anio);

    *act = '\0';
    act--;
    empleado->sexo = *act;

    *act = '\0';
    act-=TAM_APYN;
    strcpy(empleado->apyn, act);

    sscanf(linea, "%d", empleado->dni);
    return OK;
}

