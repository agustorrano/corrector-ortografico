#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "diccionario.h"

char* copia_strings(char* palabra, int largo) {

  char* copia = malloc(sizeof(char) * (largo + 1));
  assert(copia != NULL);
  memcpy(copia, palabra, largo + 1);

  return copia;
}

int compara_strings(char* palabra1, char* palabra2) {
  return strcmp(palabra1, palabra2);
}

void destruir_strings(char* palabra) {
  free(palabra);
}

int largo_strings(char* palabra) {
  return strlen(palabra);
}

unsigned long hash1_strings(char* palabra) {
  return funcion_hash1(palabra);
}

unsigned long hash2_strings(char* palabra) {
  return funcion_hash2(palabra);
}

TablaHash* almacenar_datos(char* nombreArchivo) {

  TablaHash* diccionario = tablahash_crear(CAPACIDAD, (FuncionCopiadora) copia_strings, 
  (FuncionComparadora) compara_strings, (FuncionDestructora) destruir_strings, (FuncionLongitud) largo_strings, 
  (FuncionHash) hash1_strings, (FuncionHash) hash2_strings);

  FILE* archivo = fopen(nombreArchivo, "r");
  assert(archivo != NULL);

  char buf[35];

  for (int i = 0; (buf[i] = fgetc(archivo)) != EOF; i++) {
    if (buf[i] == '\n') {
      buf[i] = '\0';
      if (i) {
        tablahash_insertar(diccionario, buf, i);
      }
      i = -1;
    }
  }

  fclose(archivo);
  return diccionario;
}
