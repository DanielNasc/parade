#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <string.h>
#include "save.h"

typedef struct score
{
    int score;
    int id;
    int data; // data em que o score foi salvo
    char nome[10];
    TipoVitoria vitoria;
} Score;

void inicializarArquivosVetores()
{
    // inicializa o vetor de scores
    Score *scores = (Score *)malloc(QTD_LIDERES * sizeof(Score));

    // inicializa o vetor de scores com -1 (vazio)
    for (int i = 0; i < QTD_LIDERES; i++)
    {
        scores[i] = criarScore(-1, "NULL", NENHUMA);
    }

    FILE *arq = fopen(ARQ_SCORE, "wb");

    if (arq == NULL)
    {
        exit(1);
    }

    fwrite(scores, sizeof(Score), QTD_LIDERES, arq);
    fclose(arq);

    free(scores);
}

Score criarScore(int pontos, string nome, TipoVitoria vitoria)
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

void inserirOrdenado(Score *scores, Score score)
{
    // procurar o lugar onde o score deve ser inserido
    int indice = 0;

    for (; indice < QTD_LIDERES; indice++)
    {
        if (scores[indice].score < score.score)
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

void saveScore(int pontos, string nome, TipoVitoria vitoria)
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
        saveScore(pontos[i], "IDK", rand() % 3);
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
        printf("vitoria: %d\n", scores[i].vitoria);
        printf("========\n");
    }

    free(scores);

    printf("\n");
}