#include "hmvector.h"
#include "ordenamiento.h"


void ordenarVectorBurbujeo(Vector* vector)
{
    for(int i=0; i<vector->ce; i++)
    {
        for(int j=0; j<vector->ce - 1 - i; j++)
        {
            if(vector->vec[j] < vector->vec[j+1])
                intercambiarElemento(vector->vec[j], vector->vec[j+1], sizeof(int));
        }
    }
}
