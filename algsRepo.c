#include <stdlib.h>

#include "memoria.h"
#include "algsRepo.h"
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

unsigned long segundaChanceRep(Lista* scLista, Quadro* quadros, int num_quadros) {
    while (1) {
        unsigned long pag = scLista->raiz->pag;
        // Acha o quadro que contém essa página
        for (int i = 0; i < num_quadros; i++) {
            if (quadros[i].numero_pagina == pag) {
                if (quadros[i].referencia == 1) {
                    // Dá segunda chance: zera referência e move pro fim da fila
                    quadros[i].referencia = 0;
                    No* removido = removerInicio(scLista);
                    adicionarFim(scLista, pag);
                } else {
                    // Se referência é 0, remove da fila e retorna a página como vítima
                    removerInicio(scLista);
                    return pag;
                }
                break;
            }
        }
    }
}
