#include <stdlib.h>
#include <stdio.h>
#include "jogo.h"
#include "interface.h"

typedef struct jogador
{
    ListaCarta *mao;
    Galeria *galeria;
} Jogador;

typedef struct computador
{
    Galeria *galeria;
} Computador;

/*
 * Função: inicializarMao
 * Parametros: baralho - Baralho a ser usado para inicializar a mão.
 *             jogador - Jogador que tem a mão a ser inicializada.
 * Descrição: Inicializa a mão do jogador. Realizando um loop com QTD_LOOPS_PREENCHER_MAO iterações
 * removendo a carta do topo do baralho e inserindo no início da mão do jogador.
 */
bool inicializarMao(Jogador *jogador, Baralho *baralho)
{
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
bool inicializarMesa(ListaCarta *mesa, Baralho *baralho)
{
    // Checa se o baralho e a mesa estão corretamente alocadas, e checa se o baralho possui pelo menos a
    // quantidade de cartas necessárias para preencher a mesa.
    if (mesa == NULL || baralho == NULL || tamanhoBaralho(baralho) < QTD_LOOPS_PREENCHER_MAO)
        return false;

    // Loop para preencher a mesa.
    for (int i = 0; i < QTD_LOOPS_PREENCHER_MAO; i++)
        // Retira a carta do topo do baralho e insere no fim da mesa.
        if (!inserirFim(mesa, removerTopo(baralho)))
            return false; // Se a inserção falhar, retorna false.

    return true;
}

// JOGAR ======================================

/*
 * Função: criarJogador
 * Descrição: Cria um jogador e inicializa suas variáveis
 */

Jogador *criarJogador()
{
    // Aloca memória para o jogador.
    Jogador *jogador = (Jogador *)malloc(sizeof(Jogador));

    // Checa se a memória foi alocada.
    if (jogador != NULL)
    {
        // Se sim, inicializa as variáveis.
        jogador->mao = criarLista();
        jogador->galeria = criarGaleria();

        // Se houve algum erro na inicialização, libera a memória que possa ter sido alocada.
        // e retorna NULL.
        if (jogador->mao == NULL || jogador->galeria == NULL)
        {
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
Computador *criarComputador()
{
    // Aloca memória para o computador.
    Computador *computador = (Computador *)malloc(sizeof(Computador));

    // Checa se a memória foi alocada.
    if (computador != NULL)
    {
        // Se sim, inicializa as variáveis.
        computador->galeria = criarGaleria();

        // Se houve algum erro na inicialização, libera a memória que possa ter sido alocada.
        if (computador->galeria == NULL)
        {
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
void jogadaPlayer(Jogador *jogador, ListaCarta *mesa, Baralho *baralho)
{
    int quantidadeAnterior = quantidadeCartasLista(mesa);
    Carta *cartaEscolhida = removerIndice(jogador->mao, escolhaCarta(jogador->mao, 4));
    imprimirCartaEscolhida(cartaEscolhida, 0);
    removerQualquerCartaValida(mesa, jogador->galeria, cartaEscolhida);

    if (quantidadeAnterior != quantidadeCartasLista(mesa))
    {
        linhaCol(72, 3);
        Sleep(1000);
        imprimirGaleria(jogador->galeria);
        box(2, 5, 29, 90);
    }

    inserirFim(mesa, cartaEscolhida);
    inserirInicio(jogador->mao, removerTopo(baralho));

    imprimirBaralho(baralho);
    imprimirMao(jogador->mao);

    imprimirControles(41, 30);
    imprimirMesa(mesa);
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
void jogadaComputador(Computador *computador, Baralho *baralho, ListaCarta *mesa)
{
    /// o computador não tem mão, então ele tira a carta do topo do baralho e joga
    int quantidadeAnterior = quantidadeCartasLista(mesa), pensando = (rand() % 3000) + 500;
    Carta *cartaEscolhida = removerTopo(baralho);
    Sleep(pensando);
    imprimirCartaEscolhida(cartaEscolhida, 26);
    removerQualquerCartaValida(mesa, computador->galeria, cartaEscolhida);
    if (quantidadeAnterior != quantidadeCartasLista(mesa))
    {
        box(2, 5, 29, 90);
    }
    inserirFim(mesa, cartaEscolhida);

    imprimirBaralho(baralho);
    imprimirMesa(mesa);
}

// FUNCOES VITORIA OU DERROTA ========================================================

/*
 * Função: checarSeJogadorTemUmaCartaDeCadaCor
 * Parametros: galeria - Galeria que será analisada
 * Descrição: Percorre todas as coleções de cartas da galeria e
 * verifica se o jogador tem pelo menos uma carta de cada cor.
 */
bool checarSeJogadorTemUmaCartaDeCadaCor(Galeria *galeria)
{
    // Checa se a galeria é nula.
    if (galeria == NULL)
        return false;

    // Percorre todas as coleções de cartas.
    for (int i = 0; i < QTD_NAIPES; i++)
    {
        // Se houver uma coleção vazia, retorna false.
        if (quantidadeCartasColecaoPorIndice(galeria, i) == 0)
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

TipoVitoria checarVitoriaJogador(Jogador *jogador)
{
    if (
        jogador == NULL || jogador->mao == NULL
        // Se o jogador não tiver 4 cartas na mão, não se pode verificar se ele venceu.
        || quantidadeCartasLista(jogador->mao) != 4
        // Se sua galeria não estiver vazia, já não se satisfazem as condições para vencer.
        || !galeriaVazia(jogador->galeria))
        return NENHUMA;

    uint8_t quantidadeZeros = 0;
    Carta *aux = primeiraCarta(jogador->mao);

    // Percorre todas as cartas da mão.
    while (aux != NULL)
    {
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
void colocarDuasCartasGaleria(Jogador *jogador)
{
    Carta *cartaEscolhida;
    for (int i = 0; i < 2; i++)
    {
        cartaEscolhida = removerIndice(jogador->mao, escolhaCarta(jogador->mao, 3 - i));
        inserirNaGaleria(jogador->galeria, cartaEscolhida);
        linhaCol(72, 3);
        Sleep(1000);
        imprimirGaleria(jogador->galeria);
        imprimirMao(jogador->mao);
        imprimirControles(41, 30);
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
int compararPontuacoes(Jogador *jogador, Computador *computador)
{
    if (jogador == NULL || computador == NULL)
        return 0;

    int pontuacaoJogador = 0;

    // Percorre todas as coleções.
    for (int i = 0; i < QTD_NAIPES; i++)
    {
        int quantidadeJogador = quantidadeCartasColecaoPorIndice(jogador->galeria, i);

        // Realiza as devidas comparações e soma os pontos de acordo com o resultado.
        pontuacaoJogador += quantidadeJogador >= quantidadeCartasColecaoPorIndice(computador->galeria, i) ? quantidadeJogador
                                                                                                          : somaValoresColecao(jogador->galeria, i);
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
bool fimDeJogo(Jogador *jogador, Computador *computador, Baralho *baralho, ListaCarta *mesa)
{
    if (jogador == NULL || computador == NULL || baralho == NULL)
        return false;

    if (checarSeJogadorTemUmaCartaDeCadaCor(jogador->galeria))
    {
        derrota();
        return true;
    }

    if (tamanhoBaralho(baralho) != 0)
        return false;

    // ultima jogada
    int quantidadeAnterior = quantidadeCartasLista(mesa);
    Carta *cartaEscolhida = removerIndice(jogador->mao, escolhaCarta(jogador->mao, 4));
    removerQualquerCartaValida(mesa, jogador->galeria, cartaEscolhida);
    inserirFim(mesa, cartaEscolhida);

    if (quantidadeAnterior != quantidadeCartasLista(mesa))
    {
        linhaCol(72, 3);
        Sleep(1000);
        imprimirGaleria(jogador->galeria);
        box(2, 5, 29, 90);
    }
    imprimirMao(jogador->mao);
    imprimirControles(41, 30);
    imprimirMesa(mesa);

    chamarPlacar(computador, jogador, checarVitoriaJogador(jogador));

    return true;
}

void imprimirMaoJogador(Jogador *jogador)
{
    imprimirMao(jogador->mao);
}

void imprimirGaleriaJogador(Jogador *jogador)
{
    imprimirGaleria(jogador->galeria);
}

void partida()
{
    Baralho *baralho = criarBaralho();
    enfiarCartasNoBaralho(baralho);
    embaralhar(baralho);

    ListaCarta *mesa = criarLista();

    inicializarMesa(mesa, baralho);

    Jogador *jogador = criarJogador();
    Computador *computador = criarComputador();

    inicializarMao(jogador, baralho);

    // IMPRESSÕES //

    imprimirBaralho(baralho);
    imprimirMesa(mesa);
    imprimirMaoJogador(jogador);
    imprimirControles(41, 30);
    imprimirJogador();
    imprimirComputer();
    imprimirNaipesColecao();
    imprimirGaleriaJogador(jogador);

    while (1)
    {
        corDaVez(1);
        jogadaPlayer(jogador, mesa, baralho);

        if (fimDeJogo(jogador, computador, baralho, mesa))
            break;
        corDaVez(0);
        jogadaComputador(computador, baralho, mesa);

        if (fimDeJogo(jogador, computador, baralho, mesa))
            break;
    }
}