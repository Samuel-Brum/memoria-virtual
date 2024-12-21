#ifndef ALGS_REPO_H
#define ALGS_REPO_H

#include "memoria.h"
#include "lista.h"

unsigned long randomRep(Quadro* quadros, int num_quadros);
unsigned long fifoRep(unsigned long num_pag, Lista* fila);
unsigned long lruRep(unsigned long num_pag, Lista* lru);
void atualizaLRU(Lista* lru, unsigned long pag);

#endif