#ifndef __CORRECTOR_H__
#define __CORRECTOR_H__

#include "correcciones.h"
#include "diccionario.h"

/**
 * continuar : int, int -> int
 * Determina si se puede continuar modificando una palabra dependiendo de la cantidad
 * de sugerencias y de la cantidad de pasos relizados. Si la cantidad de sugerencias
 * es mayor o igual a 5 y si la cantidad de pasos es mayor a 3, no se puede continuar.
 */
int continuar(int, int);

/**
 * verificar_sugerencia : TablaHash*, char*, int, SList*, int* -> void
 * Toma la tabla hash con las palabras del diccionario, una palabra, su longitud, un puntero 
 * a una lista de sugerencias y un puntero a la cantidad de sugerencias.
 * Determina si la palabra esta en el diccionario y si todavía no esta en la lista de 
 * sugerencias. Si es así, la agrega a la lista de sugerencias y aumenta la cantidad de 
 * sugerencias, en caso contrario, no hace nada.
 */
void verificar_sugerencia(TablaHash*, char*, int, SList*, int*);

/**
 * intercambiar_caracteres : TablaHash*, char*, int, SList*, SList*, int*, int* -> void
 * Toma la tabla hash con las palabras del diccionario, una palabra, su longitud, un puntero a 
 * una lista de palabras (que será donde se van a ir almacenando los cambios realizados a la palabra), 
 * un puntero a una lista de sugerencias, un puntero a la cantidad de sugerencias y un puntero a la 
 * cantidad de pasos relizados.
 * Esta función intercambia cada par de caracteres adyacentes de la palabra original, agrega la 
 * palabra resultante en la lista de palabras y verifica si dicha palabra está en el diccionario.
 */
void intercambiar_caracteres(TablaHash*, char*, int, SList*, SList*, int*, int*);

/**
 * insertar_carcteres : TablaHash*, char*, int, SList*, SList*, int*, int* -> void
 * La función inserta cada letra del abcedario en cada posición de la palabra original, agrerga 
 * la palabra resultante en la lista de palabras y verifica si dicha palabra está en el diccionario.
 */
void insertar_caracteres(TablaHash*, char*, int, SList*, SList*, int*, int*);

/**
 * eliminar_carcteres : TablaHash*, char*, int, SList*, SList*, int*, int* -> void
 * Elimina cada caracter de la palabra, agrega la palabra resultante en la lista de
 * palabras y verifica si dicha palabra está en el diccionario.
 */
void eliminar_caracteres(TablaHash*, char*, int, SList*, SList*, int*, int*);

/**
 * reemplazar_caracteres : TablaHash*, char*, int, SList*, SList*, int*, int* -> void
 * Reemplaza cada carcter de la palabra con cada letra del abcedario, agrega la palabra 
 * resultante en la lista de palabras y verifica si dicha palabra está en el diccionario.
 */
void reemplazar_caracteres(TablaHash*, char*, int, SList*, SList*, int*, int*);

/**
 * separar_palabra : TablaHash*, char*, int, SList*, int*, int* -> void
 * Toma la tabla hash con las palabras del diccionario, una palabra, su longitud, un puntero a 
 * una lista de sugerencias, un puntero a la cantidad de sugerencias y un puntero a la cantidad 
 * de pasos relizados.
 * Esta función separa la palabra en un par de palabras agregando un espacio entre cada par de 
 * caracteres adyacentes en la palabra. Si ambas palabras están en el diccionario, agrega la palabra
 * resultante a la lista de sugerencias y aumenta su cantidad.
 */
void separar_palabra(TablaHash*, char*, int, SList*, int*, int*);

/**
 * salida : Correcciones*, unsigned int, FILE* -> void
 * Dadas las sugerencias de una palabra, la línea en la que se encuentra y el archivo de salida,
 * genera el archivo de salida cuyo formato (si la palabra no se encuentra en el diccionario) será de la 
 * siguiente forma:
 *    Linea N, "PALABRA" no esta en el diccionario.
 *    Quizas quiso decir: SUGERENCIA1, SUGERENCIA2, ..., SUGERENCIAn
 * Si no se encontraron sugerencias:
 *    Linea N, "PALABRA" no esta en el diccionario.
 *    No se encuentran sugerencias para esta palabra.
 */
void salida(Correcciones*, unsigned int, FILE*);

/**
 * corregir_palabra : TablaHash*, TablaHash*, char*, unsigned int, int, FILE* -> void
 * Toma la tabla hash con las palabras del diccionario, una tabla hash con las palabras que ya se calcularon,
 * una palabra, la linea en la que se encuentra, la longitud de la palabra y el archivo de salida.
 * Esta función aplica las 5 reglas hasta obtener 5 sugerencias o relizar más de 3 pasos. Finalmente,
 * genera el archivo de salida.
 */
void corregir_palabra(TablaHash*, TablaHash*, char*, unsigned int, int, FILE*);

/**
 * corrector : char*, char*, char* -> void
 * Toma el nombre del archivo del diccionario, el nombre del archivo de entrada y el nombre del archivo
 * de salida y genera este último dando sugerencias de las palabras incorrectas.
 */
void corrector(char*, char*, char*);

#endif /* __CORRECTOR_H__ */