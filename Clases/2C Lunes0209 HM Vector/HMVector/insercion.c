#include "hmvector.h"
#include "ordenamiento.h"

void ordenarVectorInsercion(Vector* vector)
{
    for(int i=1; i<vector->ce; i++)
    {
        int pos = vector->vec[i];
        int j= i - 1;

        while (j >= 0 && vector->vec[j] > pos) {
            vector->vec[j + 1] = vector->vec[j];
            j = j - 1;
        }
        vector->vec[j + 1] = pos;

    }
}
