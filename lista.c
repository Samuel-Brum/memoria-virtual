#ifndef LISTA_H
#define LISTA_H


#include <stdio.h>
#include <stdlib.h>


typedef struct No {
    unsigned long pag;
    struct No *prox;
} No;

typedef struct {
    No *raiz;
    No *ultimo;
} Lista;

void adicionarFim(Lista *lista, unsigned long pag) {
    No *novoNo = malloc(sizeof(No));
    novoNo->pag = pag;
    novoNo->prox = NULL;

    if(lista->raiz == NULL) {
        lista->raiz = novoNo;
        lista->ultimo = novoNo;
    }
    else {
        lista->ultimo->prox = novoNo;
        lista->ultimo = novoNo;
    }
}

No* removerInicio(Lista *lista) {
    No *aux = lista->raiz;
    lista->raiz = lista->raiz->prox;
    return aux;
}

No* removerNo(Lista *lista, unsigned long pag) {
    No *ant = NULL;
    No *atual = lista->raiz;
    while (atual && atual->pag != pag) {
        ant = atual;
        atual = atual->prox;
    }
    if (!atual) return NULL;
    if (!ant) {
        lista->raiz = atual->prox;
    } else {
        ant->prox = atual->prox;
    }
    if (lista->ultimo == atual) {
        lista->ultimo = ant;
    }
    return atual;
}



#endif