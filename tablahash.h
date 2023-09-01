#ifndef __TABLAHASH_H__
#define __TABLAHASH_H__

// Copia un dato
typedef void *(*FuncionCopiadora)(void* dato1, int dato2);
// Compara dos datos, retorna 0 si son iguales
typedef int (*FuncionComparadora)(void* dato1, void* dato2);
// Libera la memoria alocada para el dato
typedef void (*FuncionDestructora)(void* dato);
// Funcion hash 
typedef unsigned long (*FuncionHash)(void* dato);
// Retorna la longitud de la palabra que se encuentre dentro del dato
typedef int (*FuncionLongitud) (void* dato);

typedef struct {
  void** casilleros;
  unsigned capacidad;
  unsigned nElementos;
  FuncionHash hash1;
  FuncionHash hash2;
  FuncionCopiadora copy;
  FuncionComparadora comp;
  FuncionDestructora destr;
  FuncionLongitud len;

  unsigned colisiones;
  unsigned peorcaso;
  unsigned rehasheos;
} TablaHash;

/**
 * funcion_hash1 : char* -> unsigned long
 * Algoritmo djb2 http://www.cse.yorku.ca/~oz/hash.html
*/
unsigned long funcion_hash1(char* palabra);

/**
 * funcion_hash2 : char* -> unsigned long
 * Algoritmo sdbm http://www.cse.yorku.ca/~oz/hash.html
*/
unsigned long funcion_hash2(char* palabra);

/**
 * tablahash_crear : unsigned,  FuncionCopiadora, FuncionComparadora, FuncionDestructora, FuncionLongitud, 
 * FuncionHash, FuncionHash -> TablaHash*
 * Crea una nueva tabla hash vacia, con la capacidad dada.
 */
TablaHash* tablahash_crear(unsigned, FuncionCopiadora, FuncionComparadora, FuncionDestructora, FuncionLongitud, 
FuncionHash, FuncionHash);

/**
 * tablahash_destruir : TablaHash* -> void
 * Destruye la tabla hash y sus datos.
 */
void tablahash_destruir(TablaHash*);

/**
 * tablahash_insertar : TablaHash*, void*, int -> void
 * Inserta un dato en la tabla. Si el factor de carga de la tabla sobrepasa un límite establecido,
 * redimensiona la tabla.
 * La implementación maneja colisiones con hashing doble.
 */
void tablahash_insertar(TablaHash*, void*, int);

/**
 * tablahash_buscar : TablaHash*, void* -> int
 * Determina si un dato está en la tabla. Si el dato dado está en la tabla, retorna su posición,
 * en caso contrario, -1.
 */
int tablahash_buscar(TablaHash*, void*);

/**
 * tablahash_redimensionar : TablaHash* -> void
 * Dada una tabla hash, la redimensiona auemntando su capacidad y rehasheando sus datos.
*/
void tablahash_redimensionar(TablaHash*);

#endif /* __TABLAHASH_H__ */