#include "vector.h"

int inicializarVector(t_vector* vect)
{
    printf("--- Inicializando vector ---\n");
    /*
    printf("Ingrese la cantidad de elementos (max: %d): ", TAM);
    scanf("%d", &vect->ce);

    int *v = vect->vec;

    for(int i=0; i<vect->ce; i++)
    {
        *v = i + 1;
        v++;
    }*/

    vect->ce = 4;

    vect->vec[0] = 1;
    vect->vec[1] = 3;
    vect->vec[2] = 4;
    vect->vec[3] = 5;

    printf("Vector inicializado correctamente. \n");

    return OK;
}

int imprimirVector(t_vector* vect)
{
    printf("Cantidad de elementos: %d\n", vect->ce);

    int* v = vect->vec;

    for(int i = 0; i < vect->ce; i++)
    {
        printf("%d ", *v);
        v++;
    }

    printf("\n");

    return OK;
}

int ordenarVector(t_vector* vect);

int insertarElementoVectorOrdenado(t_vector* vect, int elemento)
{
    // CASO 1: VECTOR LLENO
    if(vect->ce == TAM)
    {
        printf("El vector no tiene más espacio.\n");
        return VECTOR_LLENO;
    }

    // CASO 2: ELEMENTO DUPLICADO
    if(existeElemento(vect, elemento))
    {
        printf("El elemento %d ya se encuentra en el vector y no se admiten duplicados.\n", elemento);
        return ELEMENTO_DUPLICADO;
    }

    int posIns=0;

    /*int* v = vect->vec;
    for(int i=0; i<vect->ce; i++)
    {
        if( *v > elemento )
        {
            posIns = i; // Si el elemento de la iteración es menor que el elemento a insertar, incrementar
            break;
        }
        else
            v++; // Si el elemento de la iteración es mayor al elemento a insertar, capturar su posición;
    }*/ /*Esta version no contempla el caso en el que el numero es mayor a todos*/

    while(posIns < vect->ce && elemento > vect->vec[posIns])
    {
        posIns++;
    }

    for(int i=vect->ce-1; i>=posIns; i--)
    {
        vect->vec[i+1]=vect->vec[i]; // Desplazamos todos los elementos 1 lugar a la derecha
    }

    vect->vec[posIns] = elemento;
    vect->ce++;

    return OK;
}

int existeElemento(t_vector* vect, int elemento)
{
    return 0;
}

int removerElementoVectorOrdenado(t_vector* vect, int elemento)
{
    if(vect->ce == 0)
    {
        printf("El vector esta vacio.\n");
        return VECTOR_VACIO;
    }

    int posElim = 0;
    while(posElim < vect->ce && elemento > vect->vec[posElim])
    {
        posElim++;
    }

    if(posElim == v->ce || elem<v->vec[posElim])
    {
        return 1;
    }

    return OK;
}

