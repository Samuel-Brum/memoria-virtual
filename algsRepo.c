unsigned long randomRep(Quadro* quadros, int num_quadros) {
    
    //Adicionar srandom para trocar a seed
    int num_quadro_troca = random() % num_quadros;
    unsigned long num_pag_troca = quadros[num_quadro_troca].numero_pagina;
    return num_pag_troca;
}


//Manipular as estruturas (fila e pilha) dentro ou fora das funções?

unsigned long fifoRep(unsigned long num_pag, Lista* fila) {
    unsigned long num_pag_troca = removerInicio(fila);
    adicionarFim(fila, num_pag);
    return num_pag_troca;
}


//unsigned long lruRep(unsigned long num_pag, Lista* pilha) {
//    unsigned long num_pag_troca = pilha.pop();
//    pilha.adicionar(num_pag);
//    return num_pag_troca;
//}
//
//
//unsigned long SegChanceRep()