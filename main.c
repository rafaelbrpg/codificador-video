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
    // int i, num;
    char * nome_arquivo = "files/VIDEO_ORIGINAL.zip";	// Definição do nome do arquivo original do vídeo
	int qnt_arquivos;                               // Quantidade de arquivos escritos

	qnt_arquivos = codifica(nome_arquivo);		// "Codifica" o arquivo

	// system("pause");				// Pausa para verificar qnt de bytes lidas no último bloco

	nome_arquivo = "files/VIDEO_RECONSTRUIDO.zip";	// Definição do arquivo F_out, recontrução do vídeo
	decodifica(qnt_arquivos, nome_arquivo);		// "Decodifica", reconstrói o vídeo

    // srand(time(NULL));
    //
    // for(i = 0; i < 10; i++) {
    //     num = rand() % 500;
    //     printf("Gerou: %d\n", num);
    //     insereAVL(num, &raiz);
    // }

    printf("Altura da arvore: %d\n", altura_arvore(&raiz));
    puts("Imprimindo conteudo da AVL:");
    dois_imprimeAVL(&raiz);

    return 0;
}
