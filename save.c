#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "save.h"
#include "interface.h"

void inicializarArquivoFullscreen()
{
    // checa se o arquivo fullscreen.bin existe
    // se sim, não faz nada

    FILE *arq = fopen(ARQ_FULLSCREEN_OPTION, "r");
    if (arq != NULL)
    {
        fclose(arq);
        return;
    }

    // se não existir, cria o arquivo
    arq = fopen(ARQ_FULLSCREEN_OPTION, "w");

    // a opção sera iniciada como true
    fprintf(arq, "true");
    fclose(arq);
}

bool pegarFullscreen()
{
    // checa se o arquivo fullscreen.bin existe
    FILE *arq = fopen(ARQ_FULLSCREEN_OPTION, "r");
    if (arq == NULL)
    {
        return false;
    }

    // se existir, lê o valor do arquivo
    char fullscreen[10];
    fscanf(arq, "%s", fullscreen);
    fclose(arq);
    return strcmp(fullscreen, "true") == 0;
}

void mudarOpcaoFullscreen()
{
    char fullscreen[10];

    strcpy(fullscreen, pegarFullscreen() ? "false" : "true");

    FILE *arq = fopen(ARQ_FULLSCREEN_OPTION, "w");
    fprintf(arq, fullscreen);
    fclose(arq);
}

void inicializarArquivosVetores()
{
    // checa se o arquivo de scores existe, se sim, não faz nada, se não, cria o arquivo
    FILE *arq = fopen(ARQ_SCORE, "r");
    if (arq != NULL)
    {
        fclose(arq);
        return;
    }

    // inicializa o vetor de scores
    Score *scores = (Score *)malloc(QTD_LIDERES * sizeof(Score));

    // inicializa o vetor de scores com -1 (vazio)
    for (int i = 0; i < QTD_LIDERES; i++)
    {
        scores[i] = criarScore(-1, "NULL", NENHUMA);
    }

    arq = fopen(ARQ_SCORE, "wb");

    if (arq == NULL)
    {
        exit(1);
    }

    fwrite(scores, sizeof(Score), QTD_LIDERES, arq);
    fclose(arq);

    free(scores);
}

Score criarScore(int pontos, char *nome, TipoVitoria vitoria)
{
    Score score;
    score.score = pontos;
    score.id = rand();
    score.data = time(NULL);
    score.vitoria = vitoria;
    strcpy(score.nome, nome);

    return score;
}

Score *allScores()
{
    Score *scores = (Score *)malloc(QTD_LIDERES * sizeof(Score));

    if (scores != NULL)
    {
        FILE *arq = fopen(ARQ_SCORE, "rb");

        if (arq != NULL)
        {
            fread(scores, sizeof(Score), QTD_LIDERES, arq);
            fclose(arq);
        }
    }

    return scores;
}

void converterTime(time_t time, char *data)
{
    struct tm *tm = localtime(&time);
    strftime(data, TAMANHO_DATA * sizeof(char), "%d/%m/%Y %H:%M:%S", tm);
}

void inserirOrdenado(Score *scores, Score score)
{
    // o vetor deverá ser ordenado de forma crescente

    /*
        checa se o score pode ser inserido no vetor
        ele nao pode ser maior que o ultimo score do vetor
    */

    if (
        scores[QTD_LIDERES - 1].score != -1            // se o ultimo score nao for vazio
        && score.score > scores[QTD_LIDERES - 1].score // se o score for maior que o ultimo score
    )
    {
        return;
    }

    // procurar o lugar onde o score deve ser inserido
    int indice = 0;

    for (; indice < QTD_LIDERES; indice++)
    {
        if (scores[indice].score > score.score)
        {
            break;
        }
    }

    // shift todos os scores a partir do indice para a direita
    for (int i = QTD_LIDERES - 1; i > indice; i--)
    {
        scores[i] = scores[i - 1];
    }

    // inserir o score no lugar encontrado
    scores[indice] = score;
}

bool checarSeScoreEValido(Score score)
{
    return score.score != -1;
}

void saveScore(int pontos, char *nome, TipoVitoria vitoria)
{
    Score score = criarScore(pontos, nome, vitoria);
    Score *scores = allScores();

    inserirOrdenado(scores, score);

    FILE *arq = fopen(ARQ_SCORE, "wb");

    if (arq != NULL)
    {
        fwrite(scores, sizeof(Score), QTD_LIDERES, arq);
        fclose(arq);
    }
}

void imprimirScore(Score score, int lin)
{
    linhaCol(15 + lin, 55);
    printf("%s", score.nome);
    linhaCol(15 + lin, 83);

    if (score.score < 0 || abs(score.score) > 99)
        printf("%d", score.score);
    else if (score.score < 9)
        printf("00%d", score.score);
    else
        printf("0%d", score.score);

    linhaCol(15 + lin, 94);
    char *data = (char *)malloc(TAMANHO_DATA * sizeof(char));
    converterTime((time_t)score.data, data);
    printf("%s", data);
}

void scoreTest()
{
    srand(time(NULL));
    inicializarArquivosVetores();

    printf("Criando scores...\n");
    int pontos[QTD_LIDERES + 1] = {
        21,
        34,
        45,
        56,
        67,
        78,
        89,
        90,
        100,
        35,
        65,
        38,
        65,
        45,
        56,
        765};

    for (int i = 0; i < QTD_LIDERES + 1; i++)
    {
        int vitoria = rand() % 3;
        saveScore(
            vitoria == 0 ? pontos[i] : (vitoria == 1 ? -50 : -99), "IDK", vitoria);
    }

    printf("\n");
    printf("Scores:\n");
    Score *scores = allScores();

    for (int i = 0; i < QTD_LIDERES; i++)
    {
        printf("score: %d\n", scores[i].score);
        printf("nome: %s\n", scores[i].nome);
        printf("id: %d\n", scores[i].id);
        printf("data: %d\n", scores[i].data);
        char data[TAMANHO_DATA];
        converterTime((time_t)scores[i].data, data);
        printf("data formatada: %s\n", data);
        printf("vitoria: %d\n", scores[i].vitoria);
        printf("========\n");
    }

    free(scores);

    printf("\n");
}

void fullscreenTest()
{
    inicializarArquivoFullscreen();

    bool fullscreen = pegarFullscreen();

    printf("Fullscreen: %d\n", fullscreen);

    mudarOpcaoFullscreen(!fullscreen);

    fullscreen = pegarFullscreen();

    printf("Fullscreen: %d\n", fullscreen);
}