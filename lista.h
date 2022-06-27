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

int quantidadeCartasLista(ListaCarta *);

// COLECAO =======================================
bool inicializarGaleria(Galeria *);
bool inserirColecao(Colecao *, Carta *);
bool inserirNaGaleria(Galeria *, Carta *);

bool galeriaVazia(Galeria *);

void imprimirGaleria(Galeria *);

int quantidadeCartasColecao(Colecao *);
int somaValoresColecao(Galeria *galeria, int i);

int quantidadeCartasColecaoPorIndice(Galeria *, int);

// MESA =======================================
bool inserirFim(ListaCarta *, Carta *);

#endif // LISTA_H