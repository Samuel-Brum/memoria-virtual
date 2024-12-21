#include <stdlib.h>

#include "memoria.h"
#include "lista.h"


unsigned long randomRep(Quadro* quadros, int num_quadros) {
    
    //Adicionar srandom para trocar a seed
    int num_quadro_troca = random() % num_quadros;
    unsigned long num_pag_troca = quadros[num_quadro_troca].numero_pagina;
    return num_pag_troca;
}


//Manipular as estruturas (fila e pilha) dentro ou fora das funções?

unsigned long fifoRep(unsigned long num_pag, Lista* fila) {
    unsigned long num_pag_troca = removerInicio(fila)->pag;
    adicionarFim(fila, num_pag);
    return num_pag_troca;
}


unsigned long lruRep(unsigned long nova_pag, Lista* lru) {
    No* removido = removerInicio(lru);
    unsigned long pag_trocada = removido->pag;
    free(removido);
    adicionarFim(lru, nova_pag);
    return pag_trocada;
}

void atualizaLRU(Lista* lru, unsigned long pag) {
    No* removido = removerNo(lru, pag);
    if (removido) {
        free(removido);
    }
    adicionarFim(lru, pag);
}
//
//
//unsigned long SegChanceRep()
