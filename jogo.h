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
bool fimDeJogo(Jogador *, Computador *, Baralho *, ListaCarta *);
int compararPontuacoes(Jogador *, Computador *);
int colocarDuasCartasGaleria(Jogador *);
TipoVitoria checarVitoriaJogador(Jogador *);
bool checarSeJogadorTemUmaCartaDeCadaCor(Galeria *);

void imprimirMaoJogador(Jogador *);
void imprimirGaleriaJogador(Jogador *);

void partida();

#endif // JOGO_H