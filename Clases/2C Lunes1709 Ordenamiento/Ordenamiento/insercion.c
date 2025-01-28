
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
