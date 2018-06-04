/*
 * File:   lib.h
 * Author: Aleffer Rocha and Rafael Siqueira
 *
 * Created on 8 de Maio de 2018, 16:19
 */
#ifndef _H_AVL
#define _H_AVL

#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <time.h>

/* Tamanho de bytes a serem armazenados por no */
#define TAM 1024
/*
 * Sobre int bal (balanceamento):
 *     -1 se a subarvore esquerda e maior;
 *     0 se esta balanceado;
 *     1 se a subarvore direita e maior.
 */

 //Estrutura das partes do vídeo
 typedef struct _item {
     char dados[TAM]; // bytes de vídeo
     int ordem; // índice do vídeo
     int n_bytes; // quantidade de bytes lidos
 } Pacote;

// Estrutura de um nó da arvore AVL
typedef struct _no {
    int chave; // Valor chave
    int bal; // Indice de balanceamento
    Pacote inf_pct;
    struct _no *esq; // Ponteiro para a subarvore esquerda
    struct _no *dir; // Ponteiro para a subarvore direita
} No;


int codifica(char * nome_arquivo, char *diretorio, int sfile);

void decodifica (int ord, char * nome_arquivo, char *diretorio);

// Recebe um inteiro x e um no **p que aponta para a raiz da arvore
// Insere x na arvore
int insereAVL(No **p, Pacote inf);

// Recebe um no **p que aponta para a raiz da arvore
// Imprime o item chave de cada no da arvore
void imprimeAVL(No **p, FILE *out);

// Recebe um no **p que aponta para a raiz da arvore
int altura_arvore(No **p);

void dois_imprimeAVL(No **p);

// Recebe um no **p que aponta para a raiz da arvore
// Rotaciona este no para a direita
int rot_dir(No **p);

// Recebe um no **p que aponta para a raiz da arvrore
// Rotaciona este no para a esquerda
int rot_esq(No **p);

unsigned long int tamanho_arquivo (FILE* in);

#endif
