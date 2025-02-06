#ifndef VECTORES_H_INCLUDED
#define VECTORES_H_INCLUDED



int initVec(int* vec, int ce);
int insertarEnPosVec(int* vec, int pos, int el);
int imprimirVec(int*, int ce);
int insertarAlFinal(int* vec, int ce, int el);
int eliminarPrimeraAparicion(int *vec, int el, int ce);
int eliminarTodasLasApariciones(int* vec, int el, int ce);
int esPalindromo(const char* s1, const char* s2);
int printCadena(char* s);

#endif // VECTORES_H_INCLUDED
