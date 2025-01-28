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
