/*
 * File:   lib.c
 * Author: Aleffer Rocha and Rafael Siqueira
 *
 * Created on 8 de Maio de 2018, 16:19
 */

#include "lib.h"

int codifica(char * nome_arquivo) {
	FILE *F_in, *F_out;							// ponteiros - arquivo - F_in (leitura) - F_out (Escrita)
	F_in = fopen (nome_arquivo,"rb");			// Arquivo - dados originais
	TipoItem it;								// aux da estrutura
	int ord = 1;								// contador/ordem dos bytes lidos
	char nome_arq[20];							// nome do arquivo a ser gravado

	while (!feof(F_in)) {
		it.n_bytes = fread(it.dados, 1,TAM,F_in);			// leitura dos bytes do arquivo F_IN / Salva na estrututa qnt_bytes lidos
		it.ordem = ord; 						// Posicao (indice/ordem) dos dados lidos no arquivo original
		sprintf(nome_arq, "files/%06d.dat", ord); 				// escreve o nome do arquivo (Sequencial) * FALTA IMPLMENTAR A ALEATORIDADE

		// Falta gerar o nome aleatório do arquivo dentro da quantidade máxima de arquvios a serem gerados

		F_out = fopen(nome_arq, "wb");							// Abre o arquivo para escrita
		printf("\n arq %d - ord %d - num bytes -> %d",ord, it.ordem, it.n_bytes);	// Imprime na tela somente a título de controle
		fwrite(&it, sizeof(TipoItem),1,F_out);						// Escreve a estrutura no arquivo F_out
		fclose(F_out);									// Fecha o arquivo F_out
		ord ++;                         						// Incrementa o contador
	}

	fclose(F_in);								// Fecha o arquivo de leitura
	return ord;                                                             // Retorna a quantidade de arquvios criados
}

void decodifica (int ord, char * nome_arquivo) {
	FILE *F_in, *F_out;
	F_out = fopen(nome_arquivo, "wb");

	int i;
	char nome_arq[20];
	TipoItem it;
    No *raiz = NULL;

	for (i = 1; i < ord; i++) {
		sprintf(nome_arq, "files/%06d.dat", i); 				// Gera o nome do arquivo Sequencial para leitura
		F_in = fopen(nome_arq, "rb");					// Abre o arquivo para realizar a leitura da estrutura salva
		fread(&it, sizeof(TipoItem),1,F_in);				// Faz a leitura da estrutura conforme nome do arquivo

        insereAVL(&raiz, it);
        // ORDENAÇÃO DAS ESTRUTURAS LIDAS PELA AVL
        fclose(F_in);
    }

	// dois_imprimeAVL(&raiz); return;
	imprimeAVL(&raiz, F_out); return;

		// fwrite(&it.dados, sizeof(char),it.n_bytes,F_out);					// Escreve o it.dados CONFORME (indice/ordem) no arquivo de reconstrução
		// printf("\n Escrevendo arq %d - ord %d - num bytes -> %d",i, it.ordem, it.n_bytes);	// impressão de controke
		// fclose(F_in);										// Fecha o arquivo de leitura
	// }
	fclose(F_out);											// Fecha o arquivo de Escrita
}



int insereAVL(No **p, TipoItem inf_video) {
    int cresceu;
	int x = inf_video.ordem;

    // O no raiz esta vazio
    if(*p == NULL) { // Este IF esta OK
        *p = (No *) malloc(sizeof(No));

        (*p)->chave = x;
        (*p)->dir = (*p)->esq = NULL;
        (*p)->bal = 0;
		(*p)->inf_video = inf_video;

        printf("Inseri o valor chave: %d\n", (*p)->chave);
        // Esta subarvore cresceu
        cresceu = 1;
    }
    // Senao, verifica se tem que inserir a esquerda
    else if ((*p)->chave >= x) {
        // Tenta inserir a esquerda e ve se a subarvore cresceu

        puts("Chamando insereAVL (esquerda) again");
        cresceu = insereAVL(&(*p)->esq, inf_video);

        // Se cresceu for diferente de 0, logo a arvore cresceu
        if(cresceu) {
            // Verifica o estado atual de balanceamento
            switch ((*p)->bal) {
                // Se a arvore direita era maior entao nao ha crescimento
                case 1:
                    (*p)->bal = 0;
                    cresceu = 0;
                    break;
                // Se a subarvore direita tinha tamanho igual entao houve crescimento
                case 0:
                    (*p)->bal = -1;
                    cresceu = 1;
                    break;
                // Se a subarvore da esquerda ja era maior entao deve-se re-balancear
                case -1:
                    if((*p)->esq->bal == -1) {
                        // Rotacao para a direita
                        printf("Mandei rotacionar a raiz %d\n", (*p)->chave);
                        rot_dir(p);
                        // Arruma os balanceamentos
                        (*p)->bal = (*p)->dir->bal = 0;
                    }
                    else {
                        // Rotacao dupla
                        // Rotaciona primeiro a esquerda
                        printf("Mandei rotacionar o no %d\n", (*p)->esq->chave);
                        rot_esq(&(*p)->esq);
                        // Depois rotaciona a direita
                        printf("Mandei rotacionar a raiz %d\n", (*p)->chave);
                        rot_dir(p);
                        // Acerta balanceamentos
                        if((*p)->bal == -1) {
                            (*p)->esq->bal = 0;
                            (*p)->dir->bal = 1;
                        }
                        else {
                            (*p)->dir->bal = 0;
                            (*p)->esq->bal = -(*p)->bal;
                        }

                        (*p)->bal = 0;
                    }

                    cresceu = 0;
            }
        }
    }
    // Verifica se tem que inserir a direita
    else if((*p)->chave < x) {
        // Tenta inserir a direita e ve se a sub-arvore cresceu
        puts("Chamando insereAVL (direita) again");
        cresceu = insereAVL(&(*p)->dir, inf_video);

        if(cresceu) {
            // Verifica o estado atual de balanceamento
            switch ((*p)->bal) {
                // Se a arvore esquerda era maior entao nao ha crescimento
                case -1:
                    (*p)->bal = 0;
                    cresceu = 0;
                    break;
                // Se a arvore esquerda tinha tamanho igual entao houve crescimento
                case 0:
                    (*p)->bal = 1;
                    cresceu = 1;
                    break;
                // Se a arvore da direita ja era maior entao deve-se re-balancear
                case 1:
                    // Verifica qual o caso de re-balanceamentos
                    // Se a arvore da direita do filho da direita esta mais alta entao basta uma rotacao para a esquerda
                    if((*p)->dir->bal == 1) {
                        // Rotacao para a esquerda
                        printf("Mandei rotacionar a raiz %d\n", (*p)->chave);
                        rot_esq(p);
                        // Acerta os balanceamentos
                        (*p)->bal = (*p)->esq->bal = 0;
                    }
                    else {
                        // Rotacao dupla
                        // Primeiro a direita
                        printf("Mandei rotacionar a raiz %d\n", (*p)->dir->chave);
                        rot_dir(&(*p)->dir);
                        // Depois a esquerda
                        printf("Mandei rotacionar a raiz %d\n", (*p)->chave);
                        rot_esq(p);
                        // Acerta os balanceamentos
                        if((*p)->bal == -1) {
                            (*p)->esq->bal = 0;
                            (*p)->dir->bal = 1;
                        }
                        else {
                            (*p)->dir->bal = 0;
                            (*p)->esq->bal = -(*p)->bal;
                        }

                        (*p)->bal = 0;
                    }

                    cresceu = 0;
            }
        }
    }
    else
        cresceu = 0;

    puts("Saiu da insereAVL");
    return cresceu;
}

void imprimeAVL(No **p, FILE *out) {
    if((*p) != NULL) {
        imprimeAVL(&(*p)->esq, out);
		// Escreve o &(*p)->inf_video.dados CONFORME (indice/ordem) no arquivo de reconstrução
		fwrite(&(*p)->inf_video.dados, sizeof(char), (*p)->inf_video.n_bytes, out);
		printf("\n Escrevendo arq X - ord %d - num bytes -> %d", (*p)->inf_video.ordem, (*p)->inf_video.n_bytes);	// impressão de controke
        // printf("[%d]\n", (*p)->chave);
        imprimeAVL(&(*p)->dir, out);
    }
}

void dois_imprimeAVL(No **p) {
    if((*p) != NULL) {
        dois_imprimeAVL(&(*p)->esq);
        printf("[%d]\n", (*p)->chave);
        dois_imprimeAVL(&(*p)->dir);
    }
}

// Algoritmo que calcula a altura de uma arvore binaria de pesquisa
int altura_arvore(No **p) {
    int alt_esq, alt_dir;

    // Caso em que a arvore esta vazia.
    if((*p) == NULL) {
        return -1;
    }
    else {
        alt_esq = altura_arvore(&(*p)->esq);
        alt_dir = altura_arvore(&(*p)->dir);

        if(alt_esq > alt_dir)
            return alt_esq + 1;
        else
            return alt_dir + 1;
    }
}


int rot_dir(No **p) {
    No *q, *tmp;

    puts("Rotacionando para a direita");

    if((*p) == NULL)
        return 1;

    q = (*p)->esq;
    tmp = q->dir;
    q->dir = (*p);
    (*p)->esq = tmp;
    (*p) = q;

    return 0;
}

int rot_esq(No **p) {
    No *q, *tmp;

    puts("Rotacionando para a esquerda");
    if((*p) == NULL)
        return 1;

    q = (*p)->dir;
    tmp = q->esq;
    q->esq = (*p);
    (*p)->dir = tmp;
    (*p) = q;

    return 0;
}
