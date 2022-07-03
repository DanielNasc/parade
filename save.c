#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "save.h"
#include "interface.h"
#include "caracters.h"

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

void inicializarArquivosVetores()
{
    // checa se o arquivo de scores existe, se sim, não faz nada, se não, cria o arquivo
    FILE *arq = fopen(ARQ_SCORE, "rb");
    if (arq != NULL)
    {
        fclose(arq);
        return;
    }

    // se não existir, cria o arquivo
    fclose(arq);

    arq = fopen(ARQ_SCORE, "wb");

    // inicializa o arquivo com um vetor de scores vazio
    Score *scores = (Score *)malloc(sizeof(Score) * QTD_LIDERES);

    for (int i = 0; i < QTD_LIDERES; i++)
        scores[i] = criarScore(SCORE_VAZIO, "VAZIO", NENHUMA);

    fwrite(scores, sizeof(Score), QTD_LIDERES, arq);
    fclose(arq);
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
        scores[QTD_LIDERES - 1].score != SCORE_VAZIO   // se o ultimo score nao for vazio
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
    return score.score != SCORE_VAZIO;
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

    if (score.score == PONTOS_VITORIA_PERFEITA)
        printf("%c%c%c", CORACAO, CORACAO, CORACAO);
    else if (score.score == PONTOS_VITORIA_NORMAL)
        printf(" %c%c", CORACAO, CORACAO);
    else if (score.score <= 9)
        printf("00%d", score.score);
    else if (score.score <= 99)
        printf("0%d", score.score);
    else
        printf("%d", score.score);

    linhaCol(15 + lin, 94);
    char *data = (char *)malloc(TAMANHO_DATA * sizeof(char));
    converterTime((time_t)score.data, data);
    printf("%s", data);
}

bool nomeDoSave(char *nome)
{

    clearStdin();
    system("cls");
    box(12, 60, 28, 107);

    int tecla;

    corTexto(LIGHTRED, _BLACK);
    linhaCol(17, 67);
    printf("COMO GOSTARIA DE SALVAR SEU JOGO?");
    resetarAtributos();
    linhaCol(18, 80);

    // ouvir o input do usuario
    // colocar o que ele digitou no nome
    // nao permitir que o usuario digite mais de TAMANHO_NOME caracteres

    int i;
    for (i = 0; i < TAMANHO_NOME - 1;)
    {
        tecla = getch();

        if (tecla == ENTER || tecla == ESC)
        {
            break;
        }
        else if (tecla == BACKSPACE)
        {
            if (i > 0)
            {
                i--;
                nome[i] = '\0';
                linhaCol(18, 80 + i);
                printf(" ");
            }
        }
        // se a tecla nao for uma letra, numero ou espaco, ignorar
        else if (
            (tecla < 'a' || tecla > 'z') &&
            (tecla < 'A' || tecla > 'Z') &&
            (tecla < '0' || tecla > '9') &&
            tecla != ' ')
        {
            continue;
        }
        else
        {
            nome[i] = tecla;
            linhaCol(18, 80 + i);
            printf("%c", tecla);
            i++;
        }

        linhaCol(18, 80 + i);
    }

    nome[i] = '\0';

    linhaCol(20, 79);
    corTexto(LIGHTRED, _BLACK);
    printf("CONFIRMAR?");
    resetarAtributos();
    linhaCol(21, 71);
    printf("[ENTER] - Sim");
    linhaCol(21, 86);
    printf("[ESC] - Nao");

    do
    {
        tecla = getch();
    } while (tecla != ENTER && tecla != ESC);

    if (tecla == ESC)
    {
        system("cls");
        return false;
    }
    else
    {
        linhaCol(23, 70);
        corTexto(YELLOW, _BLACK);
        printf("JOGO SALVO COMO: %s", nome);
        resetarAtributos();
    }

    return true;
}
