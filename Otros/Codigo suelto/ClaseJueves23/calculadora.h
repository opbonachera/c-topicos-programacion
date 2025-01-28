#ifndef CALCULADORA_H_INCLUDED
#define CALCULADORA_H_INCLUDED
#define FACTOR_INCREMENTO 2

int calcular(int a, int b, int(*oper)(int,int)); // A la funcion calcular le pasamos como parametro los dos numeros y

// vector dinamico

typedef struct
{
    void    *vec;
    size_t  ce;      // Cantidad maxima de elementos
    size_t  cap;     // Capacidad actual
    size_t  tamElem; // Tamaño del elemento
}tVector;

int  vectorCrear(tVector* vec, size_t tamElem);
void destruirVector(tVector* vec);
int  vectorInsertarAlfinal(tVector *vec, const void *elem);
int _ampliarVector(tVector* vec);
typedef int (*cmpElemento)(const void*, const void*);
void vectorOrdenarSeleccion(tVector *vec, cmpElemento cmp);

#endif // CALCULADORA_H_INCLUDED
