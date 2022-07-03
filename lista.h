#ifndef LISTA_H
#define LISTA_H

#include <stdbool.h>
#include "carta.h"

#define QTD_LOOPS_PREENCHER_MAO 5

typedef struct listaCarta ListaCarta;
typedef struct colecao Colecao;
typedef struct galeria Galeria;

ListaCarta *criarLista();
Colecao *criarColecao(char);
Galeria *criarGaleria();

bool inserirInicio(ListaCarta *, Carta *);
bool removerQualquerCartaValida(ListaCarta *, Galeria *, Carta *);

Carta *primeiraCarta(ListaCarta *);
Carta *ultimaCarta(ListaCarta *);
Carta *primeiraCartaAposBloqueio(ListaCarta *, int);
Carta *removerIndice(ListaCarta *, int);
Carta *primeiraCartaColecaoI(Galeria *, int);

int quantidadeCartasLista(ListaCarta *);

// COLECAO =======================================
bool inicializarGaleria(Galeria *);
bool inserirColecao(Colecao *, Carta *);
bool inserirNaGaleria(Galeria *, Carta *);

bool galeriaVazia(Galeria *);
bool checarSeJogadorTemUmaCartaDeCadaCor(Galeria *);
void imprimirGaleria(Galeria *);

int quantidadeCartasColecao(Colecao *);
int somaValoresColecao(Galeria *, int i);

int quantidadeCartasColecaoPorIndice(Galeria *, int);

void imprimirContagemPontos(Galeria *);
void imprimirGaleriaComputador(Galeria *);

// MESA =======================================
bool inserirFim(ListaCarta *, Carta *);

// FREE ===========================================
void liberarLista(ListaCarta *);
void liberarColecao(Colecao *);
void liberarGaleria(Galeria *);

#endif // LISTA_H