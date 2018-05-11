/*
 * File:   lib.c
 * Author: Aleffer Rocha and Rafael Siqueira
 *
 * Created on 8 de Maio de 2018, 16:19
 */

#include "lib.h"

int insereAVL(int x, No **p) {
    int cresceu;

    if(*p == NULL) {
        *p = (No *) malloc(sizeof(No));

        (*p)->chave = x;
        (*p)->dir = (*p)->esq = NULL;
        (*p)->bal = 0;
        // Esta subarvore cresceu
        cresceu = 1;
    }
    // Senao, verifica se tem que inserir a esquerda
    else if ((*p)->chave > x) {
        // Tenta inserir a esquerda e ve se a subarvore cresceu
        cresceu = insereAVL(x, &(*p)->esq);

        if(cresceu) {
            // Verifica o estado atual de balanceamento
            switch ((*p)->bal) {
                // Se a arvore direita era maior entao nao ha crescimento
                case 1:
                    (*p)->bal = 0;
                    cresceu = 0;
                    break;
                // Se a arvore direita tinha tamanhjo igual entao houve crescimento
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
                        rot_esq(p);
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
        cresceu = insereAVL(x, &(*p)->dir);

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

void imprimeAVL(No **p) {
    puts("Esquerda");
    imprimeAVL(&(*p)->esq);
    printf("[%d]\n", (*p)->chave);
    puts("Direita");
    imprimeAVL(&(*p)->dir);
}

int rot_dir(No **p) {
    if(p == NULL)
        return 1;

    (*p)->dir->dir = (*p)->esq;
    (*p)->esq = (*p)->dir->dir;

    return 0;
}

int rot_esq(No **p) {
    if(p == NULL)
        return 1;

    (*p)->esq->esq = (*p)->dir;
    (*p)->dir = (*p)->esq->esq;

    return 0;
}
