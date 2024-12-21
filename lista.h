#ifndef LISTA_H
#define LISTA_H

typedef struct No {
    unsigned long pag;
    struct No *prox;
} No;

typedef struct {
    No *raiz;
    No *ultimo;
} Lista;

void adicionarFim(Lista *lista, unsigned long pag);
No* removerInicio(Lista *lista);
No* removerNo(Lista *lista, unsigned long pag);

#endif