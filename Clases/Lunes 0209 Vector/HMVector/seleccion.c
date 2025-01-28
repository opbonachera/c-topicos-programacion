#include "hmvector.h"
#include "ordenamiento.h"

int vectorEnterosOrdenarSeleccion(int vector[], int ce)
{
    int ult = ce - 1;
    for (int i = 0; i < ult; i++) {
        int min = i;
        for (int j = i + 1; j < ce; j++) {
            if (vector[j] < vector[min]) {
                min = j;
            }
        }
        intercambiarElemento(&vector[i], &vector[min], sizeof(int));
    }
    return OK;
}

void vectorOrdenarSeleccion(Vector* vector)
{
    int ult = vector->ce - 1;
    for (int i = 0; i < ult; i++) {
        int min = i;
        for (int j = i + 1; j < vector->ce; j++) {
            if (vector->vec[j] < vector->vec[min]) {
                min = j;
            }
        }
        intercambiarElemento(&vector->vec[i], &vector->vec[min], sizeof(int));
    }
}
