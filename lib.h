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

/* Tamanho de bytes a serem armazenados por no */
#define TAM 1024
/*
 * Sobre int bal (balanceamento):
 *     -1 se a subarvore esquerda e maior;
 *     0 se esta balanceado;
 *     1 se a subarvore direita e maior.
 */
typedef struct _no {
    int chave;
    int bal;
    struct _no *esq;
    struct _no *dir;
} No;

int insereAVL(int x, No **p);

void imprimeAVL(No **p);

int rot_dir(No **p);

int rot_esq(No **p);
