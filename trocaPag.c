#include "memoria.c"

void trocarPagDensa(unsigned long num_pag, int num_pag_troca, EntradaTabelaPagina* tabela_paginas, Quadro* quadros) {
    int num_quadro_troca = tabela_paginas[num_pag_troca].numero_quadro;

    if(quadros[num_quadro_troca].modificado == 1) {
        tabela_paginas[num_pag_troca].modificado = 1;
    }

    tabela_paginas[num_pag_troca].numero_quadro = -1;
    tabela_paginas[num_pag_troca].valido = 0;

    tabela_paginas[num_pag].numero_quadro = num_quadro_troca;
    tabela_paginas[num_pag].valido = 1;

    quadros[num_quadro_troca].numero_pagina = num_pag;
    quadros[num_quadro_troca].modificado = 0;
}

void trocarPagHierarquica2() {
    
}

void trocarPagHierarquica3() {
    
}

void trocarPagInvertida() {

}
