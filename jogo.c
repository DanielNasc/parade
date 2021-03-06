#include <stdlib.h>
#include <stdio.h>
#include "jogo.h"
#include "interface.h"
#include "caracters.h"

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
int jogadaPlayer(Jogador *jogador, ListaCarta *mesa, Baralho *baralho)
{
    if (jogador == NULL || mesa == NULL || baralho == NULL)
        return 0;

    int quantidadeAnterior = quantidadeCartasLista(mesa);

    int indiceEscolhido = escolhaCarta(jogador->mao, 4);

    if (indiceEscolhido == SAIR_PARTIDA)
        return SAIR_PARTIDA;

    Carta *cartaEscolhida = removerIndice(jogador->mao, indiceEscolhido);
    imprimirCartaEscolhida(cartaEscolhida, 0);
    removerQualquerCartaValida(mesa, jogador->galeria, cartaEscolhida);

    if (quantidadeAnterior != quantidadeCartasLista(mesa))
    {
        linhaCol(77, 23);
        Sleep(1000);
        imprimirGaleria(jogador->galeria);
        imprimirBoxMesa();
    }

    inserirFim(mesa, cartaEscolhida);
    inserirInicio(jogador->mao, removerTopo(baralho));

    imprimirBaralho(baralho);
    imprimirMao(jogador->mao);

    imprimirControles(46, 42);
    imprimirMesa(mesa);

    return 1;
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
    imprimirCartaEscolhida(cartaEscolhida, 32);
    removerQualquerCartaValida(mesa, computador->galeria, cartaEscolhida);
    if (quantidadeAnterior != quantidadeCartasLista(mesa))
    {
        imprimirBoxMesa();
    }
    inserirFim(mesa, cartaEscolhida);

    imprimirBaralho(baralho);
    imprimirMesa(mesa);
}

// FUNCOES VITORIA OU DERROTA ========================================================

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
int colocarDuasCartasGaleria(Jogador *jogador)
{
    if (jogador == NULL || jogador->mao == NULL)
        return 0;

    Carta *cartaEscolhida;
    imprimirDuasCartas();
    for (int i = 0; i < 2; i++)
    {
        int indice = escolhaCarta(jogador->mao, 3 - i);

        if (indice == SAIR_PARTIDA)
            return SAIR_PARTIDA;

        if (checarSeJogadorTemUmaCartaDeCadaCor(jogador->galeria))
            return PERDEU;

        cartaEscolhida = removerIndice(jogador->mao, indice);
        inserirNaGaleria(jogador->galeria, cartaEscolhida);
        linhaCol(77, 23);
        Sleep(1000);
        imprimirGaleria(jogador->galeria);
        imprimirMao(jogador->mao);
        imprimirControles(46, 50);
    }

    return 1;
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

    int pontuacaoJogador = 0, pontuacaoAnterior = 0;
    system("cls");
    chamarContagem(jogador);
    chamarGaleriaComputador(computador);

    // Percorre todas as coleções.
    corTexto(YELLOW, _BLACK);
    for (int i = 0; i < QTD_NAIPES; i++)
    {
        int quantidadeJogador = quantidadeCartasColecaoPorIndice(jogador->galeria, i);

        // Realiza as devidas comparações e soma os pontos de acordo com o resultado.
        pontuacaoJogador += quantidadeJogador >= quantidadeCartasColecaoPorIndice(computador->galeria, i)
                                ? quantidadeJogador
                                : somaValoresColecao(jogador->galeria, i);

        imprimirGanhoDePontos(i, pontuacaoJogador - pontuacaoAnterior);
        pontuacaoAnterior = pontuacaoJogador;
    }

    resetarAtributos();
    imprimirGanhoDePontos(6, pontuacaoJogador);
    resetarAtributos();
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
        Sleep(2000);
        return true;
    }

    if (tamanhoBaralho(baralho) != 0)
        return false;

    // ultima jogada

    imprimirUltimaCarta();
    int quantidadeAnterior = quantidadeCartasLista(mesa);

    int indice = escolhaCarta(jogador->mao, 4);

    if (indice == SAIR_PARTIDA)
        return true;

    Carta *cartaEscolhida = removerIndice(jogador->mao, indice);
    removerQualquerCartaValida(mesa, jogador->galeria, cartaEscolhida);

    if (checarSeJogadorTemUmaCartaDeCadaCor(jogador->galeria))
    {
        derrota();
        Sleep(2000);
        return true;
    }

    if (quantidadeAnterior != quantidadeCartasLista(mesa))
    {
        linhaCol(77, 23);
        Sleep(1000);
        imprimirGaleria(jogador->galeria);
        imprimirBoxMesa(); // reseta a mesa
    }
    inserirFim(mesa, cartaEscolhida);
    imprimirMao(jogador->mao);
    imprimirControles(46, 42);
    imprimirMesa(mesa);

    if (chamarPlacar(computador, jogador, checarVitoriaJogador(jogador)) == PERDEU)
    {
        derrota();
        Sleep(2000);
        return true;
    }

    return true;
}

// comentada
int chamarPlacar(Computador *computador, Jogador *jogador, int tipoVitoria)
{
    /*Função de chamada de funções:
    Essa função é basicamente para chamar outras funções, que seriam as
    funções de interface para telas de fim de jogo.
    Como parâmetros temos:
        *o Computador e o Jogador, para conseguirmos chamar a função
        colocarDuasCartasGaleria e compararPontuacoes.
        *um inteiro [0,1 ou 2] que passaria para a função o tipo de fim de jogo:
            0 -> Fim de jogo resultando em uma pontuação.
            1 -> Vitória por coleção vazia quando o baralho é zerado.
            2 -> Vitória perfeita quando o baralho é zerado com a coleção vazia
            e na mão do jogador existem pelo menos duas cartas de valor 0, independente
            do naipe. */

    // checamos se o jogador e o computador são nulos
    if (jogador == NULL || computador == NULL)
        return 0;

    char save[15];
    int pontos = 0, tecla = 0;

    // criei um switch para chamarmos as funções de acordo com o inteiro dado como parâmetro
    switch (tipoVitoria)
    {
    case 0:;
        // chama a função para colocar as últimas duas cartas da mão do jogador em sua coleção

        int duasCartasColocadas = colocarDuasCartasGaleria(jogador);
        if (duasCartasColocadas == SAIR_PARTIDA)
            return SAIR_PARTIDA;
        else if (duasCartasColocadas == PERDEU)
            return PERDEU;

        pontos = compararPontuacoes(jogador, computador);

        do
        {
            tecla = getch();
        } while (tecla != ENTER);
        system("cls");
        linhaCol(1, 1);
        // chama a função de interface para imprimir a tela de vitoria por pontuação
        nomeDoSave(save);

        saveScore(pontos, save, tipoVitoria);
        vitoriaPontuacao(pontos);
        break;
    case 1:
        // chama a função de interface para imprimir a tela de vitoria normal, por colecao vazia
        nomeDoSave(save);

        saveScore(PONTOS_VITORIA_NORMAL, save, tipoVitoria);
        vitoriaNormal();
        break;
    case 2:
        // chama a função de interface para imprimir a tela de vitoria perfeita
        nomeDoSave(save);

        saveScore(PONTOS_VITORIA_PERFEITA, save, tipoVitoria);
        vitoriaPerfeita();
        break;
    }
    Sleep(2500);
    return 1;
}

void imprimirMaoJogador(Jogador *jogador)
{
    imprimirMao(jogador->mao);
}

void imprimirGaleriaJogador(Jogador *jogador)
{
    imprimirGaleria(jogador->galeria);
}

void chamarContagem(Jogador *jogador)
{
    imprimirContagemPontos(jogador->galeria);
}

void chamarGaleriaComputador(Computador *computador)
{
    imprimirGaleriaComputador(computador->galeria);
}

void liberarjogador(Jogador *jogador)
{
    liberarLista(jogador->mao);
    liberarGaleria(jogador->galeria);
    free(jogador);
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
    imprimirControles(46, 42);
    imprimirJogador();
    imprimirComputer();
    imprimirNaipesColecao();
    imprimirGaleriaJogador(jogador);

    while (1)
    {
        corDaVez(1);

        if (jogadaPlayer(jogador, mesa, baralho) == SAIR_PARTIDA)
            break;

        if (fimDeJogo(jogador, computador, baralho, mesa))
            break;
        corDaVez(0);
        jogadaComputador(computador, baralho, mesa);

        if (fimDeJogo(jogador, computador, baralho, mesa))
            break;
    }

    liberarBaralho(baralho);
    liberarLista(mesa);
    liberarjogador(jogador);
}