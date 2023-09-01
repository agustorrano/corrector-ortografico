#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include "correcciones.h"

Correcciones* crear_correcciones(char* palabra, int largo, SList sugerencias) {
  Correcciones* repetida = malloc(sizeof(Correcciones));
  assert(repetida != NULL);
  repetida->palabra = malloc(sizeof(char) * (largo + 1));
  assert(repetida->palabra != NULL);
  memcpy(repetida->palabra, palabra, largo + 1);
  repetida->sugerencias = sugerencias;
  return repetida;
}

Correcciones* copia_correcciones(Correcciones* cor, int largo) {
  Correcciones* copia = malloc(sizeof(Correcciones));
  assert(copia != NULL);
  copia->palabra = malloc(sizeof(char) * (largo + 1));
  assert(copia->palabra != NULL);
  memcpy(copia->palabra, cor->palabra, largo + 1);
  copia->sugerencias = cor->sugerencias;
  return copia;
}

int compara_correcciones(Correcciones* cor1, Correcciones* cor2) {
  return strcmp(cor1->palabra, cor2->palabra);
}

void destruir_correcciones(Correcciones* cor) {
  free(cor->palabra);
  free(cor);
}

void correcciones_destruir_sugerencias(Correcciones* cor) {
  if(cor->sugerencias != NULL)
    slist_destruir(cor->sugerencias);
}

int largo_correcciones(Correcciones* cor) {
  return strlen(cor->palabra);
}

unsigned long hash1_correcciones(Correcciones* cor) {
  return funcion_hash1(cor->palabra);
}

unsigned long hash2_correcciones(Correcciones* cor) {
  return funcion_hash2(cor->palabra);
}
