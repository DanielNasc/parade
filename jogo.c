#include <stdlib.h>
#include <stdio.h>
#include "jogo.h"

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
    int indiceEscolhido;

    // REMOVER DEPOIS P COLOCAR AS DE LUMA ============================

    printf("Escolha uma carta para jogar:\n");
    imprimirLista(jogador->mao);

    do
    {
        scanf("%d", &indiceEscolhido);
        if (indiceEscolhido < 0 || indiceEscolhido >= quantidadeCartasLista(jogador->mao))
            printf("Escolha invalida!\n");
    } while (indiceEscolhido < 0 || indiceEscolhido >= quantidadeCartasLista(jogador->mao));

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

void imprimirGaleriaJogador(Jogador *jogador)
{
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
void jogadaComputador(Computador *computador, Baralho *baralho, ListaCarta *mesa)
{
    // o computador não tem mão, então ele tira a carta do topo do baralho e joga
    Carta *cartaEscolhida = removerTopo(baralho);
    printf("Carta selecionada: %c %d\n", cartaEscolhida->naipe, cartaEscolhida->numero);

    // Remove todas as cartas válidas da mesa e as insere na galeria do computador.
    removerQualquerCartaValida(mesa, computador->galeria, cartaEscolhida);

    // Coloca a carta na mesa.
    inserirFim(mesa, cartaEscolhida);
}

void imprimirGaleriaComputador(Computador *computador)
{
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
    int indiceEscolhido;

    // Pede duas vezes para o jogador escolher uma carta.
    for (int i = 0; i < 2; i++)
    {
        // REMOVER DEPOIS P COLOCAR AS DE LUMA ============================

        printf("Escolha uma carta para jogar:\n");
        imprimirLista(jogador->mao);

        do
        {
            scanf("%d", &indiceEscolhido);
            if (indiceEscolhido < 0 || indiceEscolhido >= quantidadeCartasLista(jogador->mao))
                printf("Escolha invalida!\n");
        } while (indiceEscolhido < 0 || indiceEscolhido >= quantidadeCartasLista(jogador->mao));

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

    // Se o jogador tiver pelo menos uma carta de cada cor, ele perde.
    if (checarSeJogadorTemUmaCartaDeCadaCor(jogador->galeria))
    {
        printf("JOGADOR PERDEU!\n");
        printf("Motivo: Tem pelo menos uma carta de cada cor\n");
        imprimirGaleriaJogador(jogador);
        return true;
    }

    // Se o baralho não estiver vazio, o jogo continua.
    if (tamanhoBaralho(baralho) != 0)
        return false;

    // ultima jogada
    // REMOVER DEPOIS P COLOCAR AS DE LUMA ============================
    printf("O baralho tem 0 cartas, faça a sua última jogada e depois escolha 2 para colocar na sua galeria\n");
    int indiceEscolhido;

    printf("Escolha uma carta para jogar:\n");
    imprimirLista(jogador->mao);

    do
    {
        scanf("%d", &indiceEscolhido);
        if (indiceEscolhido < 0 || indiceEscolhido >= quantidadeCartasLista(jogador->mao))
            printf("Escolha invalida!\n");
    } while (indiceEscolhido < 0 || indiceEscolhido >= quantidadeCartasLista(jogador->mao));

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

    if (vitoria == PERFEITA)
    {
        printf("JOGADOR VENCEU PERFEITAMENTE!\n");
        printf("Motivo: Está com as coleções vazias e tem pelo menos duas cartas com numero 0 na mão\n");
        imprimirLista(jogador->mao);
        imprimirGaleriaJogador(jogador);
        return true;
    }
    else if (vitoria == NORMAL)
    {
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