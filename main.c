#include <stdio.h>
#include <stdlib.h>
#include "parade.h"

void testes();

int main () {
    testes();

    return 0;
}

void testes() {
    Baralho *baralho = criarBaralho();
    enfiarCartasNoBaralho(baralho);
    imprimirBaralho(baralho);
    embaralhar(baralho);
    imprimirBaralho(baralho);
    removerTopo(baralho);
    imprimirBaralho(baralho);
}