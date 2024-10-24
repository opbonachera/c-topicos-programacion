#include "archivos.h"

int archivoTxtABin(const char* nomArchTxt, const char* nomArchBin, size_t tamReg, TxtABin txtABin)
{
    FILE* archivoTxt = fopen(nomArchTxt, "rb");
    if(!archivoTxt)
    {
        return ERROR_APERTURA_ARCHIVO;
    }

    FILE* archivoBin = fopen(nomArchBin, "wb");
    if(!archivoBin)
    {
        return ERROR_APERTURA_ARCHIVO;
    }

    void* reg = malloc(tamReg);
    char linea[TAM_LINEA];
    int ret = OK;

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

int archivoBinATxt(const char* nomArchBin, const char* nomArchTxt, size_t tamReg, BinATxt BinATxt)
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
        BinATxt(reg, archivoTxt);
        fread(reg, tamReg, 1, archivoBin);
    }

    free(reg);
    fclose(archivoBin);
    fclose(archivoTxt);

    return OK;
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


int empleadoTxtFijoABin(char* linea, void* reg)
{
    Empleado* e = reg;
    char* act = strchr(linea, '\n');

    if(!act)
    {
        return ERROR_LINEA_LARGA;
    }

    *act = '\0';
    act-=9;
    sscanf(act, "%f", &e->sueldo);

    *act = '\0';
    act-=8;
    sscanf(act, "%2d%2d%4d", &e->fIngr.dia, &e->fIngr.mes, &e->fIngr.anio);

    *act = '\0';
    act--;
    sscanf(act, "%c", &e->sexo);

    *act = '\0';
    act -= TAM_APYN;
    strcpy(e->apyn, act);

    *act = '\0';
    sscanf(linea, "%d", &e->dni);

    return OK;
}

int empleadoTxtVarABin(char* linea, void* reg)
{
    Empleado* empl = reg;

    char* act = strchr(linea, '\n');

    if(!act)
    {
        return ERROR_LINEA_LARGA;
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

    return OK;
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

bool esErrorFatal(int ret)
{
    if(ret == ERROR_LINEA_LARGA)
    {
        return true;
    }
    return false;
}
