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

//void atualizarPag(Lista *lista, unsigned long pag) {
//    No* atual = malloc(sizeof(No));
//
//    if(lista->raiz->pag == pag) {
//        atual = lista->raiz;
//        lista->raiz = lista->raiz->prox;
//
//        adicionarFim(lista, pag);
//    }
//    else {
//        atual = lista->raiz;
//        while(atual->prox->pag != pag) {
//            atual = atual->prox;
//        }
//        atual->prox = atual->prox->prox;
//        
//        adicionarFim(lista, pag);
//    }
//}


void atualizarPag(Lista *lista, unsigned long pag) {
    // Verificar se a lista está vazia
    if (lista->raiz == NULL) {
        fprintf(stderr, "Erro: A lista está vazia.\n");
        return;
    }

    // Caso especial: a página já está na raiz
    if (lista->raiz->pag == pag) {
        No *atual = lista->raiz;
        lista->raiz = lista->raiz->prox;
        adicionarFim(lista, pag);
        free(atual); // Liberar o nó removido
        return;
    }

    // Percorrer a lista para encontrar a página
    No *atual = lista->raiz;
    while (atual->prox != NULL && atual->prox->pag != pag) {
        atual = atual->prox;
    }

    // Verificar se a página foi encontrada
    if (atual->prox == NULL) {
        fprintf(stderr, "Erro: Página %lu não encontrada na lista.\n", pag);
        return;
    }

    // Atualizar a lista
    No *remover = atual->prox;
    atual->prox = remover->prox;
    adicionarFim(lista, pag);
    free(remover); // Liberar o nó removido
}




#endif