/*
    Crear estructuras:
    - Libro
    - Movimientos
    - Lista

    Entradas:
    Archivo de movimientos (TEXTO - LARGO VARIABLE)
    Archivo de libros (BINARIO)

    --- LEER ---
    Leer archivo de texto
    Pasar archivo de texto de largo variable a binario
    Leer archivo binario
    Leer archivo de movimientos

    Teniendo ambos archivos en formato binario, ordenar.

    --- ORDENAR ---
    | MOVIMIENTOS |
    Bajar el archivo de movimientos a un vector
    Ordenar el vector
    Escribir el vector en un archivo

    | LIBROS |
    Bajar el archivo de libros a un vector (Sin duplicados)
    Insertar elementos en un vector ordenado
    Ordenar el vector
    Escribir nuevamente en el archivo

    --- FUSIONAR ---
    Desarrollar funcion de comparacion de codigo de libros
    Leer registro de movimientos
    Leer registro de libros

     // comparacion = comparar(codigoMovimiento, codigoRegistro)
     // comparacion = 0 El movimiento corresponde al libro. Restar la cantidad en el registro.
     // comparacion > 0 El movimiento corresponde al libro siguiente. Si la cantidad es mayor que 0, escribir Leer un nuevo registro en el archivo de libros.
     // comparacion < 0 El movimiento no está en los libros.
*/
