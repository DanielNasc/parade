#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "pilha.h"
#include "os.h"

typedef struct baralho
{
    uint8_t quantidade;
    Carta *topo;
} Baralho;

// ======================= FUNÇÕES BARALHO =======================

/*
 * Função: criarBaralho
 * Descrição: Cria um baralho vazio.
 */
Baralho *criarBaralho()
{
    Baralho *baralho = (Baralho *)malloc(sizeof(Baralho));

    // Se a memória não foi alocada, retorna NULL.
    // Então simplesmente retorna NULL, para o programa não tentar mexer em uma variável que não existe.

    if (baralho != NULL)
    {
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
bool inserir(Baralho *baralho, Carta *novaCarta)
{
    // Checa se as variáveis estão corretamente alocadas.
    if (
        baralho == NULL || novaCarta == NULL)
        return false;

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
bool enfiarCartasNoBaralho(Baralho *baralho)
{
    // checa se o baralho está corretamente alocado.
    if (baralho == NULL)
        return false;

    /*
     * Realiza dois loops, onde o primeiro, percorre os naipes, e o segundo, percorre os números.
     */
    for (int naipe = 0; naipe < QTD_NAIPES; naipe++)
    {
        // Para o naipe atual, são adicionadas cartas com números de 0 a 10.

        for (int numero = 0; numero <= MAIOR_NUMERO_CARTA; numero++)
        {
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

bool jogarNoMeio(Baralho *baralho, int indice)
{
    // Checa se as variáveis são válidas.
    if (baralho == NULL || indice > baralho->quantidade - 1 || indice < 0)
        return false;

    // Cria-se duas variáveis auxiliares, uma para percorrer o baralho,
    // e outra para guardar o endereço da carta que será movida.
    Carta *aux = baralho->topo,
          *aux_topo = aux;

    // Percorre o baralho até o indice recebido.
    for (int i = 0; i < indice; i++)
    {
        aux = aux->prox;
    }

    // Remove a carta que estava no topo e a deixa "isolada"
    baralho->topo = aux_topo->prox;
    // A carta que estava abaixo da carta que estava no topo, passa a ser a carta que estava no topo.
    // Então o ponteiro anterior (aka acima) é NULL.
    baralho->topo->ant = NULL;

    // Checa se o indice escolhido é o último da lista.
    if (indice == baralho->quantidade - 1)
    {
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
bool embaralhar(Baralho *baralho)
{
    if (baralho == NULL)
        return false;

    srand((unsigned)time(NULL)); // Inicializa o gerador de números aleatórios.

    for (int i = 0; i < QTD_LOOPS_EMBARALHAR; i++)
    {
        /*
         * Soteia um índice aleatório, entre 0 e o número de cartas no baralho - 1, ou seja,
         * entre 0 e 65.
         * Depois disso é somado 1 para que o indice 0 não seja sorteado, pois, caso contrário,
         * o carta do topo trocaria de lugar com ela mesma.
         */

        int randomNumer = OS_NAME == "Windows" ? rand() : random();
        int novoIndice = (randomNumer % (QTD_MAX_CARTAS - 1)) + 1;

        jogarNoMeio(baralho, novoIndice); // Move a carta do topo para o índice sorteado.
    }

    return true;
}

/*
 * Função: tamanhoBaralho
 * Parametros: baralho - Baralho a ser analisado.
 * Descrição: Retorna a quantidade de cartas no baralho.
 */
uint8_t tamanhoBaralho(Baralho *baralho)
{
    if (baralho == NULL)
        return 0;

    return baralho->quantidade;
}

/*
 * Função: removerTopo
 * Parametros: baralho - Baralho a ser analisado.
 * Descrição: Remove a carta do topo do baralho e a retorna.
 */
Carta *removerTopo(Baralho *baralho)
{
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
bool baralhoVazio(Baralho *baralho)
{
    if (baralho == NULL)
        return true;

    return baralho->quantidade == 0;
}

void liberarBaralho(Baralho *baralho)
{
    if (baralho == NULL)
        return;

    Carta *carta = baralho->topo;
    while (carta != NULL)
    {
        Carta *aux = carta;
        carta = carta->prox;
        free(aux);
    }
    free(baralho);
}