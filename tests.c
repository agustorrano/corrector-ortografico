#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "slist.h"
#include "tablahash.h"
#include "diccionario.h"
#include "correcciones.h"
#include "corrector.h"

void test_continuar() {
  assert(continuar(1, 1) == 1);
  assert(continuar(5, 2) == 0);
  assert(continuar(2, 4) == 0);
  assert(continuar(5, 4) == 0);
}

void test_verificar_sugerencia() {
  TablaHash* diccionario = tablahash_crear(10, (FuncionCopiadora) copia_strings, (FuncionComparadora) compara_strings, 
  (FuncionDestructora) destruir_strings, (FuncionLongitud) largo_strings, (FuncionHash) funcion_hash1, 
  (FuncionHash) funcion_hash2);
  SList sugerencias = slist_crear();
  int cantSugerencias = 0;
  tablahash_insertar(diccionario, "hola", 4);
  tablahash_insertar(diccionario, "arbol", 5);
  verificar_sugerencia(diccionario, "hola", 4, &sugerencias, &cantSugerencias);
  verificar_sugerencia(diccionario, "ola", 3, &sugerencias, &cantSugerencias);
  verificar_sugerencia(diccionario, "arbol", 5, &sugerencias, &cantSugerencias);
  verificar_sugerencia(diccionario, "barco", 5, &sugerencias, &cantSugerencias);
  assert(cantSugerencias == 2);
  assert(slist_contiene(sugerencias, "hola"));
  assert(slist_contiene(sugerencias, "arbol"));
  assert(!slist_contiene(sugerencias, "ola"));
  assert(!slist_contiene(sugerencias, "barco"));
  slist_destruir(sugerencias);
  tablahash_destruir(diccionario);
}

void test_intercambiar_caracteres() {
  TablaHash* diccionario = tablahash_crear(10, (FuncionCopiadora) copia_strings, (FuncionComparadora) compara_strings, 
  (FuncionDestructora) destruir_strings, (FuncionLongitud) largo_strings, (FuncionHash) funcion_hash1, 
  (FuncionHash) funcion_hash2);
  SList listaPalabras = slist_crear();
  SList sugerencias = slist_crear();
  int cantSugerencias = 0, cantPasos = 0;
  intercambiar_caracteres(diccionario, "hola", 4, &listaPalabras, &sugerencias, &cantSugerencias, &cantPasos);
  assert(slist_contiene(listaPalabras, "ohla"));
  assert(slist_contiene(listaPalabras, "hloa"));
  assert(slist_contiene(listaPalabras, "hoal"));
  slist_destruir(sugerencias);
  slist_destruir(listaPalabras);
  tablahash_destruir(diccionario);
}

void test_insertar_caracteres() {
  TablaHash* diccionario = tablahash_crear(10, (FuncionCopiadora) copia_strings, (FuncionComparadora) compara_strings, 
  (FuncionDestructora) destruir_strings, (FuncionLongitud) largo_strings, (FuncionHash) funcion_hash1, 
  (FuncionHash) funcion_hash2);
  SList listaPalabras = slist_crear();
  SList sugerencias = slist_crear();
  int cantSugerencias = 0, cantPasos = 0;
  insertar_caracteres(diccionario, "hola", 4, &listaPalabras, &sugerencias, &cantSugerencias, &cantPasos);
  assert(slist_contiene(listaPalabras, "ahola"));
  assert(slist_contiene(listaPalabras, "hlola"));
  assert(slist_contiene(listaPalabras, "hoola"));
  assert(slist_contiene(listaPalabras, "holaz"));
  slist_destruir(sugerencias);
  slist_destruir(listaPalabras);
  tablahash_destruir(diccionario);
}

void test_eliminar_caracteres() {
  TablaHash* diccionario = tablahash_crear(10, (FuncionCopiadora) copia_strings, (FuncionComparadora) compara_strings, 
  (FuncionDestructora) destruir_strings, (FuncionLongitud) largo_strings, (FuncionHash) funcion_hash1, 
  (FuncionHash) funcion_hash2);
  SList listaPalabras = slist_crear();
  SList sugerencias = slist_crear();
  int cantSugerencias = 0, cantPasos = 0;
  eliminar_caracteres(diccionario, "hola", 4, &listaPalabras, &sugerencias, &cantSugerencias, &cantPasos);
  assert(slist_contiene(listaPalabras, "ola"));
  assert(slist_contiene(listaPalabras, "hla"));
  assert(slist_contiene(listaPalabras, "hoa"));
  assert(slist_contiene(listaPalabras, "hol"));
  slist_destruir(sugerencias);
  slist_destruir(listaPalabras);
  tablahash_destruir(diccionario);
}

void test_reemplazar_caracteres() {
  TablaHash* diccionario = tablahash_crear(10, (FuncionCopiadora) copia_strings, (FuncionComparadora) compara_strings, 
  (FuncionDestructora) destruir_strings, (FuncionLongitud) largo_strings, (FuncionHash) funcion_hash1, 
  (FuncionHash) funcion_hash2);
  SList listaPalabras = slist_crear();
  SList sugerencias = slist_crear();
  int cantSugerencias = 0, cantPasos = 0;
  reemplazar_caracteres(diccionario, "hola", 4, &listaPalabras, &sugerencias, &cantSugerencias, &cantPasos);
  assert(slist_contiene(listaPalabras, "aola"));
  assert(slist_contiene(listaPalabras, "hlla"));
  assert(slist_contiene(listaPalabras, "hoqa"));
  assert(slist_contiene(listaPalabras, "holz"));
  slist_destruir(sugerencias);
  slist_destruir(listaPalabras);
  tablahash_destruir(diccionario);
}

void test_separar_palabra() {
  TablaHash* diccionario = tablahash_crear(10, (FuncionCopiadora) copia_strings, (FuncionComparadora) compara_strings, 
  (FuncionDestructora) destruir_strings, (FuncionLongitud) largo_strings, (FuncionHash) funcion_hash1, 
  (FuncionHash) funcion_hash2);
  SList sugerencias = slist_crear();
  int cantSugerencias = 0, cantPasos = 0;
  tablahash_insertar(diccionario, "ho", 2);
  tablahash_insertar(diccionario, "la", 2);
  tablahash_insertar(diccionario, "h", 1);
  tablahash_insertar(diccionario, "ola", 3);
  separar_palabra(diccionario, "hola", 4, &sugerencias, &cantSugerencias, &cantPasos);
  assert(slist_contiene(sugerencias, "ho la"));
  assert(slist_contiene(sugerencias, "h ola"));
  slist_destruir(sugerencias);
  tablahash_destruir(diccionario);
}

int main() {
  test_continuar();
  test_verificar_sugerencia();
  test_intercambiar_caracteres();
  test_insertar_caracteres();
  test_eliminar_caracteres();
  test_reemplazar_caracteres();
  test_separar_palabra();
  return 0;
}
