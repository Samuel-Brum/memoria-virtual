#ifndef TROCA_PAG_H
#define TROCA_PAG_H

#include "memoria.h"

void trocarPagDensa(unsigned long num_pag, unsigned long num_pag_troca, EntradaTabelaPagina* tabela_paginas, Quadro* quadros);
void trocarPagHierarquica2(unsigned long num_pag, unsigned long num_pag_troca);
void trocarPagHierarquica3(unsigned long num_pag, unsigned long num_pag_troca);
void trocarPagInvertida(unsigned long num_pag, unsigned long num_pag_troca);

#endif