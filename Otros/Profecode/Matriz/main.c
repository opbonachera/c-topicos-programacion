#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define ORDEN 4

#define SIN_MEM 1

void** crearMatriz(size_t filas, size_t columnas, size_t tamElem);
void eliminarMatriz(void** matriz, size_t filas);
void cargarMatriz(int** matriz, size_t filas, size_t columnas);
void mostrarMatriz(int** mat, size_t filas, size_t columnas);
int sumaDiagonalPrincipal(int** mat, size_t orden);
int sumaDiagonalSecundaria(int mat[][ORDEN]);
int sumaTriangularInferiorDP(int mat[][ORDEN]);
int sumaTriangularSuperiorDS(int mat[][ORDEN]);
int** productoMatrices(int** mat1, int** mat2, size_t filasM1, size_t colM1FilM2, size_t columnasM2);


int main()
{
    // int** matriz = (int**)crearMatriz(ORDEN, ORDEN, sizeof(int));

	// if(!matriz)
	// {
	// 	return SIN_MEM;
	// }

    // cargarMatriz(matriz, ORDEN, ORDEN);

    // mostrarMatriz(matriz, ORDEN, ORDEN);

    // int sumaDP = sumaDiagonalPrincipal(matriz, ORDEN);

    // printf("Suma DP: %d\n", sumaDP);

	// eliminarMatriz((void**)matriz, ORDEN);

	int** mat1 = (int**)crearMatriz(2, 4, sizeof(int));
	int** mat2 = (int**)crearMatriz(4, 3, sizeof(int));

	cargarMatriz(mat1, 2, 4);
	cargarMatriz(mat2, 4, 3);

	int** mp = productoMatrices(mat1, mat2, 2, 4, 3);

	mostrarMatriz(mp, 2, 3);

	eliminarMatriz((void**)mat1, 2);
	eliminarMatriz((void**)mat2, 4);
	eliminarMatriz((void**)mp, 2);

    return 0;
}


void** crearMatriz(size_t filas, size_t columnas, size_t tamElem)
{
	void** matriz = malloc(filas * sizeof(void*));

	if(!matriz)
	{
		return NULL;
	}

	void** ult = matriz + filas - 1;

	for(void** i = matriz; i <= ult; i++)
	{
		*i = malloc(columnas * tamElem);

		if(!*i)
		{
			eliminarMatriz(matriz, i - matriz);
			return NULL;
		}
	}
	
	return matriz;
}


void eliminarMatriz(void** matriz, size_t filas)
{
	void** ult = matriz + filas - 1;

	for(void** i = matriz; i <= ult; i++)
	{
		free(*i);
	}

	free(matriz);
}


void cargarMatriz(int** mat, size_t filas, size_t columnas)
{
    int elem = 1;

    for(int i = 0; i < filas; i++)
    {
        for(int j = 0; j < columnas; j++)
        {
            mat[i][j] = elem++;
        }
    }
}


void mostrarMatriz(int** mat, size_t filas, size_t columnas)
{
    for(int i = 0; i < filas; i++)
    {
        for(int j = 0; j < columnas; j++)
        {
            printf("%3d ", mat[i][j]);
        }

        putchar('\n');
    }
}


int sumaDiagonalPrincipal(int** mat, size_t orden)
{
    int acum = 0;
    
    for(int i = 0; i < orden; i++)
    {
        acum += mat[i][i];
    }

    return acum;
}


int sumaDiagonalSecundaria(int mat[][ORDEN])
{
    int acum = 0;
    
    for(int i = 0, j = ORDEN - 1; i < ORDEN; i++, j--)
    {
        acum += mat[i][j];
    }

    return acum;
}


int sumaTriangularInferiorDP(int mat[][ORDEN])
{
    int acum = 0;

    for(int i = 1; i < ORDEN; i++)
    {
        for(int j = 0; j < i; j++)
        {
        	acum += mat[i][j];
        }
    }

	return acum;
}


int sumaTriangularSuperiorDS(int mat[][ORDEN])
{
    int acum = 0;

    for(int i = 0, limJ = ORDEN - 2; i <= ORDEN - 2; i++, limJ--)
    {
        for(int j = 0; j <= limJ; j++)
        {
        	acum += mat[i][j];
        }
    }

	return acum;
}


int** productoMatrices(int** mat1, int** mat2, size_t filasM1, size_t colM1FilM2, size_t columnasM2)
{
	int** mp = (int**)crearMatriz(filasM1, columnasM2, sizeof(int));

	if(!mp)
	{
		return NULL;
	}

	for(int i = 0; i < filasM1; i++)
	{
		for(int j = 0; j < columnasM2; j++)
		{
			mp[i][j] = 0;

			for(int k = 0; k < colM1FilM2; k++)
			{
				mp[i][j] += mat1[i][k] * mat2[k][j];
			}
		}
	}

	return mp;
}
