#include "VectorGenerico.h"
#include "Ordenamiento.h"


// ---- BURBUJEO ------
int ordenarVectorEnterosBurbujeoSinOpt(VectorGenerico* vector)
{
    int counter=0;

    for(int i=0; i<vector->ce; i++)
    {
        for(int j=0; j<vector->ce - 1 - i; j++)
        {
            if(vector->vec[j] > vector->vec[j+1])
            {
                int temp = vector->vec[j];
                vector->vec[j] = vector->vec[j+1];
                vector->vec[j+1] = temp;

                counter++;
            }
        }

    }

    printf("Ordered array passing %d times\n", counter);

    return 0;
}

int ordenarVectorEnterosBurbujeoOptimizado1(VectorGenerico* vector)
{
    int temp, flag = 1, counter = 0;

    for(int i = 0; i < vector->ce; i++)
    {
        flag = 0;

        for(int j = 0; j < vector->ce - 1 - i; j++)
        {
            if(vector->vec[j] > vector->vec[j + 1])
            {

                temp = vector->vec[j];
                vector->vec[j] = vector->vec[j + 1];
                vector->vec[j + 1] = temp;

                flag = 1;
                counter++;
            }
        }

        if(!flag)
            break;
    }

    printf("Vector ordenado en %d pasadas\n", counter);

    return 0;
}

int ordenarVectorEnterosBurbujeoOptimizado2(VectorGenerico* vector)
{
    int flag = 1, i, counter=0;

    while(flag && i < vector->ce)
    {
        flag = 0;

        for(int j=0; j<vector->ce - i; j++)
        {
                if(vector->vec[j]>vector->vec[j+1])
                {
                        int temp = vector->vec[j];
                        vector->vec[j] = vector->vec[j+1];
                        vector->vec[j+1] = temp;

                        flag=1;
                        counter++;
                }
        }
        i++;
    }

     printf("Vector ordenado en %d pasadas\n", counter);
     return 0;
}

// ---- SELECCION ------
int ordenarVectorSeleccion(VectorGenerico* vector)
{
    int menor, counter = 0;

    for (int i = 0; i < vector->ce - 1; i++)
    {
        menor = buscarMenor(vector->vec, i, vector->ce - 1);

        if (menor != i)
        {
            int temp = vector->vec[i];
            vector->vec[i] = vector->vec[menor];
            vector->vec[menor] = temp;

            counter++;
        }
    }

    printf("Vector ordenado en %d pasadas\n", counter);

    return 0;
}

int buscarMenor(int* vector, int desde, int hasta)
{
    int m = desde;

    for (int j = desde + 1; j <= hasta; j++)
    {
        if (vector[j] < vector[m])
        {
            m = j;
        }
    }

    return m;
}

// ---- INSERCION ------
int ordenarVectorEnterosInsercion(VectorGenerico* vector)
{
    int j, elementoAInsertar, counter=0;

    for(int i=1; i<vector->ce; i++)
    {
        elementoAInsertar = vector->vec[i];
        j=i-1;

        while(j>=0 &&elementoAInsertar<=vector->vec[j])
        {
            vector->vec[j+1] = vector->vec[j];
            j--;
            counter++;
        }

        vector->vec[j+1] = elementoAInsertar;
    }

    printf("Vector ordenado en %d pasadas\n", counter);
    return 0;
}

// ---- QSORT ------
void ordenarVectorQsort(Vector* vector, int inicio, int fin)
{
    if( fin <= inicio)
        return;

    int pivot = partition(vector, inicio, fin);

    ordenarVectorQsort(vector, start, pivot - 1);
    ordenarVectorQsort(vector, pivot + 1, end);

}

void partition(Vector* vector, int inicio, int fin)
{
    int pivot = vector->vec[end];
    int i = start - 1;

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

    int temp = vector->vec[i];
    vector->vec[i] = vector->vec[end];
    vector->vec[end] = temp;

    return i;
}
