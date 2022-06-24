#ifndef PILHA_H
#define PILHA_H

#include <inttypes.h>
#include <stdbool.h>
#include "carta.h"

typedef struct baralho Baralho;

#define QTD_LOOPS_EMBARALHAR 200

Baralho *criarBaralho();

bool inserir(Baralho *, Carta *);
bool enfiarCartasNoBaralho(Baralho *);
bool embaralhar(Baralho *);
bool jogarNoMeio(Baralho *, int);

uint8_t tamanhoBaralho(Baralho *);

void imprimirBaralho(Baralho *);

Carta *removerTopo(Baralho *);

#endif // PILHA_H