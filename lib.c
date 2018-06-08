/*
 * File:   lib.c
 * Author: Aleffer Rocha and Rafael Siqueira
 *
 * Created on 8 de Maio de 2018, 16:19
 */

#include "lib.h"

int codifica(char * nome_arquivo, char *diretorio, int sfile) {
	FILE *F_in, *F_out;							// ponteiros - arquivo - F_in (leitura) - F_out (Escrita)
	F_in = fopen (nome_arquivo,"rb");			// Arquivo - dados originais
	Pacote pct;								// aux da estrutura
	int ord = 0;								// contador/ordem dos bytes lidos
	char nome_arq[20];							// nome do arquivo a ser gravado
	int al, i;
	char *paleta = (char *) malloc(sizeof(char) * (sfile / TAM));

	sfile = (sfile/TAM);
	// Inicializando a paleta com 'o'
	for(i = 0; i < sfile; i++)
		paleta[i] = 'o';

	srand(time(NULL));

	while (!feof(F_in)) {
		pct.n_bytes = fread(pct.dados, 1, TAM, F_in);			// leitura dos bytes do arquivo F_IN / Salva na estrututa qnt_bytes lidos
		pct.ordem = ord; 						// Posicao (indice/ordem) dos dados lidos no arquivo original
		sprintf(nome_arq, "%s/%06d.dat", diretorio, ord); 				// escreve o nome do arquivo (Sequencial) * FALTA IMPLMENTAR A ALEATORIDADE

		al = rand() % sfile;

		for(i = al; i < sfile; i++){
			if(paleta[i] != 'x'){
				paleta[i] = 'x';
				break;
			}

			i++;
			al = i;

			if(i == (sfile - 1)){
				i = 0;
			}
		}

		F_out = fopen(nome_arq, "wb");							// Abre o arquivo para escrita
		printf("\n arq %d - ord %d - num bytes -> %d", al, pct.ordem, pct.n_bytes);	// Imprime na tela somente a titulo de controle
		fwrite(&pct, sizeof(Pacote), 1, F_out);						// Escreve a estrutura no arquivo F_out
		fclose(F_out);									// Fecha o arquivo F_out
		ord ++;                         						// Incrementa o contador
	}

	fclose(F_in);								// Fecha o arquivo de leitura
	return ord;                                                             // Retorna a quantidade de arquvios criados
}

void decodifica (int qtd_arquivos, char * nome_arquivo, char *diretorio) {
	FILE *F_in, *F_out;
	F_out = fopen(nome_arquivo, "wb");

	int i;
	char nome_arq[30];
	Pacote pct;
    No *raiz = NULL;

	for (i = 0; i < qtd_arquivos; i++) {
		sprintf(nome_arq, "%s/%06d.dat", diretorio, i); 				// Gera o nome do arquivo Sequencial para leitura

		F_in = fopen(nome_arq, "rb");					// Abre o arquivo para realizar a leitura da estrutura salva
		fread(&pct, sizeof(Pacote), 1, F_in);				// Faz a leitura da estrutura conforme nome do arquivo
        insereAVL(&raiz, pct);
        fclose(F_in);
    }

	imprimeAVL(&raiz, F_out);

	fclose(F_out);											// Fecha o arquivo de Escrita
}

int insereAVL(No **p, Pacote inf_pct) {
    int cresceu;
	int x = inf_pct.ordem;

    // O no raiz esta vazio
    if(*p == NULL) {
        *p = (No *) malloc(sizeof(No));

        (*p)->chave = x;
        (*p)->dir = (*p)->esq = NULL;
        (*p)->bal = 0;
		(*p)->inf_pct = inf_pct;

        // Esta subarvore cresceu
        cresceu = 1;
    }
    // Senao, verifica se tem que inserir a esquerda
    else if ((*p)->chave >= x) {
        // Tenta inserir a esquerda e ve se a subarvore cresceu

        // puts("Chamando insereAVL (esquerda) again");
        cresceu = insereAVL(&(*p)->esq, inf_pct);

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
                        rot_dir(p);
                        // Arruma os balanceamentos
                        (*p)->bal = (*p)->dir->bal = 0;
                    }
                    else {
                        // Rotacao dupla
                        // Rotaciona primeiro a esquerda
                        rot_esq(&(*p)->esq);
                        // Depois rotaciona a direita
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
        cresceu = insereAVL(&(*p)->dir, inf_pct);

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
                    if((*p)->dir->bal == 1) {
                        // Rotacao para a esquerda
                        rot_esq(p);
                        // Acerta os balanceamentos
                        (*p)->bal = (*p)->esq->bal = 0;
                    }
                    else {
                        // Rotacao dupla
                        // Primeiro a direita
                        rot_dir(&(*p)->dir);
                        // Depois a esquerda
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

    return cresceu;
}

void imprimeAVL(No **p, FILE *out) {
    if((*p) != NULL) {
        imprimeAVL(&(*p)->esq, out);
		// Escreve o &(*p)->inf_video.dados CONFORME (indice/ordem) no arquivo de reconstrução
		fwrite(&(*p)->inf_pct.dados, sizeof(char), (*p)->inf_pct.n_bytes, out);
		printf("\n Escrevendo arq X - ord %d - num bytes -> %d", (*p)->inf_pct.ordem, (*p)->inf_pct.n_bytes);	// impressão de controke
        imprimeAVL(&(*p)->dir, out);
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

    if((*p) == NULL) return 1;

    q = (*p)->esq;
    tmp = q->dir;
    q->dir = (*p);
    (*p)->esq = tmp;
    (*p) = q;

    return 0;
}

int rot_esq(No **p) {
    No *q, *tmp;

    if((*p) == NULL) return 1;

    q = (*p)->dir;
    tmp = q->esq;
    q->esq = (*p);
    (*p)->dir = tmp;
    (*p) = q;

    return 0;
}

unsigned long int tamanho_arquivo (FILE* in) {
	unsigned long int tamanho;
	unsigned long int atual = ftell(in);

	fseek(in, 0, SEEK_END);
	tamanho = ftell( in );
	fseek(in, atual, SEEK_SET);

	return tamanho;
}
