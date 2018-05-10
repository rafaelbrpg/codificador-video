/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   main.c
 * Author: Aleffer Rocha and Rafael Siqueira
 *
 * Created on 8 de Maio de 2018, 16:19
 */

#include "lib.h"

/* Biblioteca utilizada apenas para testes */
#include <time.h>

int main(void) {
    No *raiz = NULL;
    int i, num;

    srand(time(NULL));

    for(i = 0; i < 10; i++) {
        num = rand() % 50;
        insereAVL(num, &raiz);
        printf("Gerou: %d\n", num);
    }

    puts("Imprimindo conteudo da AVL:");

    imprimeAVL(&raiz);

    return 0;
}
