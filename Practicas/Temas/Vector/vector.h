#ifndef VECTOR_H_INCLUDED
#define VECTOR_H_INCLUDED

#define CAP_VECTOR 10

#define OK 0
#define ERROR_RESERVA_MEMORIA 1
#define ELEMENTO_DUPLICADO 2
#define POSICION_INEXISTENTE 3

#define FACTOR_INCREMENTO 5
#define FACTOR_DECREMENTO 10

typedef struct{
    size_t cap;
    size_t tamElem;
    size_t ce;
    void* v;
}Vector;

typedef void(Imprimir*)(void* elemento);
typedef int(Comparar*)(void* elemento1, void* elemento2);

int inicializarVector(Vector* vector, size_t tamElem, size_t ce);
int vaciarVector(Vector* vector);
int destruirVector(Vector* vector);
int cargarVectorOrdenadoEnteros(Vector* vector);
int cargarVectorRandom(Vector* vector);
int redimensionarVector(Vector* vector, size_t nuevaCap);
int mostrarVector(Vector* vector, Imprimir impElemento);

int insertarElementoAlFinal(Vector* vector, void* elemento);
int insertarElementoOrdenado(Vector* vector, Comparar cmp, void* elemento);
int insertarElementoEnPosicion(Vector* vector, Comparar cmp, void* elemento, int posIns);
void eliminarElementoEnPosicion(Vector* vector, void* elemento, size_t posicion);
void eliminarElementoOrdenado(Vector* vector, void* elemento);
void eliminarElementoPrimeraAparicion(Vector* vector, void* elemento);
void eliminarElementoTodasApariciones(Vector* vector, void* elemento);

void ordenarVectorBurbujeo(Vector* vector, Comparar cmp);
void ordenarVectorInsercion(Vector* vector, Comparar cmp);
void ordenarVectorSeleccion(Vector* vector, Comparar cmp);
void buscarVectorBinariaRec(Vector* vector, Comparar cmp);

#endif