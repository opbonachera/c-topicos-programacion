#include "hmvector.h"
#include "ordenamiento.h"

void ordenarVectorQsort(Vector* vector, int inicio, int fin)
{
    if( fin <= inicio)
        return; // No more available partitions

    int pivot = partition(vector, inicio, fin);

    ordenarVectorQsort(vector, start, pivot - 1); // List of numbers to the left of pivot
    ordenarVectorQsort(vector, pivot + 1, end); // List of numbers to the right of pivot

}

void partition(Vector* vector, int inicio, int fin)
{
    int pivot = vector->vec[end]; // Always take last element of array as pivot
    int i = start - 1; // First element on the list

    for(int j=start; j<=end, j++)
    {
        if(array[j] < pivot)
        {
            i++;
            int temp = vector->vec[i];
            vector->vec[i] = vector->vec[j];
            vector->vec[j] = temp;
        }
    }

    i++;
    // Change pivot position
    int temp = vector->vec[i];
    vector->vec[i] = vector->vec[end];
    vector->vec[end] = temp;

    return i;
}
