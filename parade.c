#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "parade.h"

typedef struct carta {
    int numero;
    char naipe;
    struct carta *prox;
    struct carta *ant;
} Carta;

typedef struct baralho {
    int quantidade;
    Carta *topo;
} Baralho;

Carta *criarCarta(int numero, char naipe) {
    Carta *novaCarta = (Carta *) malloc(sizeof(Carta));

    if (novaCarta != NULL) {
        novaCarta->numero = numero;
        novaCarta->naipe = naipe;
        novaCarta->prox = novaCarta->ant = NULL;
    }

    return novaCarta;
    
}

Baralho *criarBaralho() {
    Baralho *baralho = (Baralho *) malloc(sizeof(Baralho));

    if (baralho != NULL) {
        baralho->quantidade = 0;
        baralho->topo = NULL;
    }

    return baralho;
}

bool inserir(Baralho *baralho, Carta *novaCarta) {
    if (
        baralho == NULL
        || novaCarta == NULL
    ) return false;

    novaCarta->prox = baralho->topo;
    if (baralho->topo != NULL)
        baralho->topo->ant = novaCarta;
    baralho->topo = novaCarta;

    baralho->quantidade++;

    return true;
}

bool enfiarCartasNoBaralho(Baralho *baralho) {
    if (baralho == NULL)
        return false;

    for (int naipe = 0; naipe < QTD_NAIPES; naipe++) {
        for (int numero = 0; numero <= MAIOR_NUMERO_CARTA; numero++) {

            Carta *novaCarta = criarCarta(numero, naipe + 65);
            if (novaCarta == NULL) 
                return false;

            if (!inserir(baralho, novaCarta)) 
                return false;
        }
    }

    return true;
}

bool jogarNoMeio(Baralho *baralho, int indice) {
    if (baralho == NULL 
        || indice > baralho->quantidade - 1 
        || indice < 0 
    )
        return false;

    Carta *aux = baralho->topo,
          *aux_topo = aux;

    for (int i = 0; i < indice; i++) {
        aux = aux->prox;
    }

    baralho->topo = aux_topo->prox;
    baralho->topo->ant = NULL;

    if (indice == baralho->quantidade - 1) {
        aux->prox = aux_topo;
        aux_topo->ant = aux;
        aux_topo->prox = NULL;
        return true;
    }
    
    aux_topo->ant = aux;
    aux_topo->prox = aux->prox;

    aux->prox->ant = aux_topo;
    aux->prox = aux_topo;

    return true;
}

bool embaralhar(Baralho *baralho) {
    if (baralho == NULL) 
            return false;

    srand( (unsigned) time(NULL));
    
    for (int i = 0; i < QTD_LOOPS_EMBARALHAR; i++) {
        int novoIndice = (random() % (QTD_MAX_CARTAS - 1)) + 1;

        jogarNoMeio(baralho, novoIndice);
    }

    return true;
}

void imprimirBaralho(Baralho *baralho) {
    if (baralho == NULL) 
        return;

    Carta *aux = baralho->topo;

    printf("[Imprimindo Baralho]\n");
    while (aux != NULL) {
        printf("Naipe: %c | numero: %i\n", aux->naipe, aux->numero);
        aux = aux->prox;
    }
    printf("NULL\n");
    printf("Quantidade de cartas: %d\n", baralho->quantidade);
    printf("[Fim do Baralho]\n");
}