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

typedef struct jogador {
    ListaCarta *mao;
    Galeria *galeria;
} Jogador;

typedef struct computador {
    Galeria *galeria;
} Computador;

/*
    * Função: criarCarta
    * Descrição: Cria uma carta com o número e naipe passados como parâmetro.
*/
Carta *criarCarta(int numero, char naipe) {
    Carta *novaCarta = (Carta *) malloc(sizeof(Carta));

    // Se a memória não foi alocada, retorna NULL.
    // Então simplesmente retorna NULL, para o programa não tentar mexer em uma variável que não existe.
    if (novaCarta != NULL) {
        novaCarta->numero = numero;
        novaCarta->naipe = naipe;
        // Inicializa os ponteiros para NULL. Não há nenhuma carta antes ou depois da carta criada.
        novaCarta->prox = novaCarta->ant = NULL; 
    }

    return novaCarta; // Retorna a carta criada.
}

// ======================= FUNÇÕES BARALHO =======================

/*
    * Função: criarBaralho
    * Descrição: Cria um baralho vazio.
*/
Baralho *criarBaralho() {
    Baralho *baralho = (Baralho *) malloc(sizeof(Baralho));

    // Se a memória não foi alocada, retorna NULL.
    // Então simplesmente retorna NULL, para o programa não tentar mexer em uma variável que não existe.

    if (baralho != NULL) {
        baralho->quantidade = 0;
        baralho->topo = NULL; // Como o baralho está vazio, o topo aponta para NULL.
    }

    return baralho; // Retorna o baralho criado.
}

/*
    * Função: inserir
    * Parametros: baralho - Baralho a ser inserido a carta.
    *             novaCarta - Carta a ser inserida no baralho.
    * Descrição: Insere a carta recebida como parâmetro no baralho.
*/
bool inserir(Baralho *baralho, Carta *novaCarta) {
    // Checa se as variáveis estão corretamente alocadas.
    if (
        baralho == NULL
        || novaCarta == NULL
    ) return false;

    /*
        * A proxima carta (aka carta abaixo) da novaCarta será a carta que estava no topo do baralho.
        * Pois a novaCarta será inserida no topo do baralho, tomando o lugar de outra (se existir),
        * ficando acima da carta que estava no topo do baralho.
    */
    novaCarta->prox = baralho->topo;

    /*
        * Se existir uma carta no topo do baralho, então o ponteiro anterior dela (aka carta acima)
        * deve apontar para a novaCarta.
        * Pois como a novaCarta será inserida no topo do baralho, ela deve ficará acima.
    */
    if (baralho->topo != NULL)
        baralho->topo->ant = novaCarta;

    // A novaCarta é o topo do baralho.
    baralho->topo = novaCarta;

    // Incrementa a quantidade de cartas no baralho.
    baralho->quantidade++;

    return true; // Retorna true, pois a carta foi inserida no baralho.
}


/*
    * Função: enfiarCartasNoBaralho
    * Parametros: baralho - Baralho a ser enfiado as cartas.
    * Descrição: Preenche o baralho como todas as cartas requeridas para o jogo.
    * São 66 cartas, com número, variando de 0 a 10, e naipe, variando de A a F.
*/
bool enfiarCartasNoBaralho(Baralho *baralho) {
    // checa se o baralho está corretamente alocado.
    if (baralho == NULL)
        return false;

    /*
        * Realiza dois loops, onde o primeiro, percorre os naipes, e o segundo, percorre os números.
    */
    for (int naipe = 0; naipe < QTD_NAIPES; naipe++) {
        // Para o naipe atual, são adicionadas cartas com números de 0 a 10. 

        for (int numero = 0; numero <= MAIOR_NUMERO_CARTA; numero++) {
            // Cria uma carta com o número e naipe atual.
            Carta *novaCarta = criarCarta(numero, naipe + 'A'); // Soma-se 'A' para que o naipe tenha o valor inteiro correto.
            
            // Se houve algum problema com a alocação de memória, o loop é interrompido.
            if (novaCarta == NULL) 
                return false;

            // Insere a carta no baralho.
            if (!inserir(baralho, novaCarta)) 
                return false;
        }
    }

    return true;
}

/*
    * Função: jogarNoMeio
    * Parametros: baralho - Baralho onde serão realizadas as operações com as cartas
    *             indice - Indice onde a carta que estava no topo será colocada.
    * Descrção: A função pega a carta que estava no topo do baralho, e a coloca
    * no indice recebido como parâmetro.
*/

bool jogarNoMeio(Baralho *baralho, int indice) {
    // Checa se as variáveis são válidas.
    if (baralho == NULL 
        || indice > baralho->quantidade - 1 
        || indice < 0 
    )
        return false;

    // Cria-se duas variáveis auxiliares, uma para percorrer o baralho,
    // e outra para guardar o endereço da carta que será movida.
    Carta *aux = baralho->topo,
          *aux_topo = aux;

    // Percorre o baralho até o indice recebido.
    for (int i = 0; i < indice; i++) {
        aux = aux->prox;
    }

    // Remove a carta que estava no topo e a deixa "isolada"
    baralho->topo = aux_topo->prox;
    // A carta que estava abaixo da carta que estava no topo, passa a ser a carta que estava no topo.
    // Então o ponteiro anterior (aka acima) é NULL.
    baralho->topo->ant = NULL; 

    // Checa se o indice escolhido é o último da lista.
    if (indice == baralho->quantidade - 1) {
        // Se sim, a carta é inserida no final do baralho, como a carta mais abaixo.
        aux->prox = aux_topo;
        // A carta anterior (acima) agora é o aux
        aux_topo->ant = aux;
        // Como é a ultima carta, o ponteiro proximo (abaixo) é NULL.
        aux_topo->prox = NULL;
        return true; 
    }
    
    // Se não, a carta é inserida entre o aux e a carta após ele.

    // A carta é inserida abaixo do aux. Então o ponteiro anterior (aka acima) é o aux.
    aux_topo->ant = aux;
    // E o ponteiro proximo (abaixo) é a carta que estava abaixo do aux.
    aux_topo->prox = aux->prox;

    // Com isso, o ponteiro anterior (aka acima) da carta que estava abaixo do aux,
    // passa a ser a carta movida
    aux->prox->ant = aux_topo;
    // E o ponteiro proximo (abaixo) do aux passa a ser a carta movida.
    aux->prox = aux_topo;

    return true;
}

/*
    * Função: embaralhar
    * Parametros: baralho - Baralho a ser embaralhado.
    * Descrição: Usa um loop com QTD_LOOPS_EMBARALHAR iterações, dentro dele é sorteado um índice aleatório,
    * e a carta do topo do baralho é movida para o índice sorteado.
*/
bool embaralhar(Baralho *baralho) {
    if (baralho == NULL) 
            return false;

    srand( (unsigned) time(NULL)); // Inicializa o gerador de números aleatórios.
    
    for (int i = 0; i < QTD_LOOPS_EMBARALHAR; i++) {
        /*
            * Soteia um índice aleatório, entre 0 e o número de cartas no baralho - 1, ou seja,
            * entre 0 e 65.
            * Depois disso é somado 1 para que o indice 0 não seja sorteado, pois, caso contrário,
            * o carta do topo trocaria de lugar com ela mesma.
        */
        int novoIndice = (random() % (QTD_MAX_CARTAS - 1)) + 1;

        jogarNoMeio(baralho, novoIndice); // Move a carta do topo para o índice sorteado.
    }

    return true;
}

// VAI SER REMOVIDA =======================================================

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

// ==========================================================================

/*
    * Função: tamanhoBaralho
    * Parametros: baralho - Baralho a ser analisado.
    * Descrição: Retorna a quantidade de cartas no baralho.
*/
uint8_t tamanhoBaralho(Baralho *baralho) {
    if (baralho == NULL)
        return 0;

    return baralho->quantidade;
}

/*
    * Função: removerTopo
    * Parametros: baralho - Baralho a ser analisado.
    * Descrição: Remove a carta do topo do baralho e a retorna.
*/
Carta *removerTopo(Baralho *baralho) {
    // Checa se o baralho está corretamente alocado e se existe uma carta no topo.
    if (baralho == NULL || baralho->topo == NULL)
        return NULL;

    // Cria um ponteiro auxiliar para a carta do topo.
    Carta *topoAntigo = baralho->topo;
    // A carta do topo passa a ser a carta abaixo da carta do topo.
    baralho->topo = topoAntigo->prox;
    
    /*
        * Se existir uma carta abaixo da carta do topo antigo, o ponteiro anterior dela passa a
        * apontar para NULL. Já que não existe mais nenhuma carta acima dela,
        * uma vez que o topo antigo foi removido.
    */
    if (baralho->topo != NULL)
        baralho->topo->ant = NULL;
        
    // Isola o topo antigo do baralho. Colocando o ponteiro prox da carta abaixo dele para NULL.
    topoAntigo->prox = NULL;

    // Decrementa a quantidade de cartas no baralho.
    baralho->quantidade--;
    
    // Retorna a carta removida.
    return topoAntigo;
}

/*
    * Função: baralhoVazio
    * Parametros: baralho - Baralho a ser analisado.
    * Descrição: Retorna true se o baralho estiver vazio, false caso contrário.
*/
bool baralhoVazio(Baralho *baralho) {
    if (baralho == NULL)
        return true;

    return baralho->quantidade == 0;
}

// ======================= FUNÇÕES LISTA =======================

/*
    * Função: criarLista
    * Descrição: Cria uma lista vazia.
*/
ListaCarta *criarLista() {
    // Aloca memória para a lista.
    ListaCarta *novaLista = (ListaCarta *) malloc(sizeof(ListaCarta));
    
    // Checa se a lista foi alocada corretamente.
    if (novaLista != NULL) {
        // Se sim, inicializa os ponteiros.
        novaLista->quantidade = 0;
        novaLista->primeira = novaLista->ultima = NULL;
    }

    return novaLista;
}

/*
    * Função: inserirInicio
    * Parametros: lista - Lista onde a carta será inserida.
    *             novaCarta - Carta a ser inserida.
    * Descrição: Insere uma carta no início da lista.
*/
bool inserirInicio(ListaCarta *lista, Carta *novaCarta) {
    // Checa se a lista está corretamente alocada.
    if (lista == NULL || novaCarta == NULL)
        return false;

    /*
        * Como a nova carta será inserida no início da lista,
        * o ponteiro prox dela (aka segunda carta) passa a apontar para a primeira carta da lista.
    */
    novaCarta->prox = lista->primeira;

    /* 
        * Se existir uma carta na lista, o ponteiro ant dela passa a apontar para a nova carta.
        * Uma vez que novaCarta logo será a primeira carta da lista,
    */
    if (lista->primeira != NULL)
        lista->primeira->ant = novaCarta;

    // A nova carta passa a ser a primeira carta da lista.
    lista->primeira = novaCarta;

    // Se a lista estiver vazia, a nova carta passa a ser tamém a última carta da lista.
    if (lista->quantidade == 0) 
        lista->ultima = novaCarta;
        
    // Incrementa a quantidade de cartas na lista.
    lista->quantidade++;

    return true;
}

/*
    * Função: inserirFim
    * Parametros: lista - Lista onde a carta será inserida.
    *             novaCarta - Carta a ser inserida.
    * Descrição: Insere uma carta no fim da lista.
*/
bool inserirFim(ListaCarta *lista, Carta *novaCarta) {
    // Checa se a lista está corretamente alocada.
    if (lista == NULL || novaCarta == NULL)
        return false;
    
    // Checa se a lista está vazia.
    if (lista->quantidade == 0)
        // Se sim, a nova carta passa a ser a primeira e a última carta da lista.
        lista->primeira = lista->ultima = novaCarta;
    else {
        // Se não, faz-se as operações para inserir no fim da lista.

        // O ponteiro prox da última carta passa a apontar para a nova carta.
        lista->ultima->prox = novaCarta;
        // A carta anterior à nova carta é a que estava no fim da lista.
        novaCarta->ant = lista->ultima; 
        // A nova carta passa a ser a última carta da lista.
        lista->ultima = novaCarta;
    }

    // Incrementa a quantidade de cartas na lista.
    lista->quantidade++;

    return true;
}

/*
    * Função: inicializarMao
    * Parametros: baralho - Baralho a ser usado para inicializar a mão.
    *             jogador - Jogador que tem a mão a ser inicializada.
    * Descrição: Inicializa a mão do jogador. Realizando um loop com QTD_LOOPS_PREENCHER_MAO iterações
    * removendo a carta do topo do baralho e inserindo no início da mão do jogador.
*/
bool inicializarMao(Jogador *jogador, Baralho *baralho) {
    // Checa se o baralho está corretamente alocado.
    if (jogador == NULL || baralho == NULL)
        return false;

    // Loop para preencher a mão do jogador.
    for (int i = 0; i < QTD_LOOPS_PREENCHER_MAO; i++)
        // Retira a carta do topo do baralho e insere no início da mão do jogador.
        if (!inserirInicio(jogador->mao, removerTopo(baralho)))
            return false; // Se a inserção falhar, retorna false.

    return true;
}

/*
    * Função: inicializarMesa
    * Parametros: baralho - Baralho a ser usado para inicializar a mesa.
    *             mesa - Mesa a ser inicializada.
    * Descrição: Inicializa a mesa. Realizando um loop com QTD_LOOPS_PREENCHER_MAO iterações
    * removendo a carta do topo do baralho e inserindo no fim da mesa.
*/
bool inicializarMesa(ListaCarta *mesa, Baralho *baralho) {
    // Checa se o baralho e a mesa estão corretamente alocadas, e checa se o baralho possui pelo menos a 
    // quantidade de cartas necessárias para preencher a mesa.
    if (mesa == NULL || baralho == NULL || baralho->quantidade < QTD_LOOPS_PREENCHER_MAO)
        return false;

    // Loop para preencher a mesa.
    for (int i = 0; i < QTD_LOOPS_PREENCHER_MAO; i++)
        // Retira a carta do topo do baralho e insere no fim da mesa.
        if(!inserirFim(mesa, removerTopo(baralho)))
            return false; // Se a inserção falhar, retorna false.

    return true;   
}

/*
    * Função: quantidadeCartasLista
    * Parametros: lista - Lista a ser analisada.
    * Descrição: Retorna a quantidade de cartas na lista.
*/
int quantidadeCartasLista(ListaCarta *lista) {
    // Se a lista não estiver corretamente alocada, retorna 0.
    // Se estiver, retorna a quantidade de cartas na lista.
    return lista != NULL ? lista->quantidade : 0; 
}

/*
    * Função: removerIndice
    * Parametros: lista - Lista onde a carta será removida.
    *             indice - Índice da carta a ser removida.
    * Descrição: Remove a carta que estiver no índice especificado e a retorna.
*/
Carta *removerIndice(ListaCarta *lista, int indice) {
    // Checa se a lista está corretamente alocada e se o índice é válido.
    if (lista == NULL 
        || indice < 0 
        || indice > lista->quantidade)
        return NULL;

    // Ponteiro auxiliar para a carta a ser removida.
    Carta *aux = lista->ultima;

    // printf("[Buscanado indice %d]\n", indice);
    // printf("...\n");

    // Loop para encontrar a carta que será removida.
    for (int i = 0; i < indice; i++) { 
        aux = aux->ant;
    }

    // printf("[Removendo carta]\n");
    // printf("Naipe: %c | numero: %i\n", aux->naipe, aux->numero);

    if (aux->ant != NULL)
        /*
            * Se a carta a ser removida tiver uma carta anterior,
            * o ponteiro prox dessa carta anterior passa a apontar para o prox da carta a ser removida.
        */
        aux->ant->prox = aux->prox;
    else    // se o anterior for NULL, então o aux é a primeira carta
        lista->primeira = aux->prox; // a primeira carta passa a ser o prox da carta a ser removida.

    if (aux->prox != NULL)
        /*
            * Se a carta a ser removida tiver uma carta posterior,
            * o ponteiro ant dessa carta posterior passa a apontar para o ant da carta a ser removida.
        */
        aux->prox->ant = aux->ant;
    else    // se o proximo for NULL, então o aux é a ultima carta
        lista->ultima = aux->ant; // a ultima carta passa a ser o ant da carta a ser removida.

    // Decrementa a quantidade de cartas na lista.
    lista->quantidade--;

    aux->ant = aux->prox = NULL;

    return aux;
}

/*
    * Função: primeiraCartaAposBloqueio
    * Parametros: mesa - Mesa com as cartas
    *             quantidadeBloqueados - Quantidade de cartas bloqueadas
    * Descrição: Retorna a primeira carta apos o bloqueio.
*/
Carta *primeiraCartaAposBloqueio(ListaCarta *mesa, int quantidadeBloqueados) {
    // Checa se a mesa está corretamente alocada e se a quantidade de cartas bloqueadas é válida.
    if (mesa == NULL 
        || quantidadeBloqueados < 0 
        || quantidadeBloqueados >= mesa->quantidade)
        return NULL;
    
    Carta *aux = mesa->ultima; // indice 0

    // printf("\n[Checando cartas para bloqueio]\n");

    // Loop para encontrar a primeira carta apos o bloqueio.
    for (int i = 0; i < quantidadeBloqueados; i++) {
        aux = aux->ant; // O indice conta da direita para a esquerda.
    }

    // printf("[Primeira carta apos bloqueio]\n");
    // printf("Naipe: %c | numero: %i\n\n", aux->naipe, aux->numero);

    return aux;
}

/*
    * Função: removerQualquerCartaValida
    * Parametros: mesa - Mesa com as cartas
    *             galeria - Galeria onde serão colocadas as cartas removidas da mesa.
    *             carta - Carta que será usada para comparação.
    * Descrição: Itera a lista de cartas da mesa, comaprando o naipe (==) e o numero (<=) com a carta dada
    * e remove as que satisfazem essas condições.
*/
bool removerQualquerCartaValida(ListaCarta *mesa, 
                                Galeria *galeria, 
                                Carta *carta)
{
    // Checa se as variáveis estão corretamente alocadas.
    if (mesa == NULL || galeria == NULL || carta == NULL)
        return false;

    // Ponteiro auxiliar para a carta a ser removida.
    // Analisa-se apenas as cartas que estão após o bloqueio.
    Carta *aux = primeiraCartaAposBloqueio(mesa, carta->numero);
    
    if (aux == NULL)
        return true; // bloqueou tudo

    /*
        Retirar todas as cartas que possuem o mesmo naipe ou têm o número igual ou inferior ao da carta dada
        e que não estão bloqueadas
        e as inserir na lista de cartas da galeria
    */

   for (int indice = carta->numero; aux != NULL ; indice++) {
        // Checa se a carta atual é válida.
        if (aux->naipe == carta->naipe || aux->numero <= carta->numero) {
            // Se sim, realiza a remoção.

            // Coloca o ponteiro auxiliar para apontar para a carta anterior, para que ele
            // não seja removido da lista.
            aux = aux->ant;

            // Remove a carta da lista.
            Carta *removida = removerIndice(mesa, indice);
            // Insere a carta na galeria.
            inserirNaGaleria(galeria, removida);

            indice--; //decrementa o indice, uma vez que uma carta foi removida.
            continue;
        }

        // O loop itera as cartas da direita para a esquerda.
        aux = aux->ant; 
    }

    return true;
}

// VAI SER REMOVIDA ==========================================================
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

/*
    * Função: criarColecao
    * Parametros: naipe
    * Descrição: Cria uma coleção com o naipe dado
*/

Colecao *criarColecao(char naipe) {
    // Checa se o naipe é válido.
    if (naipe < 'A' || naipe > 'A' + QTD_NAIPES)
        return NULL;

    // Aloca memória para a coleção.
    Colecao *novaColecao = (Colecao *)malloc(sizeof(Colecao));

    // Checa se a memória foi alocada.
    if (novaColecao != NULL) {
        // Se sim, inicializa a coleção.
        novaColecao->naipe = naipe; // naipe da coleção
        novaColecao->somatorioPontos = 0; // somatório dos números das cartas da coleção
        novaColecao->lista = criarLista(); // lista de cartas da coleção
    }
    return novaColecao;
}

/*
    * Função: inserirColecao
    * Parametros: colecao - Coleção que será inserida
    *             novaCarta - Carta que será inserida na coleção
    * Descrição: Insere a carta na coleção
*/
bool inserirColecao(Colecao *colecao, Carta *novaCarta) {
    // Checa se as variáveis estão corretamente alocadas.
    if (colecao == NULL || novaCarta == NULL)
        return false;

    // Tenta inserir a carta na lista.
    if (inserirFim(colecao->lista, novaCarta)) {
        // Se foi inserida, atualiza o somatório de pontos.
        colecao->somatorioPontos += novaCarta->numero;
        return true;
    }

    // Se não foi inserida, retorna falso.
    return false;
}

/*
    * Função: somaValoresColecao
    * Parametros: colecao - Coleção que será analisada
    * Descrição: Retorna o somatório dos números das cartas da coleção
*/
int somaValoresColecao(Colecao *colecao) {
    if (colecao == NULL)
        return 0;

    return colecao->somatorioPontos;
}

Galeria *criarGaleria() {
    return (Galeria *)malloc(sizeof(Galeria));
}


/*
    * Função: inserirNaGaleria
    * Parametros: galeria - Galeria que será inserida
    *             carta - Carta que será inserida na galeria
    * Descrição: Cria todas as coleções que pertencem à galeria
*/
bool inicializarGaleria(Galeria *galeria) {
    if (galeria == NULL)
        return false;

    // Loop para criar as coleções.
    for (int i = 0; i < QTD_NAIPES; i++) {
        galeria->colecao[i] = criarColecao(i + 'A');
    }

    return true;
}

/*
    * Função: inserirNaGaleria
    * Parametros: galeria - Galeria que será inserida
    *             novaCarta - Carta que será inserida na galeria
    * Descrição: Insere a carta dada na galeria
*/
bool inserirNaGaleria(Galeria *galeria, Carta *novaCarta) {
    // Checa se as variáveis são válidas.
    if (galeria == NULL 
        || novaCarta == NULL
        || novaCarta->naipe < 0 + 'A'
        || novaCarta->naipe > 'A' + QTD_NAIPES)
        return false;

    // Insere a carta na coleção correspondente.
    // novaCarta->naipe - 'A' => converte o naipe para o índice da coleção.
    return inserirColecao(galeria->colecao[novaCarta->naipe - 'A'], novaCarta);
}

// VAI SER REMOVIDA ==========================================================
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
// ===========================================================================

/*
    * Função: galeriaVazia
    * Parametros: galeria - Galeria que será analisada
    * Descrição: Retorna true se a galeria estiver vazia e false caso contrário
*/
bool galeriaVazia(Galeria *galeria) {
    // Se a galeria não existir, retorna true.
    if (galeria == NULL)
        return true;

    // Percorre todas as coleções da galeria checando se estão vazias.
    for (int i = 0; i < QTD_NAIPES; i++) {
        // Se a coleção não estiver vazia, retorna false.
        if (galeria->colecao[i]->lista->quantidade > 0)
            return false;
    }

    // Todas as coleções estão vazias, retorna true.
    return true;
}

// JOGAR ======================================

/*
    * Função: criarJogador
    * Descrição: Cria um jogador e inicializa suas variáveis
*/

Jogador *criarJogador() {
    // Aloca memória para o jogador.
    Jogador *jogador = (Jogador *)malloc(sizeof(Jogador));

    // Checa se a memória foi alocada.
    if (jogador != NULL) {
        // Se sim, inicializa as variáveis.
        jogador->mao = criarLista();
        jogador->galeria = criarGaleria();

        // Se houve algum erro na inicialização, libera a memória que possa ter sido alocada.
        // e retorna NULL.
        if (jogador->mao == NULL || jogador->galeria == NULL) {
            free(jogador->mao);
            free(jogador->galeria);
            free(jogador);
            return NULL;
        }

        // Se não houve erro, inicaliza-se a galeria.
        inicializarGaleria(jogador->galeria);
    }

    return jogador;
}

/*
    * Função: criarComputador
    * Descrição: Cria um computador e inicializa suas variáveis
*/
Computador *criarComputador() {
    // Aloca memória para o computador.
    Computador *computador = (Computador *)malloc(sizeof(Computador));

    // Checa se a memória foi alocada.
    if (computador != NULL) {
        // Se sim, inicializa as variáveis.
        computador->galeria = criarGaleria();

        // Se houve algum erro na inicialização, libera a memória que possa ter sido alocada.
        if (computador->galeria == NULL) {
            free(computador->galeria);
            free(computador);
            return NULL;
        }

        // Se não houve erro, inicaliza-se a galeria.
        inicializarGaleria(computador->galeria);
    }

    return computador;
}

/*
    * Função: jogadaPlayer
    * Parametros: jogador - Jogador que irá jogar
    *             mesa - Mesa em que serão realizadas as operações respectivas
    *             baralho - Baralho de onde será tirada a carta
    * Descrição: Realiza a jogada do jogador. Primeiramente, ele escolhe uma carta da mão.
    * Após isso, analisa-se a mesa e remove todas as cartas válidas e as insere na galeria do jogador
    * Por fim, coloca-se a carta que o jogador tirou na mesa e o mesmo retira outra do topo do baralho.
*/
void jogadaPlayer(Jogador *jogador, ListaCarta *mesa, Baralho *baralho) {
    int indiceEscolhido;

    // REMOVER DEPOIS P COLOCAR AS DE LUMA ============================

    printf("Escolha uma carta para jogar:\n");
    imprimirLista(jogador->mao);
    
    do {
        scanf("%d", &indiceEscolhido);
        if (indiceEscolhido < 0 || indiceEscolhido >= jogador->mao->quantidade)
            printf("Escolha invalida!\n");
    } while (indiceEscolhido < 0 || indiceEscolhido >= jogador->mao->quantidade);

    // ================================================================

    // Pega a carta que o jogador através do índice escolhido.
    Carta *cartaEscolhida = removerIndice(jogador->mao, indiceEscolhido);
    printf("Carta selecionada: %c %d\n", cartaEscolhida->naipe, cartaEscolhida->numero);

    // Remove todas as cartas válidas da mesa e as insere na galeria do jogador.
    removerQualquerCartaValida(mesa, jogador->galeria, cartaEscolhida);

    // Coloca a carta na mesa.
    inserirFim(mesa, cartaEscolhida);

    // Jogador pega a carta do topo do baralho.
    inserirInicio(jogador->mao, removerTopo(baralho));
}

void imprimirGaleriaJogador(Jogador *jogador) {
    if (jogador == NULL)
        return;

    imprimirGaleria(jogador->galeria);
}


/*
    * Função: jogadaComputador
    * Parametros: computador - Computador que irá jogar
    *             mesa - Mesa em que serão realizadas as operações respectivas
    *             baralho - Baralho de onde será tirada a carta
    * Descrição: Realiza a jogada do computador. Primeiramente, ele pega a carta do topo do baralho e joga.
    * Após isso, analisa-se a mesa e remove todas as cartas válidas e as insere na galeria do computador
    * Por fim, coloca-se a carta que o computador tirou na mesa.
*/
void jogadaComputador(Computador *computador, Baralho *baralho, ListaCarta *mesa) {
    // o computador não tem mão, então ele tira a carta do topo do baralho e joga
    Carta *cartaEscolhida = removerTopo(baralho);
    printf("Carta selecionada: %c %d\n", cartaEscolhida->naipe, cartaEscolhida->numero);

    // Remove todas as cartas válidas da mesa e as insere na galeria do computador.
    removerQualquerCartaValida(mesa, computador->galeria, cartaEscolhida);

    // Coloca a carta na mesa.
    inserirFim(mesa, cartaEscolhida);
}

void imprimirGaleriaComputador(Computador *computador) {
    if (computador == NULL)
        return;

    imprimirGaleria(computador->galeria);
}


// FUNCOES VITORIA OU DERROTA ========================================================

/*
    * Função: checarSeJogadorTemUmaCartaDeCadaCor
    * Parametros: galeria - Galeria que será analisada
    * Descrição: Percorre todas as coleções de cartas da galeria e 
    * verifica se o jogador tem pelo menos uma carta de cada cor.
*/
bool checarSeJogadorTemUmaCartaDeCadaCor(Galeria *galeria) {
    // Checa se a galeria é nula.
    if (galeria == NULL)
        return false;

    // Percorre todas as coleções de cartas.
    for (int i = 0; i < QTD_NAIPES; i++) {
        // Se houver uma coleção vazia, retorna false.
        if (galeria->colecao[i]->lista->quantidade == 0)
            return false;
    }

    return true;
}

/*
    * Função: checarVitoriaJogador
    * Parametros: jogador - Jogador que será analisado
    * Descrição: Checa se o jogador venceu a partida, verificando se seus dados
    * satisfazem as condições abaixo:
    
    * Acabar o baralho e o jogador ter 4 cartas
    -> Se sua galeria tiver 0 pontos, ele vence
    -> Além disso, se ele tiver duas cartas com numero 0, ele vence perfeitamente
*/

TipoVitoria checarVitoriaJogador(Jogador *jogador) {
    if (
        jogador == NULL
        || jogador->mao == NULL
        // Se o jogador não tiver 4 cartas na mão, não se pode verificar se ele venceu.
        || jogador->mao->quantidade != 4 
        // Se sua galeria não estiver vazia, já não se satisfazem as condições para vencer.
        || !galeriaVazia(jogador->galeria) 
    )
        return NENHUMA;

    uint8_t quantidadeZeros = 0;
    Carta *aux = jogador->mao->primeira;

    // Percorre todas as cartas da mão.
    while (aux != NULL) {
        if (aux->numero == 0)
            quantidadeZeros++;
        if (quantidadeZeros == 2) // Se o jogador tiver duas cartas com numero 0, ele vence perfeitamente.
            return PERFEITA;
        aux = aux->prox;
    }

    // Se não, vence normalmente.
    return NORMAL;
}


/*
    * Função: colocarDuasCartasGaleria
    * Parametros: jogador - Jogador que será analisado
    * Descrição
*/
void colocarDuasCartasGaleria(Jogador *jogador) {
    int indiceEscolhido;

    // Pede duas vezes para o jogador escolher uma carta.
    for (int i = 0; i < 2; i++) {
        // REMOVER DEPOIS P COLOCAR AS DE LUMA ============================

        printf("Escolha uma carta para jogar:\n");
        imprimirLista(jogador->mao);
        
        do {
            scanf("%d", &indiceEscolhido);
            if (indiceEscolhido < 0 || indiceEscolhido >= jogador->mao->quantidade)
                printf("Escolha invalida!\n");
        } while (indiceEscolhido < 0 || indiceEscolhido >= jogador->mao->quantidade);

        // ================================================================

        // Retira a carta escolhida da mão.
        Carta *cartaEscolhida = removerIndice(jogador->mao, indiceEscolhido);
        printf("Carta selecionada: %c %d\n", cartaEscolhida->naipe, cartaEscolhida->numero);

        // Insere a carta na galeria.
        inserirNaGaleria(jogador->galeria, cartaEscolhida);
    }
}

/*
    * Função: compararPontuacoes
    * Parametro: jogador - Jogador que será analisado
    *            computador - Computador que será analisado
    * Descrição: Compara os resultados do jogador e do computador para calcular
    * a pontuação final do jogador.
    * 
    * Compara-se coleção por coleção, se o jogador tiver uma maior ou igual que a do computador,
    * soma-se a quantidade de cartas à sua pontuação.
    * Caso contrário, soma-se o seu total de pontos na respectiva coleção.
*/
int compararPontuacoes(Jogador *jogador, Computador *computador) {
    if (jogador == NULL || computador == NULL)
        return 0;

    int pontuacaoJogador = 0;

    // Percorre todas as coleções.
    for (int i = 0; i < QTD_NAIPES; i++) {
        // Realiza as devidas comparações e soma os pontos de acordo com o resultado.
        pontuacaoJogador += jogador->galeria->colecao[i]->lista->quantidade >= computador->galeria->colecao[i]->lista->quantidade ?
                            jogador->galeria->colecao[i]->lista->quantidade :
                            jogador->galeria->colecao[i]->somatorioPontos;
    }

    return pontuacaoJogador;
}

/*
    * Função: fimDeJogo
    * Parametros: jogador - Jogador que será analisado
    *             computador - Computador que será analisado
    *             baralho - Baralho que será analisado e, se tiver cartas, será
    *             removida uma do topo,
    *             mesa
    * Descrição: Checa se o jogo acabou, se sim, imprime se o jogador venceu, perdeu ou sua 
    * pontuação final.
*/
bool fimDeJogo(Jogador *jogador, Computador *computador, Baralho *baralho, ListaCarta *mesa) {
    if (jogador == NULL || computador == NULL || baralho == NULL)
        return false;

    // Se o jogador tiver pelo menos uma carta de cada cor, ele perde.
    if (checarSeJogadorTemUmaCartaDeCadaCor(jogador->galeria)) {
        printf("JOGADOR PERDEU!\n");
        printf("Motivo: Tem pelo menos uma carta de cada cor\n");
        imprimirGaleriaJogador(jogador);
        return true;
    }

    // Se o baralho não estiver vazio, o jogo continua.
    if (baralho->quantidade != 0)   
        return false;

    // ultima jogada
    // REMOVER DEPOIS P COLOCAR AS DE LUMA ============================
    printf("O baralho tem 0 cartas, faça a sua última jogada e depois escolha 2 para colocar na sua galeria\n");
    int indiceEscolhido;


    printf("Escolha uma carta para jogar:\n");
    imprimirLista(jogador->mao);
    
    do {
        scanf("%d", &indiceEscolhido);
        if (indiceEscolhido < 0 || indiceEscolhido >= jogador->mao->quantidade)
            printf("Escolha invalida!\n");
    } while (indiceEscolhido < 0 || indiceEscolhido >= jogador->mao->quantidade);

    // ================================================================

    // Retira a carta escolhida da mão.
    Carta *cartaEscolhida = removerIndice(jogador->mao, indiceEscolhido);
    printf("Carta selecionada: %c %d\n", cartaEscolhida->naipe, cartaEscolhida->numero);

    // Remove todas as cartas válidas da mesa e as insere na galeria do jogador.
    removerQualquerCartaValida(mesa, jogador->galeria, cartaEscolhida);

    // Insere a carta que o jogador escoheu no fim da mesa.
    inserirFim(mesa, cartaEscolhida);


    // Checa se o jogaor venceu a partida, e o tipo de vitória.
    TipoVitoria vitoria = checarVitoriaJogador(jogador);

    if (vitoria == PERFEITA) {
        printf("JOGADOR VENCEU PERFEITAMENTE!\n");
        printf("Motivo: Está com as coleções vazias e tem pelo menos duas cartas com numero 0 na mão\n");
        imprimirLista(jogador->mao);
        imprimirGaleriaJogador(jogador);
        return true;
    } else if (vitoria == NORMAL) { 
        printf("JOGADOR VENCEU!\n");
        printf("Motivo: Está com as coleções vazias e tem 4 cartas na mão\n");
        imprimirLista(jogador->mao);
        imprimirGaleriaJogador(jogador);
        return true;
    }

    // Se o jogador não venceu, pede-se para que ele retire duas cartas de sua mão e 
    // coloque-as na sua galeria
    colocarDuasCartasGaleria(jogador);

    // Após isso, apenas se imprime a sua pontuação final.
    printf("A partida acabou, sua pontuação é de %d\n", compararPontuacoes(jogador, computador));

     printf("SUA GALERIA==\n");
    imprimirGaleriaJogador(jogador);

    printf("GALERIA PC\n");
    imprimirGaleriaComputador(computador);
}