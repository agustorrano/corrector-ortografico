# Makefile para corrector ortográfico
# Escribiendo "make" en la terminal se genera el ejecutable del programa automáticamente
# Escribiendo "make tests" en la terminal se genera el ejecutable de los casos de prueba
# Para ejecutar el programa: ./main archivoEntrada archivoSalida

CC = gcc
CFLAGS = -g -Wall -Wextra -Werror -std=c99
EXE.NAME = main
FILES.O = slist.o tablahash.o diccionario.o correcciones.o corrector.o

all: $(FILES.O)
	$(CC) -o $(EXE.NAME) $(FILES.O) main.c

.PHONY: all clean tests

tests:
	$(CC) -o tests $(FILES.O) tests.c

slist.o: slist.c
	$(CC) $(CFLAGS) -c slist.c

tablahash.o: tablahash.c
	$(CC) $(CFLAGS) -c tablahash.c

diccionario.o: diccionario.c
	$(CC) $(CFLAGS) -c diccionario.c

correcciones.o: correcciones.c
	$(CC) $(CFLAGS) -c correcciones.c

corrector.o: corrector.c
	$(CC) $(CFLAGS) -c corrector.c

clean:
	rm -f main
	rm -f tests
	rm -f *.o