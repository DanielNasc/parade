/*
    Arquivos encarregados de salvar, carregar e modificar os scores dos jogadores em arquivos binários.
    Para que depois possa ser exibida uma tabela de leaderboard.
*/

#ifndef SAVE_H
#define SAVE_H

typedef struct score Score;

#define ARQ_SCORE "score.bin"
#define MAX_SCORE 15

Score *criarScore(int);
Score *allScores();

void saveScore(int);

void scoreTest();

#endif // SAVE_H