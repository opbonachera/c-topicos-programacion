#include <stdio.h>
#include <string.h>

#include "ordenamiento.h"

int burbujeoInt(int *vec, const int ce)
{
    int *ult = vec + ce-1; // Ultima direccion de memoria dentro del vector
    int contador = 0;

    for(int i=0; i<ce; i++)
    {
        for(int *j=vec; j< ult-i ; j++)
        {
            if(*j > *(j+1))
            {
                intercambiar(j, j+1);
            }
            contador++;
        }
    }

    printf("Cantidad de pasadas: %d\n", contador);
    return 0;
}

int intercambiar(int* x, int* y)
{
    int *temp = *x;
    *x = *y;
    *y = temp;
    return 0;
}

int ordenarBurbujeoGenerico(t_lista *pL, Cmp cmp)
{
    void *ult = pL->vec + (pL->ce) - 1 * (pL->tamElem);

    // *i = primer elemento en el vector
    // mientras i sea menor que el ultimo elemento
    // incrementamos i segun el tamaño de los elementos segun el tipo de dato del vector
    for(void *i = pL->vec; i<ult; i+= pL->tamElem)
    {
        for(void *j=i; j<ult; j+=tamElem)
        {
            if(cmp(j, j+pL->tamElem)<0)
            {
                //intercambiar(j, j+pL->tamElem, pL->tamElem);
            }
        }
    }
}

int printVector(int *vec, const int ce)
{
    int i;
    for(i=0; i<ce; i++)
    {
        printf("%d ", *vec);
        vec++;
    }
    return 0;
}
