#include <stdio.h>
#include <stdlib.h>

#define TAM 5

typedef struct
{
    int cant;
    int vec[TAM];
}t_vector;

void vectorInicializar(t_vector *);
void vectorMostrar(t_vector *);
void moverElementos(t_vector *);
int vectorInsertar(t_vector *, int);
int vectorInsertarEnPosicion(t_vector *, int, int);
int vectorEliminarPorValor(t_vector *, int);
int vectorEliminarPorPosicion(t_vector *, int);
int filtrarNulos(t_vector *);
// Array: Inicializar, mostrar, insertar, eliminar

int main()
{
    int vector[TAM];

    vectorInicializar(vector);

    vectorInsertar(vector, 1);
    vectorInsertar(vector, 9);
    vectorInsertar(vector, 5);
    vectorInsertar(vector, 3);

    vectorInsertarEnPosicion(vector, 120, 2);
    vectorMostrar(vector);
    vectorEliminarPorPosicion(vector, 2);

    filtrarNulos(vector);
    vectorMostrar(vector);
}

void vectorInicializar(t_vector *p)
{
    p->cant = 0;
}

int vectorInsertarEnPosicion(t_vector *p, int num, int pos)
{
    if(p->cant == TAM) return;

    int i = p->cant - 1;

    for(i; i >= pos; i--) {
        p->vec[i] = p->vec[i-1];
    }

    p->vec[pos - 1] = num;

}

int filtrarNulos(t_vector *p)
{
    int i = p->cant - 1;

    for (i; i >= 0; i--)
    {
        if (p->vec[i] == 0)
        {
            for (int j = i; j < p->cant - 1; j++)
            {
                p->vec[j] = p->vec[j + 1];
            }
            --p->cant;
        }
    }

    return 0;
}

int vectorInsertar(t_vector *p, int num)
{
    if(p->cant == TAM) return 0;

    p->vec[p->cant] = num;

    return ++p->cant;
}

int vectorEliminarPorValor(t_vector *p, int num)
{
    int i;
    for(i=0; i < p->cant; i++)
    {
        if(p->vec[i] == num)
        {
            p->vec[i] = 0;
            printf("Elemento eliminado por valor.");
            return 0;
        }
    }

    return 1;
}



int vectorEliminarPorPosicion(t_vector *p, int pos)
{
    int i;
    for(i=0; i<p->cant; i++)
    {
        if(i == pos)
        {
            p->vec[i] = 0;
            return 0;
        }
    }
    return 1;
}



void vectorMostrar(t_vector *p)
{
    int i;

    printf("\nMostrando elementos no nulos...\n");

    for(i=0; i < p->cant; i++)
    {
        if(p->vec[i])
        {
            printf("Posicion: %d - Elemento: %d \n", i, p->vec[i]);
        }
    }
}

