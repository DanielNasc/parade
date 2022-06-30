/*
    Arquivos encarregados de salvar, carregar e modificar os scores dos jogadores em arquivos binários.
    Para que depois possa ser exibida uma tabela de leaderboard.
*/

#ifndef SAVE_H
#define SAVE_H
#include "jogo.h"

typedef struct score Score;

#define ARQ_SCORE "score.bin"
#define QTD_LIDERES 15
#define TAMANHO_NOME 10
#define TAMANHO_DATA 20

void inicializarArquivosVetores();
Score criarScore(int, char *, TipoVitoria);
Score *allScores();

void saveScore(int, char *, TipoVitoria);

void scoreTest();

#endif // SAVE_H