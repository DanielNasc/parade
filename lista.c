#include <stdlib.h>
#include <stdio.h>
#include "lista.h"
#include "interface.h"

typedef struct listaCarta
{
    int quantidade;
    Carta *primeira, *ultima;
} ListaCarta;

typedef struct colecao
{
    char naipe;
    int somatorioPontos;
    ListaCarta *lista;
} Colecao;

typedef struct galeria
{
    Colecao *colecao[QTD_NAIPES];
} Galeria;

// ======================= FUNÇÕES LISTA =======================

/*
 * Função: criarLista
 * Descrição: Cria uma lista vazia.
 */
ListaCarta *criarLista()
{
    // Aloca memória para a lista.
    ListaCarta *novaLista = (ListaCarta *)malloc(sizeof(ListaCarta));

    // Checa se a lista foi alocada corretamente.
    if (novaLista != NULL)
    {
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
bool inserirInicio(ListaCarta *lista, Carta *novaCarta)
{
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

Carta *primeiraCarta(ListaCarta *lista)
{
    return lista != NULL ? lista->primeira : NULL;
}

Carta *ultimaCarta(ListaCarta *lista)
{
    return lista != NULL ? lista->ultima : NULL;
}

/*
 * Função: inserirFim
 * Parametros: lista - Lista onde a carta será inserida.
 *             novaCarta - Carta a ser inserida.
 * Descrição: Insere uma carta no fim da lista.
 */
bool inserirFim(ListaCarta *lista, Carta *novaCarta)
{
    // Checa se a lista está corretamente alocada.
    if (lista == NULL || novaCarta == NULL)
        return false;

    // Checa se a lista está vazia.
    if (lista->quantidade == 0)
        // Se sim, a nova carta passa a ser a primeira e a última carta da lista.
        lista->primeira = lista->ultima = novaCarta;
    else
    {
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
 * Função: quantidadeCartasLista
 * Parametros: lista - Lista a ser analisada.
 * Descrição: Retorna a quantidade de cartas na lista.
 */
int quantidadeCartasLista(ListaCarta *lista)
{
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
Carta *removerIndice(ListaCarta *lista, int indice)
{
    // Checa se a lista está corretamente alocada e se o índice é válido.
    if (lista == NULL || indice < 0 || indice > lista->quantidade)
        return NULL;

    // Ponteiro auxiliar para a carta a ser removida.
    Carta *aux = lista->ultima;

    // printf("[Buscanado indice %d]\n", indice);
    // printf("...\n");

    // Loop para encontrar a carta que será removida.
    for (int i = 0; i < indice; i++)
    {
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
    else                             // se o anterior for NULL, então o aux é a primeira carta
        lista->primeira = aux->prox; // a primeira carta passa a ser o prox da carta a ser removida.

    if (aux->prox != NULL)
        /*
         * Se a carta a ser removida tiver uma carta posterior,
         * o ponteiro ant dessa carta posterior passa a apontar para o ant da carta a ser removida.
         */
        aux->prox->ant = aux->ant;
    else                          // se o proximo for NULL, então o aux é a ultima carta
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
Carta *primeiraCartaAposBloqueio(ListaCarta *mesa, int quantidadeBloqueados)
{
    // Checa se a mesa está corretamente alocada e se a quantidade de cartas bloqueadas é válida.
    if (mesa == NULL || quantidadeBloqueados < 0 || quantidadeBloqueados >= mesa->quantidade)
        return NULL;

    Carta *aux = mesa->ultima; // indice 0

    // printf("\n[Checando cartas para bloqueio]\n");

    // Loop para encontrar a primeira carta apos o bloqueio.
    for (int i = 0; i < quantidadeBloqueados; i++)
    {
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

    for (int indice = carta->numero; aux != NULL; indice++)
    {
        // Checa se a carta atual é válida.
        if (aux->naipe == carta->naipe || aux->numero <= carta->numero)
        {
            // Se sim, realiza a remoção.

            // Coloca o ponteiro auxiliar para apontar para a carta anterior, para que ele
            // não seja removido da lista.
            aux = aux->ant;

            // Remove a carta da lista.
            Carta *removida = removerIndice(mesa, indice);
            // Insere a carta na galeria.
            inserirNaGaleria(galeria, removida);

            indice--; // decrementa o indice, uma vez que uma carta foi removida.
            continue;
        }

        // O loop itera as cartas da direita para a esquerda.
        aux = aux->ant;
    }

    return true;
}

// ============ FUNÇÕES COLEÇÃO | GALERIA ======================

/*
 * Função: criarColecao
 * Parametros: naipe
 * Descrição: Cria uma coleção com o naipe dado
 */

Colecao *criarColecao(char naipe)
{
    // Checa se o naipe é válido.
    if (naipe < 'A' || naipe > 'A' + QTD_NAIPES)
        return NULL;

    // Aloca memória para a coleção.
    Colecao *novaColecao = (Colecao *)malloc(sizeof(Colecao));

    // Checa se a memória foi alocada.
    if (novaColecao != NULL)
    {
        // Se sim, inicializa a coleção.
        novaColecao->naipe = naipe;        // naipe da coleção
        novaColecao->somatorioPontos = 0;  // somatório dos números das cartas da coleção
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
bool inserirColecao(Colecao *colecao, Carta *novaCarta)
{
    // Checa se as variáveis estão corretamente alocadas.
    if (colecao == NULL || novaCarta == NULL)
        return false;

    // Tenta inserir a carta na lista.
    if (inserirFim(colecao->lista, novaCarta))
    {
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
int somaValoresColecao(Galeria *galeria, int i)
{
    if (galeria == NULL || galeria->colecao[i] == NULL)
        return 0;

    return galeria->colecao[i]->somatorioPontos;
}

Galeria *criarGaleria()
{
    return (Galeria *)malloc(sizeof(Galeria));
}

/*
 * Função: inserirNaGaleria
 * Parametros: galeria - Galeria que será inserida
 *             carta - Carta que será inserida na galeria
 * Descrição: Cria todas as coleções que pertencem à galeria
 */
bool inicializarGaleria(Galeria *galeria)
{
    if (galeria == NULL)
        return false;

    // Loop para criar as coleções.
    for (int i = 0; i < QTD_NAIPES; i++)
    {
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
bool inserirNaGaleria(Galeria *galeria, Carta *novaCarta)
{
    // Checa se as variáveis são válidas.
    if (galeria == NULL || novaCarta == NULL || novaCarta->naipe < 0 + 'A' || novaCarta->naipe > 'A' + QTD_NAIPES)
        return false;

    // Insere a carta na coleção correspondente.
    // novaCarta->naipe - 'A' => converte o naipe para o índice da coleção.
    return inserirColecao(galeria->colecao[novaCarta->naipe - 'A'], novaCarta);
}

// comentada
void imprimirGaleria(Galeria *galeria)
{
    /* Função de Interface
    Imprime toda a galeria/coleção do jogador
    */

    if (galeria == NULL)
        return;

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
    WORD saved_attributes;

    /* Salvar estado atual */
    GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
    saved_attributes = consoleInfo.wAttributes;

    int lin = 0, col = 0;
    // delay de meio segundo
    Sleep(500);

    // for para imprimir as cartas da coleção
    for (int naipe = 0; naipe < 6; naipe++)
    {
        // auxiliar recebe a primeira carta da lista do naipe
        Carta *aux = galeria->colecao[naipe]->lista->primeira;

        while (aux)
        {
            // muda a cor do sistema para a cor da carta
            corDaCarta(aux);
            // box exterior da carta
            box(45 + lin, 12 + col, 48 + lin, 16 + col); // linha = 3, coluna = 4
            // box interior da carta
            box(46 + lin, 13 + col, 47 + lin, 15 + col);
            linhaCol(46 + lin, 14 + col);
            printf("%c", aux->naipe); // imprime número e naipe
            linhaCol(47 + lin, 14 + col);
            if (aux->numero != 10)
                printf("0%d", aux->numero);
            else
                printf("%d", aux->numero);
            SetConsoleTextAttribute(hConsole, saved_attributes);
            // auxiliar aponta para a próxima carta da lista
            aux = aux->prox;
            // incrementa 8 no inteiro das colunas
            col += 8;
        }
        // incrementa 4 no inteiro das linhas após imprimir todas as cartas da lista do naipe
        lin += 4;
        // as colunas zeram
        col = 0;
    }
    // delay de 1 segundo
    Sleep(1000);
    linhaCol(1, 1);
}

/*
 * Função: galeriaVazia
 * Parametros: galeria - Galeria que será analisada
 * Descrição: Retorna true se a galeria estiver vazia e false caso contrário
 */
bool galeriaVazia(Galeria *galeria)
{
    // Se a galeria não existir, retorna true.
    if (galeria == NULL)
        return true;

    // Percorre todas as coleções da galeria checando se estão vazias.
    for (int i = 0; i < QTD_NAIPES; i++)
    {
        // Se a coleção não estiver vazia, retorna false.
        if (galeria->colecao[i]->lista->quantidade > 0)
            return false;
    }

    // Todas as coleções estão vazias, retorna true.
    return true;
}

int quantidadeCartasColecao(Colecao *colecao)
{
    return colecao == NULL ? 0 : quantidadeCartasLista(colecao->lista);
}

int quantidadeCartasColecaoPorIndice(Galeria *galeria, int indice)
{
    return galeria == NULL ? 0 : quantidadeCartasColecao(galeria->colecao[indice]);
}
