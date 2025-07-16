/***************************************************************************************
******************************* Complete sus datos *************************************
****************************************************************************************
* Apellido, Nombres: Panasiuk Fabio
*
* DNI: 45.064.113
*
****************************************************************************************/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../Matriz/Matriz.h"
#include "../Vector/Vector.h"
#include "../SolucionMatrizDepositos/SolucionMatrizDepositos.h"

#define ARG_STOCKS 1
#define ARG_MOVIMIENTOS 2


int actualizarDepositos_ALU(const char* nombreStocks, const char* nombreMovimientos);
void** matrizCrear_ALU(int fil, int col, size_t tamElem);
void matrizDestruir_ALU(void** mat, int fil);
int crearVectorCodigosDepositos_ALU(const char* nombreStocks, Vector* codigosDepositos);
void actualizarStock_ALU(void* actualizado, const void* actualizador);
void actualizarVacio_ALU(void* actualizado, const void* actualizador);
int vectorTamano_ALU(const Vector* vec);
void* vectorObtenerElem_ALU(Vector* vec, int indice);
int procesarMatrizMovimientosDepositosActualizandoStocks_ALU(int** matMovDeps, const Vector* codigosDepositos, const char* nombreStocks);

int main(int argc, char* argv[])
{
	generarStocks(argv[ARG_STOCKS]);
	generarMovimientos(argv[ARG_MOVIMIENTOS]);

	puts("Stocks antes de actualizar:");
	mostrarStocks(argv[ARG_STOCKS]);

/*********************************************************************************************************************/
//	actualizarDepositos_ALU(argv[ARG_STOCKS], argv[ARG_MOVIMIENTOS]);
/************* Descomente la función de arriba y comente la de abajo para ejecutar su código. ************************/
	actualizarDepositos(argv[ARG_STOCKS], argv[ARG_MOVIMIENTOS]);
/*********************************************************************************************************************/

	puts("\nStocks despues de actualizar:");
	mostrarStocks(argv[ARG_STOCKS]);

	return 0;
}


int actualizarDepositos_ALU(const char* nombreStocks, const char* nombreMovimientos)
{
	/// Resolver. Todas las funciones que desarrolle deberán tener el sufijo _ALU.
    Vector vecCodigos;
    int cantDepositos, res;
    int** matMov;

    vectorCrear(&vecCodigos, sizeof(CodigoDeposito));
    crearVectorCodigosDepositos_ALU(nombreStocks, &vecCodigos);

    cantDepositos = vectorTamano_ALU(&vecCodigos);
    matMov = (int**)matrizCrear_ALU(cantDepositos, cantDepositos, sizeof(int));
    inicializarMatrizEnCero(matMov, cantDepositos, cantDepositos);

    cargarMatrizMovimientosDepositos(nombreMovimientos, matMov, &vecCodigos);
    //matrizMostrar(cantDepositos, cantDepositos, matMov);

    res = procesarMatrizMovimientosDepositosActualizandoStocks_ALU(matMov, &vecCodigos, nombreStocks);
    if(res != TODO_OK){
        vectorDestruir(&vecCodigos);
        matrizDestruir_ALU((void**)matMov, cantDepositos);
        return res;
    }

    vectorDestruir(&vecCodigos);
    matrizDestruir_ALU((void**)matMov, cantDepositos);
	return TODO_OK;
}

void** matrizCrear_ALU(int fil, int col, size_t tamElem){
    void** mat;
    int i, j;

    mat = malloc(sizeof(void*) * tamElem * fil);
    if(!mat){
        printf("\nError critico creando la matriz.");
        exit(SIN_MEM);
    }

    for(i = 0; i < fil; i++){
        mat[i] = malloc(tamElem * col);
        if(!mat[i]){
            printf("\nError critico creando la matriz.");
            for(j = 0; j < i; j++){
                free(mat[j]);
            }
            free(mat);
            exit(SIN_MEM);
        }
    }

    return mat;
}

void matrizDestruir_ALU(void** mat, int fil){
    int i;
    for(i = 0; i < fil; i++)
        if(mat[i])
            free(mat[i]);
    free(mat);
    mat = NULL;
}

int crearVectorCodigosDepositos_ALU(const char* nombreStocks, Vector* codigosDepositos){
    CodigoDeposito elem;
    Stock aux;
    FILE* f;

    f = fopen(nombreStocks, "rb");
    if(!f){
        printf("\nError critico armando el vector de codigos.");
        return ERR_ARCHIVO;
    }

    fread(&aux, sizeof(aux), 1, f);

    while(!feof(f)){
        strcpy(elem.codDeposito, aux.codDeposito);
        vectorOrdInsertar(codigosDepositos, &elem, cmpCodDep, actualizarVacio_ALU);
        fread(&aux, sizeof(aux), 1, f);
    }

    fclose(f);
    return TODO_OK;
}

void actualizarStock_ALU(void* actualizado, const void* actualizador){
    Stock* e_actualizado = actualizado;
    const Stock* e_actualizador = actualizador;

    e_actualizado->stock += e_actualizador->stock;
}

void actualizarVacio_ALU(void* actualizado, const void* actualizador){
    // Función que no hace nada pero tiene la estructura de Actualizar
}

int vectorTamano_ALU(const Vector* vec){
    if(!vec)
        return 0;
    return vec->ce;
}

int procesarMatrizMovimientosDepositosActualizandoStocks_ALU(int** matMovDeps, const Vector* codigosDepositos, const char* nombreStocks){
    FILE* f;
    int i, cantCodigos, depIndice, tamArch;
    Stock auxEscritura;

    cantCodigos = vectorTamano_ALU(codigosDepositos);

    f = fopen(nombreStocks, "rb+");
    if(!f){
        return ERR_ARCHIVO;
    }

    fseek(f, 0, SEEK_END);
    tamArch = ftell(f);
    fseek(f, 0, SEEK_SET);

    fread(&auxEscritura, sizeof(Stock), 1, f);
    fseek(f, -(long)sizeof(Stock), SEEK_CUR);

    while(ftell(f) <= tamArch){
        depIndice = vectorOrdBuscar(codigosDepositos, auxEscritura.codDeposito, cmpCodDep);
        for(i = 0; i < cantCodigos; i++){
            auxEscritura.stock -= matMovDeps[depIndice][i];
            auxEscritura.stock += matMovDeps[i][depIndice];
        }
        printf("\nEstoy en %ld", ftell(f));
        printf("\nEstoy en %ld", ftell(f));
        fwrite(&auxEscritura, sizeof(Stock), 1, f);
        fseek(f, (long)sizeof(Stock), SEEK_CUR);
        printf("\nEstoy en %ld", ftell(f));
        fread(&auxEscritura, sizeof(Stock), 1, f);
        fseek(f, -(long)sizeof(Stock), SEEK_CUR);
    }
/*
    fread(&auxEscritura, sizeof(Stock), 1, f);
    depIndice = vectorOrdBuscar(codigosDepositos, auxEscritura.codDeposito, cmpCodDep);
    for(i = 0; i < cantCodigos; i++){
        auxEscritura.stock -= matMovDeps[depIndice][i];
        auxEscritura.stock += matMovDeps[i][depIndice];
    }
    fseek(f, -(long)sizeof(Stock), SEEK_CUR);
    fwrite(&auxEscritura, sizeof(Stock), 1, f);
*/
    fclose(f);
    return TODO_OK;
}

void* vectorObtenerElem_ALU(Vector* vec, int indice){
    if(!vec) return NULL;
    if(!vec->vec) return NULL;
    return vec->vec+indice;
}
