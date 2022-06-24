#include <stdlib.h>
#include "carta.h"

/*
 * Função: criarCarta
 * Descrição: Cria uma carta com o número e naipe passados como parâmetro.
 */
Carta *criarCarta(int numero, char naipe)
{
    Carta *novaCarta = (Carta *)malloc(sizeof(Carta));

    // Se a memória não foi alocada, retorna NULL.
    // Então simplesmente retorna NULL, para o programa não tentar mexer em uma variável que não existe.
    if (novaCarta != NULL)
    {
        novaCarta->numero = numero;
        novaCarta->naipe = naipe;
        // Inicializa os ponteiros para NULL. Não há nenhuma carta antes ou depois da carta criada.
        novaCarta->prox = novaCarta->ant = NULL;
    }

    return novaCarta; // Retorna a carta criada.
}