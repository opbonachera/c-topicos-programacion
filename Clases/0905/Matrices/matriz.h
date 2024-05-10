#ifndef MATRIZ_H_INCLUDED
#define MATRIZ_H_INCLUDED

#define TAM 4

void mostrarMatriz(int orden, int m[][orden]);
int sumarDiagonalPrincipal(int orden, int m[orden][orden]);
int sumarDiagonalSecundaria(int orden, int m[orden][orden]);
int sumarTriangSupDiagSecu(int orden, int m[orden][orden]);

#endif

