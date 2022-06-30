/*
    Arquivos encarregados de salvar, carregar e modificar os scores dos jogadores em arquivos binários.
    Para que depois possa ser exibida uma tabela de leaderboard.
*/

#ifndef SAVE_H
#define SAVE_H
#include "jogo.h"

typedef struct score Score;
typedef char *string;

#define ARQ_SCORE "score.bin"
#define QTD_LIDERES 15

void inicializarArquivosVetores();
Score criarScore(int, string, TipoVitoria);
Score *allScores();

void saveScore(int, string, TipoVitoria);

void scoreTest();

#endif // SAVE_H