#ifndef JOGO_H
#define JOGO_H

#include <stdbool.h>
#include "lista.h"
#include "pilha.h"

typedef struct jogador Jogador;
typedef struct computador Computador;

#define SAIR_PARTIDA 999
#define PONTOS_VITORIA_NORMAL -100
#define PONTOS_VITORIA_PERFEITA -999
#define SCORE_VAZIO 9999999
#define PERDEU -1

typedef enum tipoVitoria
{
    NENHUMA,
    NORMAL,
    PERFEITA,
} TipoVitoria;

Jogador *criarJogador();
Computador *criarComputador();

bool inicializarMao(Jogador *, Baralho *);
bool inicializarMesa(ListaCarta *, Baralho *);

// JOGAR ======================================
int jogadaPlayer(Jogador *, ListaCarta *, Baralho *);
void jogadaComputador(Computador *, Baralho *, ListaCarta *);
void imprimirGaleriaJogador(Jogador *);
void chamarContagem(Jogador *);
void chamarGaleriaComputador(Computador *);

// FIM DE JOGO ================================
int chamarPlacar(Computador *, Jogador *, int);
int compararPontuacoes(Jogador *, Computador *);
int colocarDuasCartasGaleria(Jogador *);
bool fimDeJogo(Jogador *, Computador *, Baralho *, ListaCarta *);
TipoVitoria checarVitoriaJogador(Jogador *);

void imprimirMaoJogador(Jogador *);
void imprimirGaleriaJogador(Jogador *);

void partida();

#endif // JOGO_H