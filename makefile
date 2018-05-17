codificador: printy

printy: main.o lib.o
gcc -o printy main.o lib.o

main.o: main.c lib.h
	gcc -o main.o main.c -c -W -Wall -ansi -pedantic

lib.o: helloWorld.c helloWorld.h
	gcc -o lib.o lib.c -c -W -Wall -ansi -pedantic

clean:
	rm -rf *.o *~ printy
