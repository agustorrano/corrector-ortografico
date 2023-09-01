#ifndef __DICCIONARIO_H__
#define __DICCIONARIO_H__

#include "tablahash.h"

#define CAPACIDAD 1000

/**
 * copia_strings : char*, int -> char*
 * Copia un string.
*/
char* copia_strings(char*, int);

/**
 * compara_strings : char*, char* -> int
 * Compara dos strings. Retorna 0 si son iguales.
*/
int compara_strings(char*, char*);

/**
 * destruir_strings : char* -> void
 * Destruye un string.
*/
void destruir_strings(char*);

/**
 * largo_strings: char* -> int
 * Retorna el largo del string.
*/
int largo_strings(char*);

/**
 * hash1_strings : char* -> unsigned long
 * Funcion hash djb2 para strings. 
*/
unsigned long hash1_strings(char* palabra);

/**
 * hash2_strings : char* -> unsigned long
 * Funcion hash sdbm para strings.
*/
unsigned long hash2_strings(char* palabra);

/**
 * almacenar_datos : char* -> TablaHash*
 * Dado un archivo con palabras (diccionario), almacena cada palabra en una tabla hash y
 * la retorna.
 */
TablaHash* almacenar_datos(char*);

#endif /* __DICCIONARIO_H__ */