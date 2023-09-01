#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include "slist.h"

SList slist_crear() { return NULL; }

int slist_vacia(SList lista) {
  return lista == NULL;
}

void slist_destruir(SList lista) {
  SNodo *nodoAEliminar;
  while (!slist_vacia(lista)) {
    nodoAEliminar = lista;
    lista = lista->sig;
    free(nodoAEliminar->palabra);
    free(nodoAEliminar);
  }
}

SList slist_agregar_inicio(SList lista, char* palabra, int largo) {
  SNodo *nuevoNodo = malloc(sizeof(SNodo));
  assert(nuevoNodo != NULL);
  nuevoNodo->palabra = malloc(sizeof(char) * (largo + 1));
  assert(nuevoNodo->palabra != NULL);
  memcpy(nuevoNodo->palabra, palabra, largo + 1);
  nuevoNodo->sig = lista;
  return nuevoNodo;
}

int slist_contiene(SList lista, char* dato) {
  for (SList nodo = lista; nodo != NULL; nodo = nodo->sig) {
    if (strcmp(dato, nodo->palabra) == 0)
      return 1;
  }
  return 0;
}

