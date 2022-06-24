#ifndef CARTA_H
#define CARTA_H

typedef struct carta
{
    int numero;
    char naipe;
    struct carta *prox, *ant;
} Carta;

#define QTD_MAX_CARTAS 66
#define QTD_NAIPES 6
#define MAIOR_NUMERO_CARTA 10

Carta *criarCarta(int, char);

#endif // CARTA_H