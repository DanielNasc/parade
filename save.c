#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include "save.h"

typedef struct score
{
    int score;
    int id;
    int data; // data em que o score foi salvo
} Score;

Score *criarScore(int pontos)
{
    Score *score = (Score *)malloc(sizeof(Score));

    if (score != NULL)
    {
        score->score = pontos;
        score->id = rand();
        score->data = time(NULL);
    }

    return score;
}

Score *allScores()
{
    Score *scores = (Score *)malloc(sizeof(Score) * MAX_SCORE);

    if (scores != NULL)
    {
        FILE *arq = fopen(ARQ_SCORE, "rb");

        if (arq != NULL)
        {
            fread(scores, sizeof(Score), MAX_SCORE, arq);
            fclose(arq);
        }
    }

    return scores;
}

void inserirOrdenado(Score *scores, Score *score)
{
    // procurar o lugar onde o score deve ser inserido
    int indice = 0;

    for (; indice < MAX_SCORE; indice++)
    {
        if (scores[indice].score < score->score)
        {
            break;
        }
    }

    // shift todos os scores a partir do indice para a direita
    for (int i = MAX_SCORE - 1; i > indice; i--)
    {
        scores[i] = scores[i - 1];
    }

    // inserir o score no lugar encontrado
    scores[indice] = *score;
}

void saveScore(int pontos)
{
    Score *score = criarScore(pontos);
    Score *scores = allScores();

    if (score != NULL)
    {
        inserirOrdenado(scores, score);

        FILE *arq = fopen(ARQ_SCORE, "wb");

        if (arq != NULL)
        {
            fwrite(scores, sizeof(Score), MAX_SCORE, arq);
            fclose(arq);
        }
    }
}

void scoreTest()
{
    srand(time(NULL));
    printf("Criando scores...\n");
    int pontos[MAX_SCORE + 1] = {
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

    for (int i = 0; i < MAX_SCORE + 1; i++)
    {
        saveScore(pontos[i]);
    }

    printf("\n");
    printf("Scores:\n");
    Score *scores = allScores();
    for (int i = 0; i < MAX_SCORE; i++)
    {
        printf("score: %d\n", scores[i].score);
        printf("id: %d\n", scores[i].id);
        printf("data: %d\n", scores[i].data);
        printf("========\n");
    }

    free(scores);

    printf("\n");
}