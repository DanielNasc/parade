#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

#include "carta.h"
#include "jogo.h"
#include "lista.h"
#include "pilha.h"
#include "interface.h"

void testes();

int main()
{
    // imprimeCaixa(1, 1, 80, 25);
    // corTurno(true);
    menu(500);
    // testes();
    getch();

    return 0;
}

void testes()
{
    Baralho *baralho = criarBaralho();
    enfiarCartasNoBaralho(baralho);
    // imprimirBaralho(baralho);
    embaralhar(baralho);
    // imprimirBaralho(baralho);
    // removerTopo(baralho);
    // imprimirBaralho(baralho);

    ListaCarta *mesa = criarLista();

    inicializarMesa(mesa, baralho);

    // printf("MAO: ==============\n");
    // imprimirLista(mao);
    // printf("MESA: ==============\n");
    // imprimirLista(mesa);

    // Galeria *galeria = criarGaleria();
    // inicializarGaleria(galeria);

    // printf("MAO ANTES =========\n");
    // imprimirLista(mao);
    // Carta *random = removerIndice(mao, 0);
    // inserirFim(mao, removerTopo(baralho));
    // printf("MAO DEPOIS =========\n");
    // imprimirLista(mao);

    // preencher mesas com varias cartas para teste
    // for (int i = 0; i < 30; i++)
    //     inserirFim(mesa, removerTopo(baralho));

    // printf("MESA ANTES ========\n");
    // imprimirLista(mesa);
    // removerQualquerCartaValida(mesa, galeria, random);
    // // printf("MESA DEPOIS =======\n");
    // // imprimirLista(mesa);
    // printf("GALERIA ===========\n");
    // imprimirGaleria(galeria);
    // printf("MESA DEPOIS DEPOIS =======\n");
    // inserirFim(mesa, random);
    // imprimirLista(mesa);

    Jogador *jogador = criarJogador();
    Computador *computador = criarComputador();

    inicializarMao(jogador, baralho);

    // jogadaPlayer(jogador, mesa);

    // printf("MESA DEPOIS =======\n");
    // imprimirLista(mesa);

    // imprimirGaleriaJogador(jogador);

    // printf("JOGADA DO COMPUTADOR ===========\n");
    // jogadaComputador(computador, baralho, mesa);

    // printf("MESA DEPOIS DEPOIS =======\n");
    // imprimirLista(mesa);

    // imprimirGaleriaComputador(computador);

    // fluxo de jogo

    while (1)
    {
        printf("MESA ANTES ========\n");
        imprimirLista(mesa);

        printf("Tamanho do baralho: %i\n", tamanhoBaralho(baralho));
        jogadaPlayer(jogador, mesa, baralho);

        if (fimDeJogo(jogador, computador, baralho, mesa))
            break;

        printf("MESA DEPOIS PLAYER =======\n");
        imprimirLista(mesa);

        jogadaComputador(computador, baralho, mesa);

        if (fimDeJogo(jogador, computador, baralho, mesa))
            break;

        printf("MESA DEPOIS COMPUTADOR =======\n");
        imprimirLista(mesa);

        printf("Galeria do jogador =========\n");
        imprimirGaleriaJogador(jogador);
    }
}