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
        novaCarta->prox = novaCarta-> ant = NULL;
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
    if (baralho == NULL || indoce)
}

bool embaralhar(Baralho *baralho) {
    if (baralho == NULL) 
            return false;

    srand( (unsigned) time(NULL));
    
    for (int i = 0; i < QTD_LOOPS_EMBARALHAR; i++) {
        printf("%d\n", random() % QTD_MAX_CARTAS);
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
        printf("\t|\n\tV\n");
        aux = aux->prox;
    }
    printf("NULL\n");
    printf("Quantidade de cartas: %d\n", baralho->quantidade);
    printf("[Fim do Baralho]\n");
}