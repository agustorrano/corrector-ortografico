#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include "tablahash.h"

#define FACTOR_DE_CARGA 0.7
#define PEOR_CASO 28

unsigned long funcion_hash1(char* palabra) {
  unsigned long hash = 5381;
  int c;
  while ((c = *palabra++) != 0) 
    hash = ((hash << 5) + hash) + c; // hash * 33 + c
  return hash;
}

unsigned long funcion_hash2(char* palabra) {
  unsigned long hash = 0; int c;
  while ((c = (int)*palabra++) != 0) 
    hash = c + (hash << 6) + (hash << 16) - hash;
  return ++hash;
}

TablaHash* tablahash_crear(unsigned capacidad, FuncionCopiadora copy, FuncionComparadora comp, 
FuncionDestructora destr, FuncionLongitud len, FuncionHash hash1, FuncionHash hash2) {
  TablaHash* tabla = malloc(sizeof(TablaHash));
  tabla->casilleros = malloc(sizeof(void*) * capacidad);
  tabla->capacidad = capacidad;
  tabla->hash1 = hash1;
  tabla->hash2 = hash2;
  tabla->copy = copy;
  tabla->comp = comp;
  tabla->destr = destr;
  tabla->len = len;
  tabla->nElementos = tabla->colisiones = tabla->peorcaso = tabla->rehasheos = 0;
  for (unsigned i = 0; i < capacidad; ++i) {
    tabla->casilleros[i] = NULL;
  }
  return tabla;
}

void tablahash_destruir(TablaHash* tabla) {
  for (unsigned i = 0; i < tabla->capacidad; i++) {
    if (tabla->casilleros[i])
      tabla->destr(tabla->casilleros[i]);
  }
  free(tabla->casilleros);
  free(tabla);
}

void tablahash_insertar(TablaHash* tabla, void* dato, int largo) {
  unsigned idx = tabla->hash1(dato) % tabla->capacidad;
  unsigned int sondeos;
  if (tabla->casilleros[idx]) tabla->colisiones++;
  for (sondeos = 0; tabla->casilleros[idx] && sondeos < PEOR_CASO; sondeos++)
    idx = (idx + tabla->hash2(dato)) % tabla->capacidad;
  if (sondeos > tabla->peorcaso && sondeos < PEOR_CASO) tabla->peorcaso = sondeos;
  if ((float) tabla->nElementos / (float) tabla->capacidad < FACTOR_DE_CARGA && sondeos < PEOR_CASO) {
    tabla->casilleros[idx] = tabla->copy(dato, largo);
    tabla->nElementos++;
    } else {
      tablahash_redimensionar(tabla);
      tablahash_insertar(tabla, dato, largo);
    }
}

int tablahash_buscar(TablaHash* tabla, void* dato) {
  unsigned idx = tabla->hash1(dato) % tabla->capacidad;
  for (int i = 0; i < 28 && tabla->casilleros[idx]; i++) {
    if (tabla->comp(dato, tabla->casilleros[idx]) == 0) 
      return idx;
    idx = (idx + tabla->hash2(dato)) % tabla->capacidad;
  }
  return -1;
}

void tablahash_redimensionar(TablaHash* tabla) {
  void** casillerosNuevos = malloc(sizeof(void*) * tabla->capacidad * 2);
  for (unsigned i = 0; i < tabla->capacidad * 2; i++) 
    casillerosNuevos[i] = NULL;
  void** casillerosViejos = tabla->casilleros;
  unsigned capacidadVieja = tabla->capacidad;
  tabla->casilleros = casillerosNuevos;
  tabla->capacidad = tabla->capacidad * 2;
  tabla->nElementos = tabla->colisiones = tabla->peorcaso = 0;
  tabla->rehasheos++;
  for (unsigned i = 0; i < capacidadVieja; i++)
    if (casillerosViejos[i]) {
      int largo = tabla->len(casillerosViejos[i]);
      tablahash_insertar(tabla, casillerosViejos[i], largo);
      tabla->destr(casillerosViejos[i]);
    }
  free(casillerosViejos);
}
