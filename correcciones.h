#ifndef __CORRECCIONES_H__
#define __CORRECCIONES_H__

#include "slist.h"
#include "tablahash.h"

typedef struct _Correciones {
  char* palabra;
  SList sugerencias;
} Correcciones;

/**
 * crear_correcciones : char*, int, SList -> Correcciones*
 * Crea un tipo de dato Correcciones.
*/
Correcciones* crear_correcciones(char*, int, SList);

/**
 * copia_correcciones : Correcciones*, int -> Correcciones*
 * Hace una copia de un dato Correcciones.
*/
Correcciones* copia_correcciones(Correcciones*, int);

/**
 * compara_correcciones : Correcciones*, Correcciones* -> int
 * Compara dos datos Correcciones. Retorna 0 sin son iguales. 
*/
int compara_correcciones(Correcciones*, Correcciones*);

/**
 * destruir_correcciones : Correcciones* -> void
 * Destruye el tipo de dato Correcciones sin considerar la lista de sugerencias.
*/
void destruir_correcciones(Correcciones*);

/**
 * correcciones_destruir_sugerencias : Correcciones* -> void
 * Destruye la lista de sugerencias.
*/
void correcciones_destruir_sugerencias(Correcciones*);

/**
 * largo_correcciones : Correcciones* -> int
 * Retorna el largo de la palabra almacenada en la estructura.
*/
int largo_correcciones(Correcciones* );

/**
 * hash1_correcciones : Correcciones* -> unsigned long
 * Funcion hash djb2 para la estructura.
*/
unsigned long hash1_correcciones(Correcciones*);

/**
 * hash2_correcciones : Correcciones* -> unsigned long
 * Funcion hash sdbm para la estructura.
*/
unsigned long hash2_correcciones(Correcciones*);

#endif /* __CORRECCIONES_H__ */