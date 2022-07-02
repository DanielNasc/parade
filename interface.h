#ifndef INTERFACE_H
#define INTERFACE_H

#include <stdbool.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h> //apontar o cursor para uma coordenada da tela
#include <conio.h>   //capturar uma tecla
#include <locale.h>

#include "pilha.h"
#include "jogo.h"
#include "save.h"

#define SAIR_PROMPT 555

// ======================= IMPRESSÃO =======================

// Nome da cor da letra
enum letras
{
    BLACK,
    BLUE,
    GREEN,
    CYAN,
    RED,
    MAGENTA,
    BROWN,
    LIGHTGRAY,
    DARKGRAY,
    LIGHTBLUE,
    LIGHTGREEN,
    LIGHTCYAN,
    LIGHTRED,
    LIGHTMAGENTA,
    YELLOW,
    WHITE
};

// Nome da cor do fundo
enum fundo
{
    _BLACK = 0,
    _BLUE = 16,
    _GREEN = 32,
    _CYAN = 48,
    _RED = 64,
    _MAGENTA = 80,
    _BROWN = 96,
    _LIGHTGRAY = 112,
    _DARKGRAY = 128,
    _LIGHTBLUE = 144,
    _LIGHTGREEN = 160,
    _LIGHTCYAN = 176,
    _LIGHTRED = 192,
    _LIGHTMAGENTA = 208,
    _YELLOW = 224,
    _WHITE = 240
};

// IMPRESSÔES ==================================
void imprimirBaralho(Baralho *);
void imprimirMao(ListaCarta *);
void imprimirMesa(ListaCarta *);
void imprimirJogador();
void imprimirComputer();
void imprimirCartaEscolhida(Carta *, int);
void imprimirNaipesColecao();
void imprimirControles(int, int);
void imprimirUltimaCarta();
void imprimirDuasCartas();
void imprimirGanhoDePontos(int, int);
void imprimirBoxMesa();
void imprimirGaleriaContagemDePontos(char *, int, Galeria *);

// FUNÇÕES BASE ==================================
void fullscreen();
void mudarTamanhoJanela(int, int);
void mudarFonte();
void clearStdin();
void linhaCol(int, int);
void box(int, int, int, int);
void corTexto(int, int);
void clearStdin();
int question();

void inicializarAtributosPadrao();
void resetarAtributos();

// FUNÇÕES MUDANÇA DE COR ==================================
void corDaVez(int);
int corDaCarta(char);

// INTERFACE ==================================
void aviso();
void menu(int);
void carregando();
void chamarJogo(int);
void manual();
void telas(int);
void escolhaTela();
void ranking(Score *);

int imprimirSair();
int indicadorDeCarta(int);
int indicador(int);
int escolhaCarta(ListaCarta *, int);
int escolhaMenu();

// FIM DE JOGO ================================
int chamarPlacar(Computador *, Jogador *, int);
void nomeDoSave(char *);
void vitoriaPontuacao(int);
void vitoriaNormal();
void vitoriaPerfeita();
void derrota();

#endif // INTERFACE_H