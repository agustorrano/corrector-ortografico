#include <stdio.h>
#include <stdlib.h>
#include "corrector.h"

#define DICCIONARIO "diccionario.txt"

int main(int argc, char* argv[]) {

  if (argc == 3) {
    corrector(DICCIONARIO, argv[1], argv[2]);
    return 0;
    
  } else {
    printf("La cantidad de argumentos no es la correcta.\n");
    return -1;
  }
}
