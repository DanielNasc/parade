#ifndef JOGO_H
#define JOGO_H
#include <stdbool.h>
#include "lista.h"
#include "pilha.h"

typedef struct jogador Jogador;
typedef struct computador Computador;

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
void jogadaPlayer(Jogador *, ListaCarta *, Baralho *);
void jogadaComputador(Computador *, Baralho *, ListaCarta *);
void imprimirGaleriaJogador(Jogador *);
void imprimirGaleriaComputador(Computador *);

// FIM DE JOGO ================================
bool fimDeJogo(Jogador *, Computador *, Baralho *, ListaCarta *);
int compararPontuacoes(Jogador *, Computador *);
void colocarDuasCartasGaleria(Jogador *);
TipoVitoria checarVitoriaJogador(Jogador *);
bool checarSeJogadorTemUmaCartaDeCadaCor(Galeria *);

#endif // JOGO_H