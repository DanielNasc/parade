/*
    Arquivos encarregados de salvar, carregar e modificar os scores dos jogadores em arquivos binários.
    Para que depois possa ser exibida uma tabela de leaderboard.
*/

#ifndef SAVE_H
#define SAVE_H
#include <stdbool.h>
#include "jogo.h"

#define ARQ_SCORE "score.bin"
#define QTD_LIDERES 15
#define TAMANHO_NOME 10
#define TAMANHO_DATA 20

typedef struct score
{
    int score;
    int id;
    int data; // data em que o score foi salvo
    char nome[TAMANHO_NOME];
    TipoVitoria vitoria;
} Score;

void inicializarArquivosVetores();
Score criarScore(int, char *, TipoVitoria);
Score *allScores();

void saveScore(int, char *, TipoVitoria);

void scoreTest();
void converterTime(time_t, char *);
void imprimirScore(Score, int);

bool checarSeScoreEValido(Score);

#endif // SAVE_H