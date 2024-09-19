#include "hmvector.h"
#include "ordenamiento.h"

void ordenarVectorInsercion(Vector* vector)
{
    for(int i=1; i<vector->ce; i++)
    {
        int element = vector->vec[i];
        int j= i - 1; // Element to the left of i

        while (j >= 0 && vector->vec[j] > element) {
            vector->vec[j + 1] = vector->vec[j]; // Move all elements to the right
            j--;
        }
        vector->vec[j + 1] = element;

    }
}
