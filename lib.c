/*
 * File:   lib.c
 * Author: Aleffer Rocha and Rafael Siqueira
 *
 * Created on 8 de Maio de 2018, 16:19
 */

#include "lib.h"

int insereAVL(int x, No **p) {
    int cresceu;

    // O no raiz esta vazio
    if(*p == NULL) { // Este IF esta OK
        *p = (No *) malloc(sizeof(No));

        (*p)->chave = x;
        (*p)->dir = (*p)->esq = NULL;
        (*p)->bal = 0;

        printf("Inseri o valor chave: %d\n", (*p)->chave);
        // Esta subarvore cresceu
        cresceu = 1;
    }
    // Senao, verifica se tem que inserir a esquerda
    else if ((*p)->chave >= x) {
        // Tenta inserir a esquerda e ve se a subarvore cresceu

        puts("Chamando insereAVL (esquerda) again");
        cresceu = insereAVL(x, &(*p)->esq);

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

void imprimeAVL(No **p) {
    if((*p) != NULL) {
        imprimeAVL(&(*p)->esq);
        printf("[%d]\n", (*p)->chave);
        imprimeAVL(&(*p)->dir);
    }
}

// Algoritmo que calcula a altura de uma arvore binaria de pesquisa
int altura_arvore(No **p) {
    int alt_esq, alt_dir;

    if((*p) == NULL) {
        puts("A arvore esta vazia.");
        return -1;
    }
    else {
        alt_esq = altura_arvore((*p)->esq);
        alt_dir = altura_arvore((*p)->dir);

        if(alt_esq > alt_dir)
            return alt_esq + 1;
        else
            return alt_dir + 1;
    }
}


int rot_dir(No **p) {
    puts("Rotacionando para a direita");
    if((*p) == NULL)
        return 1;

    (*p)->dir = (*p)->esq;
    (*p)->esq = (*p)->dir;

    return 0;
}

int rot_esq(No **p) {
    puts("Rotacionando para a esquerda");
    if((*p) == NULL)
        return 1;
    (*p)->esq = (*p)->dir;
    (*p)->dir = (*p)->esq;

    return 0;
}
