#ifndef MEMORIA_H
#define MEMORIA_H

typedef struct {
  unsigned long numero_pagina;
  int numero_quadro;
  int valido;
  int modificado;
  int referencia;
} EntradaTabelaPagina;

typedef struct {
    unsigned long numero_pagina;
    int modificado;
    int referencia;
} Quadro;

#endif