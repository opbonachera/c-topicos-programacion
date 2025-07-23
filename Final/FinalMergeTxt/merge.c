#include "merge.h"


int  consolidarArchivoCargos(const char* nombreArchCargosOld,
                             const char* nombreArchCargosNuevo,
                             LineaAEst lineaCargoAEst,
                             Cmp cmpLegajos,
                             Cmp cmpCodCargo)
{
    FILE* archCargosConsolidado = fopen("cargos.txt", "w");
    if(!archCargosConsolidado)
        return ERROR;

    FILE* archCargosOld = fopen(nombreArchCargosOld, "r");
    if(!archCargosOld)
    {
        printf("Error abriendo archivo (%s)\n", nombreArchCargosOld);
        fclose(archCargosConsolidado);
        return ERROR;
    }

    FILE* archCargosNew = fopen(nombreArchCargosNuevo, "r");
    if(!archCargosNew)
    {
        printf("Error abriendo archivo (%s)\n", nombreArchCargosNuevo);
        fclose(archCargosConsolidado);
        fclose(archCargosOld);
        return ERROR;
    }

    FILE* archErrores = fopen("errores.txt", "w");
    if(!archErrores)
    {
        printf("Error abriendo archivo (%s)\n", "errores.txt");
        fclose(archCargosConsolidado);
        fclose(archCargosOld);
        fclose(archCargosNew);
        return ERROR;
    }

    void* cargoNew = malloc(sizeof(tCargo));
    if(!cargoNew)
        return ERROR;

    void* cargoOld = malloc(sizeof(tCargo));
    if(!cargoOld)
    {
        free(cargoNew);
        return ERROR;
    }

    int tamLineaArchOld = obtenerTamMaxLinea(archCargosOld);
    int tamLineaArchNew = obtenerTamMaxLinea(archCargosNew);

    char* lineaOld = malloc(tamLineaArchOld);
    if(!lineaOld)
        return ERROR;

    char* lineaNew = malloc(tamLineaArchNew);
    if(!lineaNew)
    {
        free(lineaOld);
        return ERROR;
    }

    fgets(lineaNew, tamLineaArchNew, archCargosNew);
    fgets(lineaOld, tamLineaArchOld, archCargosOld);
    while(!feof(archCargosNew) && !feof(archCargosOld))
    {
        lineaCargoAEst(lineaNew, cargoNew);
        lineaCargoAEst(lineaOld, cargoOld);

        tCargo* cNew = cargoNew;
        tCargo* cOld = cargoOld;

        int cmp = cOld->legajo - cNew->legajo;

        printf("Comparando '%s' vs '%s'  %d\n", cNew->codCargo, cOld->codCargo, cmpCodCargo(&cNew->codCargo, &cOld->codCargo));


        if(cmp==0)
        {
            if(cmpCodCargo(&cNew->codCargo, &cOld->codCargo) != 0)
            {
                fprintf(archErrores,"%d|%s|%s\n", cNew->legajo, cNew->codCargo, cNew->suc);
                fprintf(archErrores,"%d|%s|%s\n", cOld->legajo, cOld->codCargo, cOld->suc);
            }else
            {
                fprintf(archCargosConsolidado,"%d|%s|%s\n", cNew->legajo, cNew->codCargo, cNew->suc);
            }

            fgets(lineaNew, tamLineaArchNew, archCargosNew);
            fgets(lineaOld, tamLineaArchOld, archCargosOld);
        }

        if(cmp>0)
        {
            fprintf(archCargosConsolidado,"%d|%s|%s\n", cNew->legajo, cNew->codCargo, cNew->suc);
            fgets(lineaNew, tamLineaArchNew, archCargosNew);
        }

        if(cmp<0)
        {
            fprintf(archCargosConsolidado,"%d|%s|%s\n", cOld->legajo, cOld->codCargo, cOld->suc);
            fgets(lineaOld, tamLineaArchOld, archCargosOld);
        }

    }

    while(fgets(lineaNew, tamLineaArchNew, archCargosNew))
    {

        lineaCargoAEst(lineaNew, cargoNew);
        tCargo* cNew = cargoNew;

        fprintf(archCargosConsolidado,"%d|%s|%s\n", cNew->legajo, cNew->codCargo, cNew->suc);

    }

    while(fgets(lineaOld, tamLineaArchOld, archCargosOld))
    {
        lineaCargoAEst(lineaOld, cargoOld);
        tCargo* cOld = cargoOld;

        fprintf(archCargosConsolidado,"%d|%s|%s\n", cOld->legajo, cOld->codCargo, cOld->suc);

    }

    free(lineaOld);
    free(lineaNew);
    free(cargoNew);
    free(cargoOld);

    fclose(archCargosConsolidado);
    fclose(archCargosOld);
    fclose(archCargosNew);

    return OK;
}

int obtenerTamMaxLinea(FILE* arch)
{
    char linea[100];

    if (!fgets(linea, sizeof(linea), arch))
        return -1;

    char* act = strrchr(linea, '\n');
    if (act) *act = '\0';

    return atoi(linea);
}

int  lineaCargoAEst(char* linea, void* reg)
{
    char* act=strchr(linea, '\n');
    if(!act)
        return ERROR;
    *act='\0';

    tCargo* cargo = reg;

    act=strrchr(linea,'|');
    strcpy(cargo->codCargo, act + 1);
    *act='\0';

    act=strrchr(linea, '|');
    strcpy(cargo->suc, act + 1);
    *act='\0';

    cargo->legajo=atoi(linea);

    return OK;
}

int  procesarCargoConError(FILE* archErrores, void* reg);

int cmpCodCargo(const void* e1, const void* e2)
{
    return strcmp((const char*) e1, (const char*) e2);
}


int  cmpCodLegajo(const void* e1, const void* e2)
{
    return *(int*)e1 - *(int*)e2;
}
