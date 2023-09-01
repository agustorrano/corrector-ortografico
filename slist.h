#ifndef __SLIST_H__
#define __SLIST_H__

typedef struct _SNodo {
  char* palabra;
  struct _SNodo *sig;
} SNodo;

typedef SNodo *SList;

/**
 * slist_crear : void -> SList
 * Devuelve una lista vacía
 */
SList slist_crear();

/**
 * slist_vacia : SList -> int
 * Determina si la lista es vacía
 */
int slist_vacia(SList);

/**
 * slist_destruir : SList -> void
 * Destruye la lista
 */
void slist_destruir(SList);

/**
 * slist_agregar_inicio : SList, char* -> SList
 * Agrega un elemento al inicio de la lista
 */
SList slist_agregar_inicio(SList, char*, int);

/**
 * slist_contiene : SList, char* -> int
 * Determina si un elemento se encuantra en la lista
 */
int slist_contiene(SList, char*);

#endif /* __SLIST_H__ */
