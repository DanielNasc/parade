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
    int somatorioPontos;
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

// ======================= FUNÇÕES LISTA =======================

ListaCarta *criarLista() {
    ListaCarta *novaLista = (ListaCarta *) malloc(sizeof(ListaCarta));
    
    if (novaLista != NULL) {
        novaLista->quantidade = 0;
        novaLista->primeira = novaLista->ultima = NULL;
    }

    return novaLista;
}

bool inserirInicio(ListaCarta *lista, Carta *novaCarta) {
    if (lista == NULL || novaCarta == NULL)
        return false;

    novaCarta->prox = lista->primeira;

    if (lista->primeira != NULL)
        lista->primeira->ant = novaCarta;

    lista->primeira = novaCarta;

    if (lista->quantidade == 0) 
        lista->ultima = novaCarta;
        
    lista->quantidade++;

    return true;
}

bool inserirFim(ListaCarta *lista, Carta *novaCarta) {
    if (lista == NULL || novaCarta == NULL)
        return false;
    
    if (lista->quantidade == 0)
        lista->primeira = lista->ultima = novaCarta;
    else {
        lista->ultima->prox = novaCarta;
        novaCarta->ant = lista->ultima;
        lista->ultima = novaCarta;
    }

    lista->quantidade++;
    return true;
}


bool inicializarMao(ListaCarta *mao, Baralho *baralho) {
    if (mao == NULL)
        return false;

    for (int i = 0; i < QTD_LOOPS_PREENCHER_MAO; i++)
        if (!inserirInicio(mao, removerTopo(baralho)))
            return false;

    return true;
}


bool inicializarMesa(ListaCarta *mesa, Baralho *baralho) {
    if (mesa == NULL || baralho == NULL || baralho->quantidade == 0)
        return false;

    for (int i = 0; i < QTD_LOOPS_PREENCHER_MAO; i++)
        if(!inserirFim(mesa, removerTopo(baralho)))
            return false;

    return true;   
}

int quantidadeCartasLista(ListaCarta *lista) {
    return lista != NULL ? lista->quantidade : 0;
}

Carta *removerIndice(ListaCarta *lista, int indice) {
    if (lista == NULL 
        || indice < 0 
        || indice > lista->quantidade)
        return NULL;

    Carta *aux = lista->ultima;

    printf("[Buscanado indice %d]\n", indice);
    printf("...\n");
    for (int i = 0; i < indice; i++) { 
        aux = aux->ant;
    }

    printf("[Removendo carta]\n");
    printf("Naipe: %c | numero: %i\n", aux->naipe, aux->numero);

    if (aux->ant != NULL)
        aux->ant->prox = aux->prox;
    else    // se o anterior for NULL, então o aux é a primeira carta
        lista->primeira = aux->prox;

    if (aux->prox != NULL)
        aux->prox->ant = aux->ant;
    else    // se o proximo for NULL, então o aux é a ultima carta
        lista->ultima = aux->ant;

    lista->quantidade--;

    aux->ant = aux->prox = NULL;

    return aux;
}

Carta *primeiraCartaAposBloqueio(ListaCarta *mesa, int quantidadeBloqueados) {
    if (mesa == NULL 
        || quantidadeBloqueados < 0 
        || quantidadeBloqueados >= mesa->quantidade)
        return NULL;
    
    Carta *aux = mesa->ultima; // indice 0

    // printf("\n[Checando cartas para bloqueio]\n");
    for (int i = 0; i < quantidadeBloqueados; i++) {
        // printf("Naipe: %c | numero: %i\n", aux->naipe, aux->numero);
        aux = aux->ant;
    }

    // printf("[Primeira carta apos bloqueio]\n");
    // printf("Naipe: %c | numero: %i\n\n", aux->naipe, aux->numero);

    return aux;
}

// Itera a lista de cartas da mesa, comaprando o naipe (==) e o numero (<=) com a carta dada
bool removerQualquerCartaValida(ListaCarta *mesa, 
                                Galeria *galeria, 
                                Carta *carta)
{
    if (mesa == NULL || galeria == NULL || carta == NULL)
        return false;

    Carta *aux = primeiraCartaAposBloqueio(mesa, carta->numero);
    
    if (aux == NULL)
        return true; // bloqueou tudo

    /*
        Retirar todas as cartas que possuem o mesmo naipe ou têm o número igual ou inferior ao da carta dada
        e que não estão bloqueadas
        e as inserir na lista de cartas da galeria
    */

   printf("Loop iniciando\n");
   for (int indice = carta->numero; aux != NULL ; indice++) {
       printf("Carta: %c | %i | indice: %i\n", aux->naipe, aux->numero, indice);
        if (aux->naipe == carta->naipe || aux->numero <= carta->numero) {
            printf("Removendo carta %c%d com indice %i\n", aux->naipe, aux->numero, indice);
            aux = aux->ant;
            Carta *removida = removerIndice(mesa, indice);
            inserirNaGaleria(galeria, removida);
            indice--;   
            continue;
        }
        aux = aux->ant;
    }
    printf("Loop terminado\n");

    return true;
}

void imprimirLista(ListaCarta *lista) {
    if (lista == NULL)
        return;

    printf("Lista de Cartas:");

    Carta *aux = lista->primeira;

    while (aux != NULL) {
        printf(" [ %c %d ]", aux->naipe, aux->numero);
        aux = aux->prox;
    }

    printf(" | Quantidade: %d\n", lista->quantidade);
}

// ============ FUNÇÕES COLEÇÃO | GALERIA ======================

Colecao *criarColecao(char naipe) {
    Colecao *novaColecao = (Colecao *)malloc(sizeof(Colecao));

    if (novaColecao != NULL) {
        novaColecao->naipe = naipe;
        novaColecao->somatorioPontos = 0;
        novaColecao->lista = criarLista();
    }
    return novaColecao;
}

bool inserirColecao(Colecao *colecao, Carta *novaCarta) {
    if (colecao == NULL) 
        return false;

    colecao->somatorioPontos += novaCarta->numero;
    return inserirFim(colecao->lista, novaCarta);
}

int somaValoresColecao(Colecao *colecao) {
    if (colecao == NULL)
        return 0;

    return colecao->somatorioPontos;
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

bool inserirNaGaleria(Galeria *galeria, Carta *novaCarta) {
    if (galeria == NULL 
        || novaCarta == NULL
        || novaCarta->naipe < 0 + 'A'
        || novaCarta->naipe > 'F')
        return false;

    return inserirColecao(galeria->colecao[novaCarta->naipe - 'A'], novaCarta);
}

void imprimirGaleria(Galeria *galeria) {
    if (galeria == NULL)
        return;

    printf("Imprimindo galeria:\n");

    for (int i = 0; i < QTD_NAIPES; i++) {
        Colecao *current = galeria->colecao[i];
        printf("COLECAO DE NAIPE %c : ", current->naipe);
        imprimirLista(current->lista);
        printf("\nSomatorio: %d\n", current->somatorioPontos);
    }
}