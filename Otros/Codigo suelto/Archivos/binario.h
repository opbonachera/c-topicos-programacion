#ifndef ARCHIVOS_H_INCLUDED
#define ARCHIVOS_H_INCLUDED

#define ARCH_BIN "origen.bin"
#define ARCH_TXT "destino.txt"

#define TODO_OK 0
#define ERROR 1

typedef struct
{
    int legajo;
    char nombre[20];
    char apellido[20];
    float sueldo;
}t_persona;

int crearArchivoBinarioEjemplo(const char *ruta);

#endif // ARCHIVOS_H_INCLUDED
