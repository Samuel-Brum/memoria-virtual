#include <stdio.h>


typedef struct {
   unsigned long pag;
   struct no *prox;
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
