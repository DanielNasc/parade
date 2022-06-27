#include <windows.h>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>

#include "interface.h"
#include "caracters.h"

void irParaxy(int x, int y)
{
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), (COORD){x - 1, y - 1});
}

void imprimeCaixa(int linha_sup, int col_esq, int linha_inf, int col_dir)
{
    int col, linha, largura, altura;

    largura = col_dir - col_esq;
    altura = linha_inf - linha_sup;

    // Desenha as linhas horizontais da caixa
    for (col = col_esq; col <= col_dir; col++)
    {
        irParaxy(col, linha_sup);
        printf("%c", LINHA_HORIZONTAL);
        irParaxy(col, linha_inf);
        printf("%c", LINHA_HORIZONTAL);
    }

    // Preenche a caixa com espaços em branco
    for (linha = linha_sup + 1; linha < linha_inf; linha++)
    {
        for (col = col_esq; col <= col_dir; col++)
        {
            irParaxy(col, linha);
            printf(" ");
        }
    }

    // Desenha as linhas verticais da caixa
    for (linha = linha_sup; linha <= linha_inf; linha++)
    {
        irParaxy(col_esq, linha);
        printf("%c", LINHA_VERTICAL);
        irParaxy(col_dir, linha);
        printf("%c", LINHA_VERTICAL);
    }

    // Desenha os cantos da caixa
    irParaxy(col_esq, linha_sup);
    printf("%c", CANTO_SUP_ESQUERDO);
    irParaxy(col_esq, linha_inf);
    printf("%c", CANTO_INF_ESQUERDO);
    irParaxy(col_dir, linha_sup);
    printf("%c", CANTO_SUP_DIREITO);
    irParaxy(col_dir, linha_inf);
    printf("%c", CANTO_INF_DIREITO);
}

void corTexto(CorLetras cor, CorFundo fundo)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), fundo + cor);
}

void corCarta(char naipe)
{
    switch (naipe - 'A')
    {
    case 0:
        corTexto(RED, _BLACK);
        break;
    case 1:
        corTexto(BLUE, _BLACK);
        break;
    case 2:
        corTexto(LIGHTMAGENTA, _BLACK);
        break;
    case 3:
        corTexto(BROWN, _BLACK);
        break;
    case 4:
        corTexto(LIGHTCYAN, _BLACK);
        break;
    case 5:
        corTexto(GREEN, _BLACK);
        break;
    default:
        corTexto(WHITE, _BLACK);
        break;
    }
}

void corTurno(bool vezDoJogador)
{
    HANDLE hConsole;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo;

    GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
    WORD saved_attributes = consoleInfo.wAttributes;

    int colComputador = 96, linhaComputador = 15,
        colJogador = 95, linhaJogador = 42;

    if (vezDoJogador)
    {
        corTexto(BLACK, _GREEN);
        irParaxy(colJogador, linhaJogador);
        printf("      JOGADOR      ");
        corTexto(BLACK, _RED);
        irParaxy(colComputador, linhaComputador);
        printf("    COMPUTADOR    ");
    }
    else
    {
        corTexto(BLACK, _RED);
        irParaxy(colJogador, linhaJogador);
        printf("      JOGADOR      ");
        corTexto(BLACK, _GREEN);
        irParaxy(colComputador, linhaComputador);
        printf("    COMPUTADOR    ");
    }

    SetConsoleTextAttribute(hConsole, saved_attributes); // restaura as cores antigas
}

void menu(int tempo)
{
    HANDLE hConsole;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo;

    GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
    WORD saved_attributes = consoleInfo.wAttributes;

    imprimeCaixa(2, 5, 41, 118);

    corTexto(BLACK, MAGENTA);
    imprimeCaixa(3, 7, 14, 116);
    SetConsoleTextAttribute(hConsole, saved_attributes);

    // imprime gato
    // Computer Art
    corTexto(BLACK, _MAGENTA);
    irParaxy(4, 57);
    printf(".'\\   /`.");
    irParaxy(5, 55);
    printf(".'.-.`-'.-.`.");
    irParaxy(6, 50);
    printf("..._:   .-. .-.   :_...");
    irParaxy(7, 48);
    printf(".'    '-.(");
    corTexto(CYAN, _MAGENTA);
    printf("o");
    corTexto(BLACK, _MAGENTA);
    printf(" ) (");
    corTexto(CYAN, _MAGENTA);
    printf("o");
    corTexto(BLACK, _MAGENTA);
    printf(" ).-'    `.");
    irParaxy(8, 47);
    printf("|  _    _ _`~(_)~`_ _    _  |");
    irParaxy(9, 46);
    printf("|  /:   ' .-=_   _=-. `   ;\\  |");
    irParaxy(10, 46);
    printf("|   :|-.._  '     `  _..-|:   |");
    irParaxy(11, 47);
    printf("|   `:| |`:-:-.-:-:'| |:'   |");
    irParaxy(12, 48);
    printf("`.   `.| | | | | | |.'   .'");
    irParaxy(13, 50);
    printf("`.   `-:_| | |_:-'   .'");
    SetConsoleTextAttribute(hConsole, saved_attributes);

    // Letra P
    Sleep(tempo);
    corTexto(MAGENTA, BLACK);
    irParaxy(16, 37);
    printf("%c%c%c%c", TEXTURA, TEXTURA, TEXTURA, TEXTURA);
    irParaxy(19, 37);
    printf("%c%c%c%c", TEXTURA, TEXTURA, TEXTURA, TEXTURA);

    for (int i = 0; i < 7; i++)
    {
        irParaxy(16 + i, 36);
        printf("%c", TEXTURA);
    }

    for (int i = 0; i < 7; i++)
    {
        irParaxy(16 + i, 37);
        printf("%c", TEXTURA);
    }

    irParaxy(16, 39);
    printf("%c", TEXTURA);

    for (int i = 0; i < 2; i++)
    {
        irParaxy(17 + i, 40);
        printf("%c%c", TEXTURA, TEXTURA);
    }
    irParaxy(42, 1);
    SetConsoleTextAttribute(hConsole, saved_attributes);

    // Letra A
    Sleep(tempo);
    corTexto(BROWN, _BLACK);
    irParaxy(16, 46);
    printf("%c%c%c", TEXTURA, TEXTURA, TEXTURA);
    irParaxy(19, 46);
    printf("%c%c%c", TEXTURA, TEXTURA, TEXTURA);

    for (int i = 0; i < 6; i++)
    {
        irParaxy(17 + i, 45);
        printf("%c", TEXTURA);
    }

    for (int i = 0; i < 7; i++)
    {
        irParaxy(16 + i, 46);
        printf("%c", TEXTURA);
    }

    for (int i = 0; i < 7; i++)
    {
        irParaxy(16 + i, 49);
        printf("%c", TEXTURA);
    }

    for (int i = 0; i < 6; i++)
    {
        irParaxy(17 + i, 50);
        printf("%c", TEXTURA);
    }
    irParaxy(42, 1);
    SetConsoleTextAttribute(hConsole, saved_attributes);

    // Letra R
    Sleep(tempo);
    corTexto(GREEN, _BLACK);
    irParaxy(16, 55);
    printf("%c%c%c", TEXTURA, TEXTURA, TEXTURA);
    irParaxy(19, 55);
    printf("%c%c%c", TEXTURA, TEXTURA, TEXTURA);

    for (int i = 0; i < 6; i++)
    {
        irParaxy(17 + i, 55);
        printf("%c", TEXTURA);
    }

    for (int i = 0; i < 7; i++)
    {
        irParaxy(16 + i, 54);
        printf("%c", TEXTURA);
    }

    irParaxy(20, 57);
    printf("%c", TEXTURA);
    irParaxy(21, 58);
    printf("%c", TEXTURA);

    for (int i = 0; i < 7; i++)
    {
        if (i != 4 && i != 5 && i != 6)
        {
            irParaxy(16 + i, 58);
            printf("%c", TEXTURA);
        }
    }

    irParaxy(17, 59);
    printf("%c", TEXTURA);
    irParaxy(18, 59);
    printf("%c", TEXTURA);
    irParaxy(22, 58);
    printf("%c%c", TEXTURA, TEXTURA);
    irParaxy(42, 1);
    SetConsoleTextAttribute(hConsole, saved_attributes);

    // Letra A
    Sleep(tempo);
    corTexto(BROWN, _BLACK);
    irParaxy(16, 64);
    printf("%c%c%c", TEXTURA, TEXTURA, TEXTURA);
    irParaxy(19, 64);
    printf("%c%c%c", TEXTURA, TEXTURA, TEXTURA);

    for (int i = 0; i < 6; i++)
    {
        irParaxy(17 + i, 63);
        printf("%c", TEXTURA);
    }

    for (int i = 0; i < 7; i++)
    {
        irParaxy(16 + i, 64);
        printf("%c", TEXTURA);
    }

    for (int i = 0; i < 7; i++)
    {
        irParaxy(16 + i, 67);
        printf("%c", TEXTURA);
    }

    for (int i = 0; i < 6; i++)
    {
        irParaxy(17 + i, 68);
        printf("%c", TEXTURA);
    }
    irParaxy(42, 1);
    SetConsoleTextAttribute(hConsole, saved_attributes);

    // Letra D
    Sleep(tempo);
    corTexto(BLUE, _BLACK);
    irParaxy(16, 73);
    printf("%c%c%c", TEXTURA, TEXTURA, TEXTURA);
    irParaxy(22, 73);
    printf("%c%c%c", TEXTURA, TEXTURA, TEXTURA);

    irParaxy(17, 76);
    printf("%c", TEXTURA);
    irParaxy(18, 76);
    printf("%c", TEXTURA);

    for (int i = 0; i < 7; i++)
    {
        irParaxy(16 + i, 72);
        printf("%c", TEXTURA);
    }

    for (int i = 0; i < 7; i++)
    {
        irParaxy(16 + i, 73);
        printf("%c", TEXTURA);
    }

    for (int i = 0; i < 3; i++)
    {
        irParaxy(19 + i, 76);
        printf("%c", TEXTURA);
    }
    irParaxy(42, 1);
    SetConsoleTextAttribute(hConsole, saved_attributes);

    // Letra E
    Sleep(tempo);
    corTexto(RED, _BLACK);
    irParaxy(16, 81);
    printf("%c%c%c", TEXTURA, TEXTURA, TEXTURA);
    irParaxy(19, 81);
    printf("%c%c%c", TEXTURA, TEXTURA, TEXTURA);
    irParaxy(22, 81);
    printf("%c%c%c", TEXTURA, TEXTURA, TEXTURA);

    for (int i = 0; i < 7; i++)
    {
        irParaxy(16 + i, 80);
        printf("%c", TEXTURA);
    }
    for (int i = 0; i < 6; i++)
    {
        irParaxy(16 + i, 81);
        printf("%c", TEXTURA);
    }

    irParaxy(16, 81);
    printf("%c", TEXTURA);
    irParaxy(42, 1);
    SetConsoleTextAttribute(hConsole, saved_attributes);

    irParaxy(27, 57);
    printf("Iniciar o Jogo");
    irParaxy(30, 57);
    printf("Manual do Jogo");
    irParaxy(1, 1);
}