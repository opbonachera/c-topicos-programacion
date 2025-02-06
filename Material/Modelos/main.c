/*
REVISION ULTIMO PARCIAL

ERRORES COMETIDOS EN EL PARCIAL:
~ Mala planificación y comprensión del texto
~ Realizar varios archivos para guardar las funciones (todo en uno debe ser)
~ Realizar funciones de más que no fueron pedidas
~ No conocer la lectura de un archivo en orden inverso (problema del docente)
~ No prestar atención a los warnigs
~ No cerrar el proyecto y archivos antes de guardarlo
Extra:
~ La mayoria interpreto que se debia realizar la lectura de permutaciones de abajo para arriba, cuando era el opuesto

DETALLES:
~ El profesor realizo un error al tomar algo que no debia
~ La dificultad en verdad era facil, la mayoria son cosas de la guia. Solo era muy ambiguo

Lo importante comienza en la funcion "restaurarArchClientesALU" de la linea 318, y el proceso mas importante en la linea 376

*/
#include <stdio.h>
#include <stdlib.h>

// Valores Varios
#define MAXCLI 50000 // Se debe consultar si se crean 50000 espacios, o se crea una cantidad baja pero se va extendiendo
#define BUFFER 650
#define SEP '|'
#define EXTTDA 50

// Retorno funciones
#define EXITO 1
#define ERROR 0
#define ERROR_ARCH -1
#define ERROR_MALL -2
#define ERROR_LLEN -3

// Nombre Archivos
#define ARCHCLIENTE     "clientes.txt"
#define ARCHCLIENTEPERM "clientesPermutado.txt"
#define ARCHCLIENTEREST "clientesRestaurado.txt"
#define ARCHPERM        "perm.txt"

// ESTRUCTURAS
#define TAMNOM 64
#define TAMCOD 512
typedef struct
{
    int leg;
    char nom[TAMNOM];
    char cod[TAMCOD];
    float saldo;
} tCliente;

#define TAMPOS 5
typedef struct
{
    size_t pos1;
    size_t pos2;
} tPos;

typedef struct
{
    void* dir;
    size_t lon;
    size_t cantEl;
    size_t tamEl;
} tVec;

// GENERALES
void* tMemcpy(void *dest, void *ori, size_t bytes);
void intercambio(void *el1, void *el2, size_t bytes);

// TDA
int crearTVec(tVec *TDA, const size_t lon, const size_t tamEl);
void destruirTVec(tVec *TDA);
int extenderTVec(tVec *TDA, const size_t lonNue);
int ingUltTVec(tVec *TDA, void *ingreso);
void mapTVec(tVec *TDA, void accion(void*));

// STR
char* tStrrchr(char *str, char bus);
char* tStrcpy(char *dest, char *ori);

// TROZADOS
void trozarCli(char *linea, void *el);
void trozarInvCli(char *linea, void *el);
void trozarPos(char *linea, void*el);
void trozarInvPos(char *linea, void*el);

// PROCESOS PRINCIPALES
void intercambioSaldo(tVec *listCli, tPos *posPerm);
//int permutarArchClientesALU(const char* archOri, const char* archDes);
int restaurarArchClientesALU(const char* archOri, const char* archDes);

int main()
{
    restaurarArchClientesALU(ARCHCLIENTEPERM, ARCHCLIENTEREST);

    puts("\n-FIN-");
    return 0;
}

/*
================================
GENERALES
================================
*/
void* tMemcpy(void *dest, void *ori, size_t bytes)
{
    void *ini = dest;
    while(bytes--)
        *(char*)dest++ = *(char*)ori++;
    return ini;
}

void intercambio(void *el1, void *el2, size_t bytes)
{
    char *ec1 = (char*)el1,
         *ec2 = (char*)el2,
         aux;

    while(bytes--)
    {
        aux = *ec1;
        *ec1 = *ec2;
        *ec2 = aux;

        ec1++;
        ec2++;
    }
}

/*
================================
TDA
================================
*/
int crearTVec(tVec *TDA, const size_t lon, const size_t tamEL)
{
    if(!(TDA->dir = malloc(lon * tamEL)))
    {
        return ERROR_MALL;
    }

    TDA->lon = lon;
    TDA->cantEl = 0;
    TDA->tamEl = tamEL;

    return EXITO;
}

void destruirTVec(tVec *TDA)
{
    if(TDA->dir)
    {
        free(TDA->dir);
    }

    TDA->lon = 0;
    TDA->cantEl = 0;
    TDA->tamEl = 0;
}

int extenderTVec(tVec *TDA, const size_t lonNue)
{
    void *auxDir;

    if(!(auxDir = realloc(TDA->dir, lonNue * TDA->tamEl)))
    {
        return ERROR;
    }

    TDA->dir = auxDir;
    TDA->lon = lonNue;
    return EXITO;
}

int ingUltTVec(tVec *TDA, void *ingreso)
{
    if(TDA->cantEl >= TDA->lon && extenderTVec(TDA, TDA->lon + EXTTDA) != EXITO)
        return ERROR_LLEN;

    void *fin = TDA->dir + TDA->cantEl * TDA->tamEl;

    tMemcpy(fin,ingreso,TDA->tamEl);
    TDA->cantEl++;
    return EXITO;
}

void mapTVec(tVec *TDA, void accion(void*))
{
    void *ini = TDA->dir;
    void *fin = TDA->dir + TDA->cantEl * TDA->tamEl;

    while(ini < fin)
    {
        accion(ini);
        ini += TDA->tamEl;
    }
}

/*
================================
STR
================================
*/
char* tStrrchr(char *str, char bus)
{
    char *pos = NULL;

    while(*str)
    {
        if(*str == bus)
            pos = str;
        str++;
    }

    return pos;
}

char* tStrcpy(char *dest, char *ori)
{
    char *ini = dest;
    while(*ori)
    {
        *dest = *ori;
        dest++;
        ori++;
    }

    *dest = '\0';
    return ini;
}

/*
================================
TROZAR
================================
*/
void trozarCli(char *linea, void *el)
{
    tCliente *cli = (tCliente*)el;
    char *dir;

    if(!(dir = tStrrchr(linea,'\n')))
        return ERROR;
    *dir = '\0';

    if(!(dir = tStrrchr(linea,SEP)))
        return ERROR;
    sscanf(dir+1,"%f",&cli->saldo);
    *dir = '\0';

    if(!(dir = tStrrchr(linea,SEP)))
        return ERROR;
    tStrcpy(cli->cod,dir+1);
    *dir = '\0';

    if(!(dir = tStrrchr(linea,SEP)))
        return ERROR;
    tStrcpy(cli->nom,dir+1);
    *dir = '\0';

    sscanf(linea,"%d",&cli->leg);
}

void trozarInvCli(char *linea, void *el)
{
    tCliente *ec = (tCliente*)el;
    sprintf(linea,"%d|%s|%s|%.2f\n",ec->leg,ec->nom,ec->cod,ec->saldo);
}

void trozarPos(char *linea, void*el)
{
    tPos *pos = (tPos*)el;
    char *dir = linea + TAMPOS + TAMPOS;

    *dir = '\0';

    dir -= TAMPOS;
    sscanf(dir,"%u",&pos->pos2);
    dir = '\0';

    sscanf(linea,"%u",&pos->pos1);
}

void trozarInvPos(char *linea, void*el)
{
    tPos *pos = (tPos*)el;
    sprintf(linea,"%5d%5d\n",pos->pos1,pos->pos2);
}

/*
================================
MOSTRAR
================================
*/
void mostrarCli(void *el)
{
    tCliente *elC = (tCliente*)el;
    printf("%5d %20s %20s %6.2f\n", elC->leg ,elC->nom, elC->cod, elC->saldo);
}

/*
================================
PROCESO PRINCIPALES
================================
*/

void intercambioSaldo(tVec *listCli, tPos *posPerm)
{
    tCliente *interC1 = listCli->dir + posPerm->pos1 * listCli->tamEl;
    tCliente *interC2 = listCli->dir + posPerm->pos2 * listCli->tamEl;

    intercambio(&interC1->saldo, &interC2->saldo, sizeof(float));
}

int restaurarArchClientesALU(const char* archOri, const char* archDes){
    // Variables para manipular archivos
    FILE *fileOri, *fileDes, *filePerm;
    char linea[BUFFER];
    long int posTell;

    // Variables para manipular vector
    tVec listCli;
    void *ini, *fin, *pos;

    // Variables auxiliares
    tPos posPerm;
    tCliente cliAux;

    if(!(fileOri = fopen(archOri,"rt"))) // Lectura archivo permutado
    {
        return ERROR_ARCH;
    }

    if(!(fileDes = fopen(archDes,"wt"))) // Escribir archivo restaurado
    {
        fclose(fileOri);
        return ERROR_ARCH;
    }

    if(!(filePerm = fopen(ARCHPERM,"rt"))) // Lista permutaciones
    {
        fclose(fileOri);
        fclose(fileDes);
        return ERROR_ARCH;
    }

    if(crearTVec(&listCli,MAXCLI,sizeof(tCliente)) <= 0)
    {
        fclose(fileOri);
        fclose(fileDes);
        fclose(filePerm);
        return ERROR_MALL;
    }

    ///=================================
    /// CARGAMOS CLIENTES AL VECTOR
    ///=================================
    while(fgets(linea,BUFFER,fileOri))
    {
        trozarCli(linea,&cliAux);
        ingUltTVec(&listCli, &cliAux);
    }
    fclose(fileOri);
    ///=================================

    puts("\nARCHIVO PERMUTADO:");
    mapTVec(&listCli, mostrarCli);

    ///=================================
    /// RETROCEDEMOS LAS PERMUTACIONES
    ///=================================
    // Lectura de abajo para arriba
    fseek(filePerm, 0, SEEK_END);
    posTell = ftell(filePerm) - 2; // Se resta 2 por el salto de linea final

    while (posTell > 0) {
        if (fgetc(filePerm) == '\n')
        {
            if (posTell == 0)
                fseek(filePerm, posTell, SEEK_SET);
            posTell--;
            fgets(linea, BUFFER, filePerm);

            trozarPos(linea,&posPerm);
            intercambioSaldo(&listCli,&posPerm);
        }

        fseek(filePerm, --posTell, SEEK_SET);
    }
    fclose(filePerm);

    /*
    COMENTARIO:
    La manera eficiente de resolverlo es leer el archivo de permutaciones de abajo para arriba,
    en cual es un error del docente ya que nunca fue visto en la materia la lectura de un archivo de texto
    en ese orden. Por lo que la otra manera de resolverlo es crear otro TDA de la misma longitud que los clientes,
    cargar las permutaciones y comenzar a leer el vector en el orden invertido.
    */

    ///=================================
    /// INSERTAMOS VECTOR CLIENTER AL ARCHIVO
    ///=================================
    ini = listCli.dir;
    fin = listCli.dir + listCli.cantEl * listCli.tamEl;
    pos = ini;
    while(pos < fin)
    {
        trozarInvCli(linea,pos);
        fputs(linea,fileDes);
        pos += listCli.tamEl;
    }
    fclose(fileDes);
    ///=================================

    puts("\nARCHOVO RESTAURADO:");
    mapTVec(&listCli, mostrarCli);

    destruirTVec(&listCli);
    return 0;
}
