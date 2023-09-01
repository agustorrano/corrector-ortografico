#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "corrector.h"

#define MAX_SUG 5
#define MAX_PASOS 3

int continuar(int cantSugerencias, int cantPasos) {
  return cantSugerencias < MAX_SUG && cantPasos <= MAX_PASOS;
}

void verificar_sugerencia(TablaHash* diccionario, char* palabra, int largo, SList* sugerencias, int* cantSugerencias) {
  if ((tablahash_buscar(diccionario, palabra) != -1) && !slist_contiene(*sugerencias, palabra)) {
    *sugerencias = slist_agregar_inicio(*sugerencias, palabra, largo);
    (*cantSugerencias)++;
  }
}

void intercambiar_caracteres(TablaHash* diccionario, char* palabra, int largo, SList* listaPalabras, SList* sugerencias, 
int* cantSugerencias, int* cantPasos) {

  if (continuar(*cantSugerencias, *cantPasos)) {
    char charAux, *buf;

    for (int i = 0; i < (largo - 1) && continuar(*cantSugerencias, *cantPasos); i++) {
      buf = malloc(sizeof(char) * (largo + 1));
      assert(buf != NULL);
      memcpy(buf, palabra, largo + 1);

      if (buf[i] != buf[i + 1]) {
        charAux = buf[i];
        buf[i] = buf[i + 1];
        buf[i + 1] = charAux;

        *listaPalabras = slist_agregar_inicio(*listaPalabras, buf, largo);
        verificar_sugerencia(diccionario, buf, largo, sugerencias, cantSugerencias);
      }

      free(buf);
    }
  }
}

void insertar_caracteres(TablaHash* diccionario, char* palabra, int largo, SList* listaPalabras, SList* sugerencias, 
int* cantSugerencias, int* cantPasos) {

  if (continuar(*cantSugerencias, *cantPasos)) {
    char abecedario[27] = "abcdefghijklmnopqrstuvwxyz";
    char *buf;

    for (int i = 0; i <= largo && continuar(*cantSugerencias, *cantPasos); i++) {
      for (int j = 0; j < 26 && continuar(*cantSugerencias, *cantPasos); j++) {

        buf = malloc(sizeof(char) * (largo + 2));
        assert(buf != NULL);
        memcpy(buf, palabra, i + 1);
        memcpy(buf + i + 1, palabra + i, largo - i + 1);
        buf[i] = abecedario[j];

        *listaPalabras = slist_agregar_inicio(*listaPalabras, buf, largo + 1);
        verificar_sugerencia(diccionario, buf, largo + 1, sugerencias, cantSugerencias);
        free(buf);
      }
    }
  }
}

void eliminar_caracteres(TablaHash* diccionario, char* palabra, int largo, SList* listaPalabras, SList* sugerencias, 
int* cantSugerencias, int* cantPasos) {

  if (continuar(*cantSugerencias, *cantPasos)) {
    char *buf;

    for (int i = 0; i < largo && continuar(*cantSugerencias, *cantPasos); i++) {

      buf = malloc(sizeof(char) * (largo + 1));
      assert(buf != NULL);
      memcpy(buf, palabra, largo + 1);

      if (buf[i] != buf[i + 1]) {

        for (int j = i; j < largo; j++)
          buf[j] = buf[j + 1];

        *listaPalabras = slist_agregar_inicio(*listaPalabras, buf, largo - 1);
        verificar_sugerencia(diccionario, buf, largo - 1, sugerencias, cantSugerencias);
      }

      free(buf);
    }
  }
}

void reemplazar_caracteres(TablaHash* diccionario, char* palabra, int largo, SList* listaPalabras, SList* sugerencias, 
int* cantSugerencias, int* cantPasos) {

  if (continuar(*cantSugerencias, *cantPasos)) {
    char abecedario[27] = "abcdefghijklmnopqrstuvwxyz";
    char *buf;

    for (int i = 0; i < largo && continuar(*cantSugerencias, *cantPasos); i++) {
      for (int j = 0; j < 26 && continuar(*cantSugerencias, *cantPasos); j++) {

        buf = malloc(sizeof(char) * (largo + 1));
        assert(buf != NULL);
        memcpy(buf, palabra, largo + 1);

        if (buf[i] != abecedario[j]) {
          buf[i] = abecedario[j];
          *listaPalabras = slist_agregar_inicio(*listaPalabras, buf, largo);
          verificar_sugerencia(diccionario, buf, largo, sugerencias, cantSugerencias);
        }

        free(buf);
      }
    }
  }
}

void separar_palabra(TablaHash* diccionario, char* palabra, int largo, SList* sugerencias, int* cantSugerencias, 
int* cantPasos) {

  if (continuar(*cantSugerencias, *cantPasos)) {
    char *buf1, *buf2;

    for (int i = 1; i < largo && continuar(*cantSugerencias, *cantPasos); i++) {

      buf1 = malloc(sizeof(char) * (i + 2));
      assert(buf1 != NULL);
      buf2 = malloc(sizeof(char) * (largo - i + 1));
      assert(buf2 != NULL);
      memcpy(buf1, palabra, i + 1);
      buf1[i] = 0;
      memcpy(buf2, palabra + i, largo - i + 1);

      if ((tablahash_buscar(diccionario, buf1) != -1) && (tablahash_buscar(diccionario, buf2) != -1)) {
        buf1[i] = ' ';
        buf1[i + 1] = 0;

        char* nuevaPalabra = malloc(sizeof(char) * (largo + 2));
        assert(nuevaPalabra != NULL);
        memcpy(nuevaPalabra, buf1, i + 1);
        memcpy(nuevaPalabra + i + 1, buf2, largo - i + 1);

        if (!slist_contiene(*sugerencias, nuevaPalabra)) {
          *sugerencias = slist_agregar_inicio(*sugerencias, nuevaPalabra, largo + 1);
          (*cantSugerencias)++;
        }

        free(nuevaPalabra);
      }

      free(buf1);
      free(buf2);
    }
  }
}

void salida(Correcciones* correcciones, unsigned int linea, FILE* archivoSalida) {
  SList sugerencias = correcciones->sugerencias;

  if (!slist_vacia(sugerencias)) {
    SList nodo = sugerencias;
    fprintf(archivoSalida, "Linea %d, \"%s\" no esta en el diccionario.\n", linea, correcciones->palabra);
    fprintf(archivoSalida, "Quizas quiso decir: ");

    for (; nodo->sig != NULL; nodo = nodo->sig) {
      fprintf(archivoSalida, "%s, ", nodo->palabra);
    }

    fprintf(archivoSalida, "%s\n\n", nodo->palabra);

  } else {
    fprintf(archivoSalida, "Linea %d, \"%s\" no esta en el diccionario.\n", linea, correcciones->palabra);
    fprintf(archivoSalida, "No se encuentran sugerencias para esta palabra.\n\n");
  }
}

void corregir_palabra(TablaHash* diccionario, TablaHash* repetidas, char* palabra, unsigned int linea, 
int largo, FILE* archivoSalida) {

  SList listaPalabras = slist_crear();
  SList sugerencias = slist_crear();
  SList listaAux = slist_crear();
  listaAux = slist_agregar_inicio(listaAux, palabra, largo);

  TablaHash* palabrasModificadas = tablahash_crear(CAPACIDAD, (FuncionCopiadora) copia_strings, 
  (FuncionComparadora) compara_strings, (FuncionDestructora) destruir_strings, (FuncionLongitud) largo_strings, 
  (FuncionHash) hash1_strings, (FuncionHash) hash2_strings);

  int cantSugererncias = 0, cantPasos = 1, largoNodo;

  while (continuar(cantSugererncias, cantPasos)) {
    for (SList nodo = listaAux; nodo != NULL; nodo = nodo->sig) {

      if (tablahash_buscar(palabrasModificadas, nodo->palabra) == -1) {
        largoNodo = strlen(nodo->palabra);
        tablahash_insertar(palabrasModificadas, nodo->palabra, largoNodo);
        eliminar_caracteres(diccionario, nodo->palabra, largoNodo, &listaPalabras, &sugerencias, &cantSugererncias, &cantPasos);
        reemplazar_caracteres(diccionario, nodo->palabra, largoNodo, &listaPalabras, &sugerencias, &cantSugererncias, &cantPasos);
        intercambiar_caracteres(diccionario, nodo->palabra, largoNodo, &listaPalabras, &sugerencias, &cantSugererncias, &cantPasos);
        insertar_caracteres(diccionario, nodo->palabra, largoNodo, &listaPalabras, &sugerencias, &cantSugererncias, &cantPasos);
        separar_palabra(diccionario, nodo->palabra, largoNodo, &sugerencias, &cantSugererncias, &cantPasos);
      }
    }

    cantPasos++;
    slist_destruir(listaAux);
    listaAux = listaPalabras;
    listaPalabras = slist_crear();
  }

  slist_destruir(listaAux);
  tablahash_destruir(palabrasModificadas);
  Correcciones* correciones = crear_correcciones(palabra, largo, sugerencias);
  tablahash_insertar(repetidas, correciones, largo);
  salida(correciones, linea, archivoSalida);
  destruir_correcciones(correciones);
}

void corrector(char* nombreDiccionario, char* nombreArchivoEntrada, char* nombreArchivoSalida) {
  TablaHash* diccionario = almacenar_datos(nombreDiccionario);
  TablaHash* repetidas = tablahash_crear(CAPACIDAD, (FuncionCopiadora) copia_correcciones, (FuncionComparadora) compara_correcciones,
  (FuncionDestructora) destruir_correcciones, (FuncionLongitud) largo_correcciones, (FuncionHash) hash1_correcciones,
  (FuncionHash) hash2_correcciones);

  FILE* archivoEntrada = fopen(nombreArchivoEntrada, "r");
  assert(archivoEntrada != NULL);
  FILE* archivoSalida = fopen(nombreArchivoSalida, "w");
  assert(archivoSalida != NULL);

  char charBuf, buf[50];
  int i = 0, linea = 1;
  SList sugerencias = slist_crear();
  Correcciones* palabraRep;

  while(!feof(archivoEntrada)) {
    charBuf = tolower(fgetc(archivoEntrada));

    if (isalpha(charBuf)) {
      buf[i] = charBuf;
      i++;

    } else {
      buf[i] = '\0';

      if (strlen(buf) != 0) {
        
        if (tablahash_buscar(diccionario, buf) == -1) {
          palabraRep = crear_correcciones(buf, i, sugerencias);
          int idx = tablahash_buscar(repetidas, palabraRep);

          if (idx == -1)
            corregir_palabra(diccionario, repetidas, buf, linea, i, archivoSalida);
          else
            salida(repetidas->casilleros[idx], linea, archivoSalida);

          slist_destruir(palabraRep->sugerencias);
          destruir_correcciones(palabraRep);
        }
      }
      i = 0;

      if (charBuf == '\n')
        linea++;
    }
  }

  fclose(archivoEntrada);
  fclose(archivoSalida);

  for (unsigned i = 0; i < repetidas->capacidad; i++) {
    if (repetidas->casilleros[i])
      correcciones_destruir_sugerencias(repetidas->casilleros[i]);
  }

  tablahash_destruir(repetidas);
  tablahash_destruir(diccionario);
}
