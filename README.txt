File:   README.txt
Author: Aleffer Rocha and Rafael Siqueira

Created on 8 de Maio de 2018, 16:19

Compilador utilizado:
    https://gcc.gnu.org

Para compilar a biblioteca:
    $ gcc -c lib.c lib.h

Para compilar o arquivo main e gerar um executavel:
    $ gcc main.c lib.c -Wall
    ou
    $ gcc main.c lib.o -Wall
