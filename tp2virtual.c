#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "memoria.h"
#include "lista.h"
#include "algsRepo.h"
#include "trocaPag.h"

typedef enum { LRU, SEGUNDA_CHANCE, FIFO, RANDOM } AlgoritmoSubstituicao;
typedef enum { DENSA, DOIS_NIV, TRES_NIV, INVERTIDA } TipoTabelaPaginas;


AlgoritmoSubstituicao parse_algorithm(char* nome);
TipoTabelaPaginas parse_page_table_type(char* name);
void simula(AlgoritmoSubstituicao algoritmo, TipoTabelaPaginas tipo_tabela_pags, char* nome_arquivo, int tam_pag_kb, int tam_mem_kb);

int main(int argc, char* argv[]) {
    if (argc != 6) {
        printf("Uso: tp2virtual <algoritmo> <tipo_de_tabela_de_pag> <arquivo> <tamanho_da_pagina_kb> <tamanho_da_memoria_kb>\n");
        return 1;
    }

    AlgoritmoSubstituicao algoritmo = parse_algorithm(argv[1]);
    TipoTabelaPaginas tipo_tabela_pags = parse_page_table_type(argv[2]);
    char* nome_arquivo = argv[3];
    char* arq_print = strrchr(nome_arquivo, '/');
    arq_print++;  
    int tam_pag_kb = atoi(argv[4]);
    int tam_mem_kb = atoi(argv[5]);

    printf("Executando o simulador...\n");
    //printf("Arquivo de entrada: %s\n", arq_print);
    printf("Tamanho da memoria: %d\n", tam_mem_kb);
    printf("Tamanho das paginas: %d\n", tam_pag_kb);
    printf("Tecnica de reposicao: %s\n", argv[1]);

    simula(algoritmo, tipo_tabela_pags, nome_arquivo, tam_pag_kb, tam_mem_kb);
    return 0;
}

AlgoritmoSubstituicao parse_algorithm(char* name) {
    if (strcmp(name, "lru") == 0) {
        return LRU;
    } else if (strcmp(name, "2a") == 0) {
        return SEGUNDA_CHANCE;
    } else if (strcmp(name, "fifo") == 0) {
        return FIFO;
    } else if (strcmp(name, "random") == 0) {
        return RANDOM;
    } else {
        printf("Algoritmo invalido: %s\n", name);
        exit(1);
    }
}

TipoTabelaPaginas parse_page_table_type(char* name) {
    if (strcmp(name, "densa") == 0) {
        return DENSA;
    } else if (strcmp(name, "2_niveis") == 0) {
        return DOIS_NIV;
    } else if (strcmp(name, "3_niveis") == 0) {
        return TRES_NIV;
    } else if (strcmp(name, "invertida") == 0) {
        return INVERTIDA;
    } else {
        printf("Paginação inválida: %s\n", name);
        exit(1);
    }
}

void simula(AlgoritmoSubstituicao algoritmo, TipoTabelaPaginas tipo_tabela_pags, char* nome_arquivo, int tam_pag_kb, int tam_mem_kb) {
  int tam_pag = tam_pag_kb * 1024;
  int tam_mem = tam_mem_kb * 1024;
  int num_quadros = tam_mem / tam_pag;

  // Inicializa tabela de páginas e tabela de quadros
  // Comecei com o caso mais simples, tem mais tres que têm que serem implementados pra comparar no relatorio

  Quadro* quadros = malloc(sizeof(Quadro) * num_quadros);
  for (int i = 0; i < num_quadros; i++) {
    quadros[i].numero_pagina = 0;
    quadros[i].modificado = 0;
  }

  unsigned long paginas_lidas = 0;
  unsigned long page_faults = 0;
  unsigned long paginas_escritas = 0;
  unsigned long tempo = 0;

  EntradaTabelaPagina* tabela_paginas = NULL;
  unsigned long num_pags = (unsigned long)(1UL << 32) / tam_pag; 

  if(tipo_tabela_pags == DENSA) {
    tabela_paginas = malloc(sizeof(EntradaTabelaPagina) * num_pags);
        for (unsigned long i = 0; i < num_pags; i++) {
            tabela_paginas[i].valido = 0;
        }
  }


  // Inicializar estruturas de suporte (listas, pilhas, filas)
  Lista *lista = malloc(sizeof(Lista));
  lista->raiz = NULL;
  lista->ultimo = NULL;


  // Processsamento do arquivo

  FILE* arquivo = fopen(nome_arquivo, "r");
  if (!arquivo) {
      printf("Erro ao abrir arquivo %s\n", nome_arquivo);
      exit(1);
  }

  char linha[100];
  while (fgets(linha, sizeof(linha), arquivo)) {
    char* str_endereco = strtok(linha, " ");
    char* operacao = strtok(NULL, " \n");
    unsigned long endereco = strtoul(str_endereco, NULL, 16);
    char op = operacao[0];

    paginas_lidas++;
    unsigned long num_pag = endereco / tam_pag;

    int page_fault_flag = 0;
    int num_quadro = -1;

    if (tipo_tabela_pags == DENSA) {
      EntradaTabelaPagina* entrada = &tabela_paginas[num_pag];

      if (!entrada->valido) {
        // Page fault
        page_faults++;
        page_fault_flag = 1;

        // Procura endereco vago
        for (int i = 0; i < num_quadros; i++) {
          if (quadros[i].numero_pagina == 0 && quadros[i].modificado == 0) {
            num_quadro = i;
            tabela_paginas[num_pag].numero_quadro = i;
            tabela_paginas[num_pag].valido = 1;
            quadros[i].numero_pagina = num_pag;

            adicionarFim(lista, num_pag);

            break;
          }
        }

        //Se necessário, faz reposição
        if (num_quadro == -1) {
          unsigned long num_pag_troca;
          
          if(algoritmo == RANDOM) {
            num_pag_troca = randomRep(quadros, num_quadros);
          }

          if(algoritmo == FIFO) {
            num_pag_troca = fifoRep(num_pag, lista);
          }

          if(algoritmo == LRU) {
            adicionarFim(lista, num_pag);
          }

          trocarPagDensa(num_pag, num_pag_troca, tabela_paginas, quadros);
          
        } 
        else {
          if (algoritmo == LRU) {
            unsigned long num_pag_troca = lruRep(num_pag, lista);
            trocarPagDensa(num_pag, num_pag_troca, tabela_paginas, quadros);
          } 
          else if (algoritmo == SEGUNDA_CHANCE) {
            unsigned long num_pag_troca = segundaChanceRep(lista, quadros, num_quadros);
            trocarPagDensa(num_pag, num_pag_troca, tabela_paginas, quadros);  
          }
        }
      } 
      else {
        if (op == 'R' || op == 'W') {
        quadros[tabela_paginas[num_pag].numero_quadro].referencia = 1;
        }
        
        if(algoritmo == LRU) {
          atualizaLRU(lista, num_pag);
        }
      }

      //Manipular pag dps da reposição
      if(op == 'W') {
        quadros[tabela_paginas[num_pag].numero_quadro].modificado = 1;
        paginas_escritas++;
      }
    }  
    
    tempo++;
  }

  // printf("Paginas lidas: %d\n", paginas_lidas); quebrado
  // printf("Paginas escritas: %d\n", paginas_escritas); quebrado
  printf("Page Faults: %lu\n", page_faults);
}
