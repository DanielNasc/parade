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
    // imprimirBaralho(baralho);
    embaralhar(baralho);
    // imprimirBaralho(baralho);
    // removerTopo(baralho);
    // imprimirBaralho(baralho);

    ListaCarta *mao = criarLista(),
               *mesa = criarLista();

    inicializarMao(mao, baralho);
    inicializarMesa(mesa, baralho);

    // printf("MAO: ==============\n");
    // imprimirLista(mao);
    // printf("MESA: ==============\n");
    // imprimirLista(mesa);

    Galeria *galeria = criarGaleria();
    inicializarGaleria(galeria);

    printf("MAO ANTES =========\n");
    imprimirLista(mao);
    Carta *random = removerIndice(mao, 0);
    inserirFim(mao, removerTopo(baralho));
    printf("MAO DEPOIS =========\n");
    imprimirLista(mao);
    printf("MESA ANTES ========\n");
    imprimirLista(mesa);
    removerQualquerCartaValida(mesa, galeria, random);
    printf("MESA DEPOIS =======\n");
    imprimirLista(mesa);
    printf("GALERIA ===========\n");
    imprimirGaleria(galeria);
    printf("MESA DEPOIS DEPOIS =======\n");
    inserirFim(mesa, random);
    imprimirLista(mesa);
}