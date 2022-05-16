#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "parade.h"

typedef struct carta {
    int numero;
    char naipe;
    struct carta *prox, *ant;
} Carta;

typedef struct baralho {
    uint8_t quantidade;
    Carta *topo;
} Baralho;

typedef struct listaCarta {
    int quantidade;
    Carta *primeira, *ultima;
} ListaCarta;

typedef struct colecao {
    char naipe;
    ListaCarta *lista;
} Colecao;

typedef struct galeria {
    Colecao *colecao[QTD_NAIPES];
} Galeria;

Carta *criarCarta(int numero, char naipe) {
    Carta *novaCarta = (Carta *) malloc(sizeof(Carta));

    if (novaCarta != NULL) {
        novaCarta->numero = numero;
        novaCarta->naipe = naipe;
        novaCarta->prox = novaCarta->ant = NULL;
    }

    return novaCarta;
}

// ======================= FUNÇÕES BARALHO =======================

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
            Carta *novaCarta = criarCarta(numero, naipe + 'A');
            
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


uint8_t tamanhoBaralho(Baralho *baralho) {
    if (baralho == NULL)
        return 0;

    return baralho->quantidade;
}

Carta *removerTopo(Baralho *baralho) {
    if (baralho == NULL || baralho->topo == NULL)
        return NULL;

    Carta *topoAntigo = baralho->topo;
    baralho->topo = topoAntigo->prox;
    
    if (baralho->topo != NULL)
        baralho->topo->ant = NULL;
        
    topoAntigo->prox = NULL;

    baralho->quantidade--;
    
    return topoAntigo;
}

// ======================= FUNÇÕES MÃO =======================

ListaCarta *criarLista() {
    ListaCarta *novaLista = (ListaCarta *) malloc(sizeof(ListaCarta));
    
    if (novaLista != NULL) {
        novaLista->quantidade = 0;
        novaLista->primeira = novaLista->ultima = NULL;
    }

    return novaLista;
}

bool inserirNaMao(ListaCarta *mao, Baralho *baralho) {
    if (mao == NULL || baralho == NULL)
        return false;

    Carta *novaCarta = removerTopo(baralho);

    if (novaCarta != NULL) {
        novaCarta->prox = mao->primeira;

        if (mao->primeira != NULL)
            mao->primeira->ant = novaCarta;

        mao->primeira = novaCarta;

        if (mao->quantidade == 0) 
            mao->ultima = novaCarta;
            
        mao->quantidade++;
    }

    return true;
}

bool preencherMaoInicioJogo(ListaCarta *mao, Baralho *baralho) {
    if (mao == NULL)
        return false;

    for (int i = 0; i < QTD_LOOPS_PREENCHER_MAO; i++)
        if (!inserirNaMao(mao, baralho))
            return false;

    return true;
}

void imprimirMao(ListaCarta *mao) {
    if (mao == NULL)
        return;

    printf("MAO:");

    Carta *aux = mao->primeira;

    while (aux != NULL) {
        printf(" [ %c %d ]", aux->naipe, aux->numero);
        aux = aux->prox;
    }

    printf("\n");
}

Colecao *criarColecao(char naipe) {
    Colecao *novaColecao = (Colecao *)malloc(sizeof(Colecao));

    if (novaColecao != NULL) {
        novaColecao->naipe = naipe;
        novaColecao->lista = criarLista();
    }
    return novaColecao;
}

Galeria *criarGaleria() {
    return (Galeria *)malloc(sizeof(Galeria));
}
bool inicializarGaleria(Galeria *galeria) {
    if (galeria == NULL)
        return false;

    for (int i = 0; i < QTD_NAIPES; i++) {
        galeria->colecao[i] = criarColecao(i + 'A');
    }

    return true;
}
