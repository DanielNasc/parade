
#include "carta.h"
#include "jogo.h"
#include "lista.h"
#include "pilha.h"
#include "interface.h"
#include "caracters.h"

// Função que muda a cor do sistema
void textColor(int letras, int fundo)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), letras + fundo);
}

// Função que leva o cursor para uma coordenada da tela
void linhaCol(int linha, int coluna)
{
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), (COORD){coluna - 1, linha - 1});
}

// Função que imprime uma caixa
void box(int linha_1, int coluna_1, int linha_2, int coluna_2)
{
    int i, largura;

    // Acha o tamanho do box
    largura = linha_2 - linha_1;

    // Monta o box
    for (i = coluna_1; i <= coluna_2; i++)
    {
        linhaCol(linha_1, i);
        printf("%c", LINHA_HORIZONTAL);
        linhaCol(linha_2, i);
        printf("%c", LINHA_HORIZONTAL);
    }
    // Cria a box colorida
    int j;
    for (j = 1; j < largura; j++)
    {
        for (i = coluna_1 + 1; i <= coluna_2; i++)
        {
            linhaCol(linha_1 + j, i);
            printf(" ");
        }
    }

    // Laterais
    for (i = linha_1; i <= linha_2; i++)
    {
        linhaCol(i, coluna_1);
        printf("%c", LINHA_VERTICAL);
        linhaCol(i, coluna_2);
        printf("%c", LINHA_VERTICAL);
    }
    // Posicoes dos cantos
    linhaCol(linha_1, coluna_1);
    printf("%c", CANTO_SUP_ESQUERDO);
    linhaCol(linha_1, coluna_2);
    printf("%c", CANTO_SUP_DIREITO);
    linhaCol(linha_2, coluna_1);
    printf("%c", CANTO_INF_ESQUERDO);
    linhaCol(linha_2, coluna_2);
    printf("%c", CANTO_INF_DIREITO);
}

void simSelecionado()
{
    linhaCol(29, 74);
    printf("%c SIM", SETAS_DUPLAS);
    linhaCol(29, 84);
    printf("não", 131);
}

// Função que imprime a caixa de texto perguntando se o jogador que encerrar o jogo
int question()
{
    int tecla;
    int sim_nao = 1;

    // Monta a tela
    box(25, 51, 33, 112); // linha = 8, coluna = 22

    // // linguagem(1);
    linhaCol(27, 76);
    printf("Deseja sair?");
    simSelecionado();

    // linguagem(0);
    imprimirControles(31, 55);
    printf("  [ESC] - Voltar");

    linhaCol(42, 1);

    while (1)
    {
        tecla = getch();
        fflush(stdin);
        if (tecla == ESC)
        { // ESC
            sim_nao = 0;
            break;
        }
        else if (tecla == ENTER)
        { // Enter
            break;
        }

        // Alterna entre o sim e o nao
        if (tecla == ARROW_ESQUERDA)
        {
            simSelecionado();
            linhaCol(42, 1);
            sim_nao = 1;
        }
        else if (tecla == ARROW_DIREITA)
        {
            // linguagem(1);
            linhaCol(29, 74);
            printf("  sim");
            linhaCol(29, 82);
            printf("%c NAO", 175);
            linhaCol(42, 1);
            // linguagem(0);
            sim_nao = 0;
        }
    }

    return sim_nao;
}

// comentada
void imprimirMao(ListaCarta *mao)
{
    /* Função de Interface
    Imprime a mão do jogador
    */

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
    WORD saved_attributes;

    /* Salvar estado atual */
    GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
    saved_attributes = consoleInfo.wAttributes;

    // aux aponta para a última carta da lista
    Carta *aux = ultimaCarta(mao);
    int col = 0;
    for (int i = 0; i < QTD_LOOPS_PREENCHER_MAO; i++)
    {
        if (aux == NULL)
        {
            // box representando carta vazia
            box(30, 29 + col, 37, 38 + col);
            return;
        }
        // muda a cor do sistema para a cor da carta
        corDaCarta(aux);
        // box exterior da carta
        box(30, 29 + col, 37, 38 + col);
        // box interior da carta
        box(31, 30 + col, 36, 37 + col);
        // imprime o número e o naipe
        linhaCol(31, 30 + col);
        printf("%c", aux->naipe);
        linhaCol(36, 37 + col);
        printf("%c", aux->naipe);
        linhaCol(33, 33 + col);
        if (aux->numero != 10)
            printf("0%d", aux->numero);
        else
            printf("%d", aux->numero);
        SetConsoleTextAttribute(hConsole, saved_attributes);
        // coluna incrementa em 15
        col += 15;
        // aux aponta para a carta anterior
        aux = aux->ant;
    }
}

// comentada
int escolhaCarta(ListaCarta *mao, int indice)
{
    /* Função que retorna o índice da carta escolhida da mão. */
    if (mao == NULL)
        return 0;

    // criei um indice anterior para quando a mão tiver uma quantidade de cartas menor do que 5
    int indiceAnterior = indice, tecla = 0;
    // imprime o indicador de qual carta está selecionada
    indicadorDeCarta(indice);
    // loop até o jogador apertar a tecla enter
    do
    { // Enter
        do
        {
            tecla = getch();
            fflush(stdin);
        } while (tecla != ENTER && tecla != ARROW_ESQUERDA && tecla != ARROW_DIREITA); // alternar
        // se a tecla digitada for -> e o indice for menor do que o indice anterior, ele incrementa
        if (tecla == ARROW_DIREITA && indice < indiceAnterior)
        {
            indice++;
        }
        // se a tecla digitada for <- e o indice for maior do que 0, ele decrementa
        if (tecla == ARROW_ESQUERDA && indice > 0)
        {
            indice--;
        }
        // imprime o indicador novamente
        indicadorDeCarta(indice);
    } while (tecla != ENTER);
    return indice;
}

// comentada
int corDaCarta(Carta *carta)
{
    // Função que modifica a cor do sistema conforme o naipe da carta passada como parâmetro
    if (carta == NULL)
        return 0;

    switch (carta->naipe)
    {
    case 'A':
        textColor(RED, _BLACK);
        return 1;
    case 'B':
        textColor(BLUE, _BLACK);
        return 1;
    case 'C':
        textColor(LIGHTMAGENTA, _BLACK);
        return 1;
    case 'D':
        textColor(BROWN, _BLACK);
        return 1;
    case 'E':
        textColor(LIGHTCYAN, _BLACK);
        return 1;
    case 'F':
        textColor(GREEN, _BLACK);
        return 1;
    }
}

// comentada
int indicadorDeCarta(int indice)
{
    /* Função de Interface
    Imprime o indicador de qual carta está selecionada conforme o parâmetro de índice.
        0 -> primeira carta da mão
        1 -> segunda carta da mão
        2 -> ...
        3 -> ..
        4 -> quinta e última carta da mão
    Para não precisar limpar a tela toda, eu apenas imprimi "espaços" nas demais áreas.
    */

    if (indice < 0 || indice > 4)
        return 0;

    switch (indice)
    {
    case 0:
        linhaCol(38, 32);
        printf("%c%c%c%c", CANTO_INF_ESQUERDO, LINHA_HORIZONTAL, LINHA_HORIZONTAL, CANTO_INF_DIREITO);
        linhaCol(39, 33);
        printf("%c%c", TEXTURA_BARALHO, TEXTURA_BARALHO);
        linhaCol(38, 47);
        printf("    ");
        linhaCol(39, 48);
        printf("  ");
        linhaCol(42, 1);
        return 1;
    case 1:
        linhaCol(38, 32);
        printf("    ");
        linhaCol(39, 33);
        printf("  ");
        linhaCol(38, 47);
        printf("%c%c%c%c", CANTO_INF_ESQUERDO, LINHA_HORIZONTAL, LINHA_HORIZONTAL, CANTO_INF_DIREITO);
        linhaCol(39, 48);
        printf("%c%c", TEXTURA_BARALHO, TEXTURA_BARALHO);
        linhaCol(38, 62);
        printf("    ");
        linhaCol(39, 63);
        printf("  ");
        linhaCol(42, 1);
        return 1;
    case 2:
        linhaCol(38, 47);
        printf("    ");
        linhaCol(39, 48);
        printf("  ");
        linhaCol(38, 62);
        printf("%c%c%c%c", CANTO_INF_ESQUERDO, LINHA_HORIZONTAL, LINHA_HORIZONTAL, CANTO_INF_DIREITO);
        linhaCol(39, 63);
        printf("%c%c", TEXTURA_BARALHO, TEXTURA_BARALHO);
        linhaCol(38, 77);
        printf("    ");
        linhaCol(39, 78);
        printf("  ");
        linhaCol(42, 1);
        return 1;
    case 3:
        linhaCol(38, 62);
        printf("    ");
        linhaCol(39, 63);
        printf("  ");
        linhaCol(38, 77);
        printf("%c%c%c%c", CANTO_INF_ESQUERDO, LINHA_HORIZONTAL, LINHA_HORIZONTAL, CANTO_INF_DIREITO);
        linhaCol(39, 78);
        printf("%c%c", TEXTURA_BARALHO, TEXTURA_BARALHO);
        linhaCol(38, 92);
        printf("    ");
        linhaCol(39, 93);
        printf("  ");
        linhaCol(42, 1);
        return 1;
    case 4:
        linhaCol(38, 32);
        printf("    ");
        linhaCol(39, 33);
        printf("  ");
        linhaCol(38, 47);
        printf("    ");
        linhaCol(39, 48);
        printf("  ");
        linhaCol(38, 62);
        printf("    ");
        linhaCol(39, 63);
        printf("  ");
        linhaCol(38, 77);
        printf("    ");
        linhaCol(39, 78);
        printf("  ");
        linhaCol(38, 92);
        printf("%c%c%c%c", CANTO_INF_ESQUERDO, LINHA_HORIZONTAL, LINHA_HORIZONTAL, CANTO_INF_DIREITO);
        linhaCol(39, 93);
        printf("%c%c", TEXTURA_BARALHO, TEXTURA_BARALHO);
        linhaCol(42, 1);
        return 1;
    }
}

// comentada
void imprimirBaralho(Baralho *baralho)
{
    /* Função de Interface
    Imprime o baralho conforme a quantidade de cartas nele.
    */
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
    WORD saved_attributes;

    /* Salvar estado atual */
    GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
    saved_attributes = consoleInfo.wAttributes;

    int qtdCartas = tamanhoBaralho(baralho);
    box(26, 132, 28, 135);
    linhaCol(27, 133);
    if (qtdCartas < 10)
        printf("0%d", qtdCartas);
    else
        printf("%d", qtdCartas);
    int i = 4;
    // 1º Impressão possível: se a quantidade do baralho for maior do que 40
    if (tamanhoBaralho(baralho) > 40)
    {
        for (int j = 0; j < 4; j++)
        {
            linhaCol(28 - j, 120);
            printf("%c%c%c%c%c%c%c%c%c%c", 200, 205, 205, 205, 205, 205, 205, 205, 205, 188);
        }
    }
    // 2º Impressão possível: se a quantidade do baralho for maior do que 25 e menor ou igual a 40
    if (tamanhoBaralho(baralho) > 25 && tamanhoBaralho(baralho) <= 40)
    {
        i = 3;
        linhaCol(17, 120);
        printf("          ");
        for (int j = 0; j < 3; j++)
        {
            linhaCol(28 - j, 120);
            printf("%c%c%c%c%c%c%c%c%c%c", 200, 205, 205, 205, 205, 205, 205, 205, 205, 188);
        }
    }
    // 3º Impressão possível: se a quantidade do baralho for maior do que 15 e menor ou igual a 25
    if (tamanhoBaralho(baralho) > 15 && tamanhoBaralho(baralho) <= 25)
    {
        i = 2;
        linhaCol(17, 120);
        printf("          ");
        linhaCol(18, 120);
        printf("          ");
        for (int j = 0; j < 2; j++)
        {
            linhaCol(28 - j, 120);
            printf("%c%c%c%c%c%c%c%c%c%c", 200, 205, 205, 205, 205, 205, 205, 205, 205, 188);
        }
    }
    // 4º Impressão possível: se a quantidade do baralho for maior do que 1 e menor ou igual a 15
    if (tamanhoBaralho(baralho) > 1 && tamanhoBaralho(baralho) <= 15)
    {
        i = 1;
        linhaCol(17, 120);
        printf("          ");
        linhaCol(18, 120);
        printf("          ");
        linhaCol(19, 120);
        printf("          ");
        for (int j = 0; j < 1; j++)
        {
            linhaCol(28 - j, 120);
            printf("%c%c%c%c%c%c%c%c%c%c", 200, 205, 205, 205, 205, 205, 205, 205, 205, 188);
        }
    }
    // 5º Impressão possível: se tiver apenas uma carta no baralho
    if (tamanhoBaralho(baralho) == 1)
    {
        i = 0;
        linhaCol(17, 120);
        printf("          ");
        linhaCol(18, 120);
        printf("          ");
        linhaCol(19, 120);
        printf("          ");
        linhaCol(20, 120);
        printf("          ");
    }
    // 6º Impressão possível: se o baralho estiver vazio
    if (tamanhoBaralho(baralho) == 0)
    {
        box(21, 120, 28, 129);
        return;
    }

    // box exterior das cartas do baralho
    box(21 - i, 120, 28 - i, 129);
    textColor(RED, _BLACK);
    // art da parte de trás da carta
    linhaCol(22 - i, 121);
    printf("%c %c %c %c", TEXTURA_BARALHO, TEXTURA_BARALHO, TEXTURA_BARALHO, TEXTURA_BARALHO);
    linhaCol(23 - i, 121);
    printf(" %c %c %c %c", TEXTURA_BARALHO, TEXTURA_BARALHO, TEXTURA_BARALHO, TEXTURA_BARALHO);
    linhaCol(24 - i, 121);
    printf("%c %c %c %c", TEXTURA_BARALHO, TEXTURA_BARALHO, TEXTURA_BARALHO, TEXTURA_BARALHO);
    linhaCol(25 - i, 121);
    printf(" %c %c %c %c", TEXTURA_BARALHO, TEXTURA_BARALHO, TEXTURA_BARALHO, TEXTURA_BARALHO);
    linhaCol(26 - i, 121);
    printf("%c %c %c %c", TEXTURA_BARALHO, TEXTURA_BARALHO, TEXTURA_BARALHO, TEXTURA_BARALHO);
    linhaCol(27 - i, 121);
    printf(" %c %c %c %c", TEXTURA_BARALHO, TEXTURA_BARALHO, TEXTURA_BARALHO, TEXTURA_BARALHO);

    SetConsoleTextAttribute(hConsole, saved_attributes);
}

// comentada
void imprimirMesa(ListaCarta *mesa)
{
    if (mesa == NULL)
    {
        exit(1);
    }

    /*Função de Interface
    Imprime a Mesa do jogo.
    */
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
    WORD saved_attributes;

    /* Salvar estado atual */
    GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
    saved_attributes = consoleInfo.wAttributes;

    // box exterior da plaquinha com o nome "MESA"
    box(1, 26, 3, 37);
    textColor(BLACK, _WHITE);
    linhaCol(2, 26);
    printf("    MESA    ");
    SetConsoleTextAttribute(hConsole, saved_attributes);

    // imprimir cantos da caixa do jogador
    linhaCol(29, 110);
    printf("%c", LINHA_VERTICAL_CENTRO);
    linhaCol(29, 138);
    printf("%c", LINHA_VERTICAL_CENTRO_ESQUERDA);
    linhaCol(42, 110);
    printf("%c", LINHA_VERTICAL_CENTRO_CIMA);

    // imprimir cantos da caixa do computador
    linhaCol(2, 110);
    printf("%c", LINHA_VERTICAL_CENTRO_BAIXO);
    linhaCol(15, 110);
    printf("%c", LINHA_VERTICAL_CENTRO_DIREITA);

    // aux aponta para a última carta da lista da mesa
    Carta *aux = ultimaCarta(mesa);
    int lin = 18, col = 70;
    // for para definir as linhas e as colunas conforme a quantidade de cartas na mesa
    for (int i = 0; i < quantidadeCartasLista(mesa); i++)
    {
        if (i > 7 && i < 16)
        {
            lin = 12;
            if (i == 8)
                col += 80;
        }
        if (i > 15 && i < 24)
        {
            lin = 6;
            if (i == 16)
                col += 80;
        }
        if (i > 23 && i < 32)
        {
            lin = 0;
            if (i == 24)
                col += 80;
        }
        // a cor do sistema muda para a cor da carta
        corDaCarta(aux);
        // box exterior da carta
        box(4 + lin, 27 + col, 9 + lin, 34 + col);
        // box interior da carta
        box(5 + lin, 28 + col, 8 + lin, 33 + col);
        // imprime número e naipe
        linhaCol(5 + lin, 28 + col);
        printf("%c", aux->naipe);
        linhaCol(8 + lin, 33 + col);
        printf("%c", aux->naipe);
        linhaCol(6 + lin, 30 + col);
        if (aux->numero != 10)
            printf("0%d", aux->numero);
        else
            printf("%d", aux->numero);
        SetConsoleTextAttribute(hConsole, saved_attributes);
        // o auxiliar aponta para a carta anterior
        aux = aux->ant;
        // inteiro das colunas decrementa em 10
        col -= 10;
    }
}

// comentada
void imprimirNaipesColecao()
{
    /* Função de Interface
    Imprime uma caixa com o naipe das cartas na parte da galeria.
    */
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
    WORD saved_attributes;

    /* Salvar estado atual */
    GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
    saved_attributes = consoleInfo.wAttributes;

    // box exterior da plaquinha com o nome "GALERIA"
    box(42, 26, 44, 38);
    textColor(BLACK, _WHITE);
    linhaCol(43, 26);
    printf("   GALERIA   ");
    SetConsoleTextAttribute(hConsole, saved_attributes);

    int lin = 0;

    // Muda a cor do sistema conforme o naipe
    for (int naipe = 0; naipe < 6; naipe++)
    {
        switch (naipe)
        {
        case 0:
            textColor(RED, _BLACK);
            break;
        case 1:
            textColor(BLUE, _BLACK);
            break;
        case 2:
            textColor(LIGHTMAGENTA, _BLACK);
            break;
        case 3:
            textColor(BROWN, _BLACK);
            break;
        case 4:
            textColor(LIGHTCYAN, _BLACK);
            break;
        case 5:
            textColor(GREEN, _BLACK);
            break;
        }
        // box exterior da caixinha
        box(46 + lin, 23, 48 + lin, 28);
        linhaCol(47 + lin, 25);
        printf("%c %c", 'A' + naipe, SETA_DIREITA);
        SetConsoleTextAttribute(hConsole, saved_attributes);
        lin += 4;
    }
    SetConsoleTextAttribute(hConsole, saved_attributes);
}

void imprimirControles(int x, int y)
{
    // Função de Interface que que imprime os controles
    linhaCol(x, y);
    printf("[ %c | %c ] - Mover  [ENTER] - Confirmar", SETA_ESQUERDA, SETA_DIREITA);
}

// comentada
void imprimirJogador()
{
    /* Função de Interface
    Função que imprime a art usada para representar o jogador
    */
    // box exterior da área onde a art vai ficar
    box(29, 110, 42, 138);

    // imprimir cantos da caixa do jogador
    linhaCol(29, 110);
    printf("%c", LINHA_VERTICAL_CENTRO);
    linhaCol(29, 138);
    printf("%c", LINHA_VERTICAL_CENTRO_ESQUERDA);
    linhaCol(42, 110);
    printf("%c", LINHA_VERTICAL_CENTRO_CIMA);

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
    WORD saved_attributes;

    /* Salvar estado atual */
    GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
    saved_attributes = consoleInfo.wAttributes;

    // Combinei as funções "linhaCol+printf+textColor" para imprimir um coelhinho
    textColor(LIGHTMAGENTA, _BLACK);
    linhaCol(30, 123);
    printf("/|      __");
    linhaCol(31, 122);
    printf("/ |   ,-~ /");
    linhaCol(32, 121);
    printf("Y :|  /   /"); //-1
    linhaCol(33, 121);
    printf("|  | /  ./"); //-3
    linhaCol(34, 121);
    printf("> '~'  '"); //-3
    linhaCol(35, 120);
    printf("/       Y"); //-2
    linhaCol(36, 119);
    printf("j^  ^    |"); //+2
    linhaCol(37, 118);
    printf("(  T      j"); // 0
    linhaCol(38, 119);
    printf(">._   _./"); //-1
    linhaCol(39, 117);
    printf("/|  -'     l"); //-7
    linhaCol(40, 116);
    printf("/            \\"); //-9
    SetConsoleTextAttribute(hConsole, saved_attributes);
    box(41, 115, 43, 133);
    // box da plaquinha com o nome "JOGADOR".
    linhaCol(42, 115);
    printf("      JOGADOR      ");
    SetConsoleTextAttribute(hConsole, saved_attributes);
}

// comentada
void imprimirComputer()
{
    /* Função de Interface
    Função que imprime a art usada para representar o computador
    */
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
    WORD saved_attributes;

    /* Salvar estado atual */
    GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
    saved_attributes = consoleInfo.wAttributes;

    // Combinei as funções "linhaCol+printf+textColor" para imprimir um sapinho
    linhaCol(2, 110);
    printf("%c", LINHA_VERTICAL_CENTRO_BAIXO);
    linhaCol(15, 138);
    printf("%c", LINHA_VERTICAL_CENTRO_ESQUERDA);
    linhaCol(15, 110);
    printf("%c", LINHA_VERTICAL_CENTRO_DIREITA);

    for (int i = 0; i < 27; i++)
    {
        printf("%c", 205);
    }
    textColor(GREEN, _BLACK);
    linhaCol(7, 122);
    printf("_   _");
    linhaCol(8, 121);
    printf("(.)_(.)");
    linhaCol(9, 118);
    printf("_ (   _   ) _");
    linhaCol(10, 117);
    printf("/ \\/`-----'\\/ \\");
    linhaCol(11, 115);
    printf("__\\ ( (     ) ) /__");
    linhaCol(12, 115);
    printf(")   /\\ \\._./ /\\   (");
    linhaCol(13, 116);
    printf(")_/ /|\\   /|\\ \\_(");
    SetConsoleTextAttribute(hConsole, saved_attributes);
    // box da plaquinha com o nome "COMPUTADOR".
    box(14, 116, 16, 133);
    linhaCol(15, 116);
    printf("    COMPUTADOR    ");
}

// comentada
void imprimirCartaEscolhida(Carta *cartaEscolhida, int lin)
{
    /* Função de Interface
    Função que imprime no lado direito da tela, a carta escolhida por cada jogador, com um temporizador de 1 seg.
    */

    if (cartaEscolhida == NULL)
    {
        exit(1);
    }

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
    WORD saved_attributes;

    /* Salvar estado atual */
    GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
    saved_attributes = consoleInfo.wAttributes;

    linhaCol(29 - lin, 140);
    printf("| CARTA ESCOLHIDA |");
    corDaCarta(cartaEscolhida);
    // box exterior da carta
    box(30 - lin, 147, 33 - lin, 151); // linha = 3, coluna = 4
    // box interiro da carta
    box(31 - lin, 148, 32 - lin, 150);
    // impressão do número e do naipe na carta
    linhaCol(31 - lin, 149);
    printf("%c", cartaEscolhida->naipe);
    linhaCol(32 - lin, 149);
    // se a carta for de número 10, não é necessário imprimir o "0" na frente do número.
    if (cartaEscolhida->numero != 10)
        printf("0%d", cartaEscolhida->numero);
    else
        printf("%d", cartaEscolhida->numero);
    SetConsoleTextAttribute(hConsole, saved_attributes);
    // para não ter que limpar a tela toda, apenas imprime "espaços" no lugar onde anteriormente imprimiu a carta
    linhaCol(42, 1);
    Sleep(1000);
    linhaCol(29 - lin, 140);
    printf("                   ");
    linhaCol(30 - lin, 147);
    printf("        ");
    linhaCol(31 - lin, 147);
    printf("        ");
    linhaCol(32 - lin, 147);
    printf("        ");
    linhaCol(33 - lin, 147);
    printf("        ");
    linhaCol(34 - lin, 147);
    printf("        ");
    linhaCol(42, 1);
}

// comentada
void menu(int tempo)
{
    /* Função de Interface
    Função que imprime na tela toda a interface do Menu.
    */
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
    WORD saved_attributes;

    /* Salvar estado atual */
    GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
    saved_attributes = consoleInfo.wAttributes;

    // Box exterior
    box(2, 25, 41, 138);

    // Box interior superior
    textColor(BLACK, _MAGENTA);
    box(3, 27, 14, 136);
    SetConsoleTextAttribute(hConsole, saved_attributes);

    // Computer Art
    textColor(BLACK, _MAGENTA);
    linhaCol(4, 77);
    printf(".'\\   /`.");
    linhaCol(5, 75);
    printf(".'.-.`-'.-.`.");
    linhaCol(6, 70);
    printf("..._:   .-. .-.   :_...");
    linhaCol(7, 68);
    printf(".'    '-.(");
    textColor(CYAN, _MAGENTA);
    printf("o");
    textColor(BLACK, _MAGENTA);
    printf(" ) (");
    textColor(CYAN, _MAGENTA);
    printf("o");
    textColor(BLACK, _MAGENTA);
    printf(" ).-'    `.");
    linhaCol(8, 67);
    printf("|  _    _ _`~(_)~`_ _    _  |");
    linhaCol(9, 66);
    printf("|  /:   ' .-=_   _=-. `   ;\\  |");
    linhaCol(10, 66);
    printf("|   :|-.._  '     `  _..-|:   |");
    linhaCol(11, 67);
    printf("|   `:| |`:-:-.-:-:'| |:'   |");
    linhaCol(12, 68);
    printf("`.   `.| | | | | | |.'   .'");
    linhaCol(13, 70);
    printf("`.   `-:_| | |_:-'   .'");
    SetConsoleTextAttribute(hConsole, saved_attributes);

    // Letra P
    Sleep(tempo);
    textColor(MAGENTA, BLACK);
    linhaCol(16, 59);
    printf("%c%c%c%c", TEXTURA, TEXTURA, TEXTURA, TEXTURA);
    linhaCol(19, 59);
    printf("%c%c%c%c", TEXTURA, TEXTURA, TEXTURA, TEXTURA);

    for (int i = 0; i < 7; i++)
    {
        linhaCol(16 + i, 58);
        printf("%c", TEXTURA);
    }

    for (int i = 0; i < 7; i++)
    {
        linhaCol(16 + i, 59);
        printf("%c", TEXTURA);
    }

    linhaCol(16, 61);
    printf("%c", TEXTURA);

    for (int i = 0; i < 2; i++)
    {
        linhaCol(17 + i, 62);
        printf("%c%c", TEXTURA, TEXTURA);
    }
    linhaCol(42, 1);
    SetConsoleTextAttribute(hConsole, saved_attributes);

    // Letra A
    Sleep(tempo);
    textColor(BROWN, _BLACK);
    linhaCol(16, 68);
    printf("%c%c%c", TEXTURA, TEXTURA, TEXTURA);
    linhaCol(19, 68);
    printf("%c%c%c", TEXTURA, TEXTURA, TEXTURA);

    for (int i = 0; i < 6; i++)
    {
        linhaCol(17 + i, 67);
        printf("%c", TEXTURA);
    }

    for (int i = 0; i < 7; i++)
    {
        linhaCol(16 + i, 68);
        printf("%c", TEXTURA);
    }

    for (int i = 0; i < 7; i++)
    {
        linhaCol(16 + i, 71);
        printf("%c", TEXTURA);
    }

    for (int i = 0; i < 6; i++)
    {
        linhaCol(17 + i, 72);
        printf("%c", TEXTURA);
    }
    linhaCol(42, 1);
    SetConsoleTextAttribute(hConsole, saved_attributes);

    // Letra R
    Sleep(tempo);
    textColor(GREEN, _BLACK);
    linhaCol(16, 77);
    printf("%c%c%c", TEXTURA, TEXTURA, TEXTURA);
    linhaCol(19, 77);
    printf("%c%c%c", TEXTURA, TEXTURA, TEXTURA);

    for (int i = 0; i < 6; i++)
    {
        linhaCol(17 + i, 77);
        printf("%c", TEXTURA);
    }

    for (int i = 0; i < 7; i++)
    {
        linhaCol(16 + i, 76);
        printf("%c", TEXTURA);
    }

    linhaCol(20, 79);
    printf("%c", TEXTURA);
    linhaCol(21, 80);
    printf("%c", TEXTURA);

    for (int i = 0; i < 7; i++)
    {
        if (i != 4 && i != 5 && i != 6)
        {
            linhaCol(16 + i, 80);
            printf("%c", TEXTURA);
        }
    }

    linhaCol(17, 81);
    printf("%c", TEXTURA);
    linhaCol(18, 81);
    printf("%c", TEXTURA);
    linhaCol(22, 80);
    printf("%c%c", TEXTURA, TEXTURA);
    linhaCol(42, 1);
    SetConsoleTextAttribute(hConsole, saved_attributes);

    // Letra A
    Sleep(tempo);
    textColor(BROWN, _BLACK);
    linhaCol(16, 86);
    printf("%c%c%c", TEXTURA, TEXTURA, TEXTURA);
    linhaCol(19, 86);
    printf("%c%c%c", TEXTURA, TEXTURA, TEXTURA);

    for (int i = 0; i < 6; i++)
    {
        linhaCol(17 + i, 85);
        printf("%c", TEXTURA);
    }

    for (int i = 0; i < 7; i++)
    {
        linhaCol(16 + i, 86);
        printf("%c", TEXTURA);
    }

    for (int i = 0; i < 7; i++)
    {
        linhaCol(16 + i, 89);
        printf("%c", TEXTURA);
    }

    for (int i = 0; i < 6; i++)
    {
        linhaCol(17 + i, 90);
        printf("%c", TEXTURA);
    }
    linhaCol(42, 1);
    SetConsoleTextAttribute(hConsole, saved_attributes);

    // Letra D
    Sleep(tempo);
    textColor(BLUE, _BLACK);
    linhaCol(16, 95);
    printf("%c%c%c", TEXTURA, TEXTURA, TEXTURA);
    linhaCol(22, 95);
    printf("%c%c%c", TEXTURA, TEXTURA, TEXTURA);

    linhaCol(17, 98);
    printf("%c", TEXTURA);
    linhaCol(18, 98);
    printf("%c", TEXTURA);

    for (int i = 0; i < 7; i++)
    {
        linhaCol(16 + i, 94);
        printf("%c", TEXTURA);
    }

    for (int i = 0; i < 7; i++)
    {
        linhaCol(16 + i, 95);
        printf("%c", TEXTURA);
    }

    for (int i = 0; i < 3; i++)
    {
        linhaCol(19 + i, 98);
        printf("%c", TEXTURA);
    }
    linhaCol(42, 1);
    SetConsoleTextAttribute(hConsole, saved_attributes);

    // Letra E
    Sleep(tempo);
    textColor(RED, _BLACK);
    linhaCol(16, 103);
    printf("%c%c%c", TEXTURA, TEXTURA, TEXTURA);
    linhaCol(19, 103);
    printf("%c%c%c", TEXTURA, TEXTURA, TEXTURA);
    linhaCol(22, 103);
    printf("%c%c%c", TEXTURA, TEXTURA, TEXTURA);

    for (int i = 0; i < 7; i++)
    {
        linhaCol(16 + i, 102);
        printf("%c", TEXTURA);
    }
    for (int i = 0; i < 6; i++)
    {
        linhaCol(16 + i, 103);
        printf("%c", TEXTURA);
    }

    linhaCol(16, 103);
    printf("%c", TEXTURA);
    linhaCol(42, 1);
    SetConsoleTextAttribute(hConsole, saved_attributes);

    // Opções
    linhaCol(27, 77);
    printf("Iniciar o Jogo");
    linhaCol(30, 77);
    printf("Manual do Jogo");

    textColor(MAGENTA, _BLACK);
    linhaCol(39, 28);
    printf("[ESC] - Sair?");
    linhaCol(38, 121);
    printf("[ALT + ENTER]");
    linhaCol(39, 119);
    printf("Janela/Tela cheia");
    SetConsoleTextAttribute(hConsole, saved_attributes);
    linhaCol(1, 1);
}

// comentada
int indicador(int indice)
{
    // Função de Interface
    /*Função usada no menu para imprimir o indicador de qual a opção selecionada com base no parâmetro índice
        0 -> Novo Jogo
        1 -> Instruções
    */
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
    WORD saved_attributes;

    /* Salvar estado atual */
    GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
    saved_attributes = consoleInfo.wAttributes;

    if (indice < 0 || indice > 2)
        return 0;

    // Se o índice for 0, o indicador é imprimido nas coordenadas dadas na função "linhaCol". O mesmo para índice = 1;
    textColor(MAGENTA, _BLACK);
    switch (indice)
    {
    case 0:
        linhaCol(27, 74);
        printf("%c%c", 175, 175);
        linhaCol(30, 74);
        printf("  ");
        linhaCol(33, 74);
        printf("  ");
        linhaCol(42, 1);
        return 1;
    case 1:
        linhaCol(27, 74);
        printf("  ");
        linhaCol(30, 74);
        printf("%c%c", SETAS_DUPLAS, SETAS_DUPLAS);
        linhaCol(33, 74);
        printf("  ");
        linhaCol(42, 1);
        return 1;
    }
    SetConsoleTextAttribute(hConsole, saved_attributes);
}

// comentada
int escolhaMenu(int indice)
{
    /* Função de chamada de funções
    Função usada no menu para chamar as funções do jogo, instruções ou finalizar o programa dependendo da
    opcão escolhida pelo jogador.
    */
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
    WORD saved_attributes;

    /* Salvar estado atual */
    GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
    saved_attributes = consoleInfo.wAttributes;

    // Criei um inteiro para receber a tecla digitada e chamei a função "indicador" para imprimir na tela o indicador rsrs.
    int tecla;
    textColor(MAGENTA, _BLACK);
    indicador(indice);

    // Loop que finaliza quando o jogador digita a tecla "Enter (13)".
    do
    { // Enter
        do
        {
            tecla = getch();
            fflush(stdin);
        } while (tecla != ESC && tecla != ENTER && tecla != ARROW_CIMA && tecla != ARROW_BAIXO); // alterna o indicador

        // Se a tecla precionada for o "Esc (27)", chama a função "question" que imprime na tela uma caixa de texto perguntando se o jogador quer sair do jogo.
        if (tecla == 27)
        {
            SetConsoleTextAttribute(hConsole, saved_attributes);
            if (question() == 0)
                // Se der false -> imprime o menu novamente, agora sem temporizador.
                menu(0);
            else
                // Se der true -> o programa finaliza
                return -1;
        }
        // Se a tecla pressionada for a seta para baixo e o inteiro indice for 0, ele incrementa.
        if (tecla == ARROW_BAIXO && indice < 1)
        {
            indice++;
        }
        // Se a tecla pressionada for a seta para cima e o indice for 1, ele decrementa.
        if (tecla == ARROW_CIMA && indice > 0)
        {
            indice--;
        }
        // chama a função indicador para imprimir novamente o indicador de opção
        indicador(indice);
    } while (tecla != ENTER);
    // retorna o indice e volta à cor padrão
    SetConsoleTextAttribute(hConsole, saved_attributes);
    return indice;
}

// comentada
void chamarJogo(int indice)
{
    /*Função de chamada de funções:
    Essa função recebe um inteiro [0 ou 1] passado pela função escolhaMenu:
        0 -> significa que o jogador escolheu a primeira opção do menu para
        começar um novo jogo.
        1 -> significa que o jogador escolheu a segunda opção do meunu para
        ver as instruções. */

    // criei um switch para chara as funções de acordo com o inteiro passado como parâmetro
    switch (indice)
    {
    case 0:
        // chama a função carregando
        // carregando();
        // limpa a tela
        system("cls");
        // aqui, usei a função box 4 vezes para imprimir as caixas das respectivas divisões do jogo:
        box(2, 25, 42, 138);  // box exterior
        box(29, 25, 42, 138); // box da mão
        box(2, 25, 29, 110);  // box da mesa
        box(43, 25, 69, 138); // box da coleçao

        partida();
        break;
    case 1:
        // limpa a tela e imprime as instruções
        system("cls");
        manual(0);
        // chama a função menu, para imprimir o menu do jogo
        menu(0);
        // uso da recursividade!
        chamarJogo(escolhaMenu(0));
        break;
    }
}

// comentada
void carregando()
{
    /* Função de Interface:
    Essa função é meramente visual, criada para imprimir uma tela de carregamento de jogo */

    /*criamos dois inteiro:
        *contador -> criei ele para receber um número aleatório e ser usado dentro da função
        Sleep, passando a ideia de que o jogo estaria de fato carregando.
        *col -> criado para receber o somatorio de colunas, que quando usado dentro da função linhaCol,
        dentro do for, imprimiria o texto passado nas coordenadas (x, y+col). */
    int contador = 0, col = 0;

    // criei uma caixa
    box(2, 25, 41, 138);
    // usei a combinação de funções linhaCol+printf
    linhaCol(24, 76);
    printf("CARREGANDO");

    // criei um for de 0 à 9, para imprimir 9 bloquinhos
    for (int i = 0; i < 9; i++)
    {
        // o contador recebe o resto da divisão de um número aleatório por 1000, + 500 (número para ser usado na função Sleep)
        contador = (rand() % 1000) + 500;
        // imprime o bloquinho
        linhaCol(25, 72 + col);
        printf("%c", 254);
        // delay de "contador" milissegundos
        Sleep(contador);
        // col(o somatorio de colunas) incrementa em 2
        col += 2;
    }
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

    // criei um switch para chamarmos as funções de acordo com o inteiro dado como parâmetro
    switch (tipoVitoria)
    {
    case 0:
        // chama a função para colocar as últimas duas cartas da mão do jogador em sua coleção
        colocarDuasCartasGaleria(jogador);
        // chama a função de interface para imprimir a tela de vitoria por pontuação
        vitoriaPontuacao(compararPontuacoes(jogador, computador));
        break;
    case 1:
        // chama a função de interface para imprimir a tela de vitoria normal, por colecao vazia
        vitoriaNormal();
        break;
    case 2:
        // chama a função de interface para imprimir a tela de vitoria perfeita
        vitoriaPerfeita();
        break;
    }
    Sleep(2500);
    system("cls");
    menu(0);
    chamarJogo(escolhaMenu(0));
    return 1;
}

// comentada
void vitoriaPontuacao(int pontuacao)
{
    /* Função de Interface:
    Essa é a função que imprime a tela de PONTUACAO, quando o jogador termina o jogo sem coletar
    todos os tipos de naipes possíveis em sua coleção. */
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
    WORD saved_attributes;

    /* Salvar estado atual */
    GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
    saved_attributes = consoleInfo.wAttributes;

    // chama a função para limpar a tela do terminal;
    system("cls");
    // a função box cria uma caixa com as coordenadas da seguinte forma (1º linha, 1º coluna, 2º linha, 2º coluna);
    box(2, 25, 42, 138); // box exterior

    /* Aqui eu organizei uma arte em ascii de uma cenoura, simbolizando a vitória perfeita. Eu combinei a função
    linhaCol, que leva o cursor para as coordenadas dadas como parâmetros da função, com a função printf.
    Apesar de parecer confuso, é bem simples de entender se você observar com calma. */

    textColor(BROWN, _BLACK);
    linhaCol(10, 74);
    printf("___");
    textColor(GREEN, _BLACK);
    linhaCol(11, 66);
    printf("`-._\\ ");
    textColor(BROWN, _BLACK);
    printf("/     `~~'--.,_");
    textColor(GREEN, _BLACK);
    linhaCol(12, 64);
    printf("------>");
    textColor(BROWN, _BLACK);
    printf("|              `~~'--.,_");
    textColor(GREEN, _BLACK);
    linhaCol(13, 65);
    printf("_.-'/ ");
    textColor(BROWN, _BLACK);
    printf("'.____,,,,----'''~~```'");

    // os próximos passos são semelhantes às outras funçõe sde imprimir a tela final
    SetConsoleTextAttribute(hConsole, saved_attributes);
    linhaCol(18, 69);
    printf("| RECEBA SUA CENOURA |");

    box(20, 52, 27, 106);
    linhaCol(22, 57);
    printf("Nada Mal! Voc%c conseguiu finalizar o jogo sem", E_COM_TIL);
    linhaCol(23, 65);
    printf("coletar todos os");
    textColor(RED, _BLACK);
    printf(" NAIPES");
    SetConsoleTextAttribute(hConsole, saved_attributes);
    printf(" com uma");
    linhaCol(24, 71);
    printf(" pontua%c%co de: ", CEDILHA, A_COM_TIL);
    textColor(CYAN, _BLACK);
    printf("%d", pontuacao);
    SetConsoleTextAttribute(hConsole, saved_attributes);
    linhaCol(25, 68);
    printf("Aproveite sua vitamina A!");
    linhaCol(31, 74);
    printf("F");
    Sleep(900);
    printf("i");
    Sleep(900);
    printf("m");
    Sleep(900);
    printf(" d");
    Sleep(900);
    printf("e");
    Sleep(900);
    printf(" J");
    Sleep(900);
    printf("o");
    Sleep(900);
    printf("g");
    Sleep(900);
    printf("o");
    Sleep(900);
    printf("!");
    Sleep(900);
    linhaCol(42, 1);
}

// comentada
void vitoriaPerfeita()
{
    /* Função de Interface:
    Essa é a função que imprime a tela de VITÓRIA PERFEITA, quando o jogador termina o jogo, no caso
    zera o baralho, sem nenhuma carta em sua coleção e com no mínimo dois zeros em sua mão. */

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
    WORD saved_attributes;

    /* Salvar estado atual */
    GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
    saved_attributes = consoleInfo.wAttributes;

    // chama a função para limpar a tela do terminal;
    system("cls");
    // a função box cria uma caixa com as coordenadas da seguinte forma (1º linha, 1º coluna, 2º linha, 2º coluna);
    box(2, 25, 42, 138); // box exterior;
    // define a cor do texto como MARROM/AMARELA e a cor de fundo PRETA;
    textColor(BROWN, _BLACK);
    /* Aqui eu organizei uma arte em ascii de dois trófeus, simbolizando a vitória perfeita. Eu combinei a função
    linhaCol, que leva o cursor para as coordenadas dadas como parâmetros da função, com a função printf.
    Apesar de parecer confuso, é bem simples de entender se você observar com calma. */
    linhaCol(7, 64);
    printf("___________");
    linhaCol(8, 63);
    printf("'._==_==_=_.'");
    linhaCol(9, 63);
    printf(".-\\:      /-.");
    linhaCol(10, 62);
    printf("| (|:.     |) |");
    linhaCol(11, 63);
    printf("'-|:.     |-'");
    linhaCol(12, 65);
    printf("\\::.    /");
    linhaCol(13, 66);
    printf("'::. .'");
    linhaCol(14, 68);
    printf(") (");
    linhaCol(15, 66);
    printf("_.' '._");
    linhaCol(16, 65);
    printf("#########");
    // segundo troféu
    linhaCol(7, 85);
    printf("___________"); //+15
    linhaCol(8, 84);
    printf("'._==_==_=_.'");
    linhaCol(9, 84);
    printf(".-\\:      /-.");
    linhaCol(10, 83);
    printf("| (|:.     |) |");
    linhaCol(11, 84);
    printf("'-|:.     |-'");
    linhaCol(12, 86);
    printf("\\::.    /");
    linhaCol(13, 87);
    printf("'::. .'");
    linhaCol(14, 89);
    printf(") (");
    linhaCol(15, 87);
    printf("_.' '._");
    linhaCol(16, 86);
    printf("#########");
    // retornei para a cor do texto BRANCA e o fundo PRETO;
    SetConsoleTextAttribute(hConsole, saved_attributes);
    // imprimi o texto na coordenada (18,51) usando a função linhaCol;
    linhaCol(18, 71);
    printf("| PERFECT VICTORY |");

    // aqui criei outra caixa com a função box
    box(20, 52, 26, 106);

    /*atribui a função setlocale para conseguir usar acentuação no terminal, porém, por algum motivo que
    desconheço, no meu Dev C++ não funcionou. Mas eu deixei mesmo assim caso o problema fosse só aqui no meu
    notebook. */
    // setlocale(LC_ALL, "Portuguese");
    // mais uma vez combinei as funções linhaCol e printf para imprimir no local que eu queria
    linhaCol(22, 57);
    printf("Voc%c conseguiu o imposs%cvel! Finalizou o jogo", E_COM_TIL, I_COM_ACENTO);
    linhaCol(23, 56);
    printf("com ao menos 2 zeros e nenhuma carta na");
    // defini a cor de texto como VERMELHA e a de fundo, PRETA
    textColor(RED, _BLACK);
    // mais uma impressão
    printf(" GALERIA");
    // retornei à cor de texto BRANCA e fundo PRETO
    SetConsoleTextAttribute(hConsole, saved_attributes);
    printf(".");
    linhaCol(24, 68);
    printf("Devia tentar a loteria!");
    linhaCol(29, 74);
    // aqui fui intercalando as impressões com um tempo de 900 milisegundos
    printf("F");
    Sleep(900);
    printf("i");
    Sleep(900);
    printf("m");
    Sleep(900);
    printf(" d");
    Sleep(900);
    printf("e");
    Sleep(900);
    printf(" J");
    Sleep(900);
    printf("o");
    Sleep(900);
    printf("g");
    Sleep(900);
    printf("o");
    Sleep(900);
    printf("!");
    Sleep(900);
    //"desfiz" o setlocale anteriormente para não "bugar" as demais impressões do programa
    // setlocale(LC_ALL, "C");
    // levei o cursor para a coordenada dada apenas por questão estética
    linhaCol(42, 1);
}

// comentada
void vitoriaNormal()
{
    /* Função de Interface:
    Essa é a função que imprime a tela de VITÓRIA, quando o jogador termina o jogo, no caso
    zera o baralho, sem nenhuma carta em sua coleção. */

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
    WORD saved_attributes;

    /* Salvar estado atual */
    GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
    saved_attributes = consoleInfo.wAttributes;

    // chama a função para limpar a tela do terminal;
    system("cls");
    // a função box cria uma caixa com as coordenadas da seguinte forma (1º linha, 1º coluna, 2º linha, 2º coluna);
    box(2, 25, 42, 138); // box exterior;
    // define a cor do texto como MARROM/AMARELA e a cor de fundo PRETA;
    textColor(BROWN, _BLACK);
    /* Aqui eu organizei uma arte em ascii de um trófeu, simbolizando a vitória. Eu combinei a função
    linhaCol, que leva o cursor para as coordenadas dadas como parâmetros da função, com a função printf.
    Apesar de parecer confuso, é bem simples de entender se você observar com calma. */
    linhaCol(7, 74);
    printf("___________");
    linhaCol(8, 73);
    printf("'._==_==_=_.'");
    linhaCol(9, 73);
    printf(".-\\:      /-.");
    linhaCol(10, 72);
    printf("| (|:.     |) |");
    linhaCol(11, 73);
    printf("'-|:.     |-'");
    linhaCol(12, 75);
    printf("\\::.    /");
    linhaCol(13, 76);
    printf("'::. .'");
    linhaCol(14, 78);
    printf(") (");
    linhaCol(15, 76);
    printf("_.' '._");
    linhaCol(16, 75);
    printf("#########");
    // retornei para a cor do texto BRANCA e o fundo PRETO;
    SetConsoleTextAttribute(hConsole, saved_attributes);
    // imprimi o texto na coordenada (18,54) usando a função linhaCol;
    linhaCol(18, 74);
    printf("| VICTORY |");

    // aqui criei outra caixa com a função box
    box(20, 52, 26, 106);
    /*atribui a função setlocale para conseguir usar acentuação no terminal, porém, por algum motivo que
    desconheço, no meu Dev C++ não funcionou. Mas eu deixei mesmo assim caso o problema fosse só aqui no meu
    notebook. */
    // setlocale(LC_ALL, "Portuguese");
    // mais uma vez combinei as funções linhaCol e printf para imprimir no local que eu queria
    linhaCol(22, 57);
    printf("Well Done! Voce conseguiu finalizar o jogo sem");
    linhaCol(23, 68);
    printf("nenhuma carta na");
    // defini a cor de texto como VERMELHA e a de fundo, PRETA
    textColor(RED, _BLACK);
    // mais uma impressão
    printf(" Galeria");
    // retornei à cor de texto BRANCA e fundo PRETO
    SetConsoleTextAttribute(hConsole, saved_attributes);
    // mais combinações linhaCol+printf
    printf(".");
    linhaCol(24, 72);
    printf("Congratulations!");
    linhaCol(29, 74);
    // aqui fui intercalando as impressões com um tempo de 900 milisegundos
    printf("F");
    Sleep(900);
    printf("i");
    Sleep(900);
    printf("m");
    Sleep(900);
    printf(" d");
    Sleep(900);
    printf("e");
    Sleep(900);
    printf(" J");
    Sleep(900);
    printf("o");
    Sleep(900);
    printf("g");
    Sleep(900);
    printf("o");
    Sleep(900);
    printf("!");
    Sleep(900);
    //"desfiz" o setlocale anteriormente para não "bugar" as demais impressões do programa
    // setlocale(LC_ALL, "C");
    // levei o cursor para a coordenada dada apenas por questão estética
    linhaCol(42, 1);
}

// comentada
void derrota()
{
    /* Função de Interface:
    Essa é a função que imprime a tela de DERROTA, quando o jogador não consegue terminar o jogo
    pois coletou todos os naipes em sua coleção. */

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
    WORD saved_attributes;

    /* Salvar estado atual */
    GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
    saved_attributes = consoleInfo.wAttributes;

    // chama a função para limpar a tela do terminal;
    system("cls");
    // a função box cria uma caixa com as coordenadas da seguinte forma (1º linha, 1º coluna, 2º linha, 2º coluna);
    box(2, 25, 42, 138); // box exterior

    // defini a cor de texto como VERMELHA e a de fundo, PRETA
    textColor(RED, _BLACK);
    /*Aqui usei a combinação das funções linhaCol+textColor+printf para conseguir imprimir na tela uma "Ascii Art" de
    um palhaço.
        *A função linCol leva o cursor para a coordenada dada como parâmetros da função;
        *A função textColor modifica a cor de texto e de fundo da seguinte forma (Cor_do_texto, Cor_de_fundo). Utilizei
        um enum para nomear as cores disponíveis.*/
    linhaCol(10, 36);
    printf("0_");
    linhaCol(11, 37);
    printf("\\`.");
    linhaCol(12, 38);
    printf("\\ \\   / __>0");
    linhaCol(13, 34);
    printf("/\\  /  |/' /");
    linhaCol(14, 33);
    printf("/  \\/   `  ,`'--.");
    linhaCol(15, 32);
    printf("/ /(___________)_ \\");
    linhaCol(16, 32);
    printf("|/ ");
    textColor(WHITE, _BLACK);
    printf("//.-.   .-.\\");
    textColor(RED, _BLACK);
    printf(" \\ \\");
    linhaCol(17, 32);
    printf("0 ");
    textColor(WHITE, _BLACK);
    printf("// :@ ");
    textColor(RED, _BLACK);
    printf("___");
    textColor(WHITE, _BLACK);
    printf(" @: \\");
    textColor(RED, _BLACK);
    printf(" \\/");
    textColor(WHITE, _BLACK);
    linhaCol(18, 34);
    printf("( o ^");
    textColor(RED, _BLACK);
    printf("(___)");
    textColor(WHITE, _BLACK);
    printf("^ o )");
    textColor(RED, _BLACK);
    printf(" 0");
    textColor(WHITE, _BLACK);
    linhaCol(19, 35);
    printf("\\ \\_______/ /");
    linhaCol(20, 31);
    printf("/\\   '._______.'");
    textColor(BLUE, _BLACK);
    printf("--.");
    textColor(WHITE, _BLACK);
    linhaCol(21, 31);
    printf("\\ /|  ");
    textColor(BLUE, _BLACK);
    printf("|");
    textColor(WHITE, _BLACK);
    printf("<_____>");
    textColor(BLUE, _BLACK);
    printf("    |");
    textColor(WHITE, _BLACK);
    linhaCol(22, 32);
    printf("\\ \\__");
    textColor(BLUE, _BLACK);
    printf("|");
    textColor(WHITE, _BLACK);
    printf("<_____>____/|__");
    linhaCol(23, 33);
    printf("\\____<_____>_______/");
    textColor(BLUE, _BLACK);
    linhaCol(24, 37);
    printf("|");
    textColor(WHITE, _BLACK);
    printf("<_____>");
    textColor(BLUE, _BLACK);
    printf("    |");
    linhaCol(25, 37);
    printf("|");
    textColor(WHITE, _BLACK);
    printf("<_____>");
    textColor(BLUE, _BLACK);
    printf("    |");
    linhaCol(26, 37);
    printf(":");
    textColor(WHITE, _BLACK);
    printf("<_____>");
    textColor(BLUE, _BLACK);
    printf("____:");
    linhaCol(27, 36);
    printf("/");
    textColor(WHITE, _BLACK);
    printf(" <_____>");
    textColor(BLUE, _BLACK);
    printf("   /|");
    linhaCol(28, 35);
    printf("/");
    textColor(WHITE, _BLACK);
    printf("  <_____>");
    textColor(BLUE, _BLACK);
    printf("  / |");
    textColor(BLUE, _BLACK);
    linhaCol(29, 34);
    printf("/___________/  |");
    linhaCol(30, 34);
    printf("|           | _|");
    linhaCol(31, 34);
    printf("|           | ---||_");
    linhaCol(32, 34);
    printf("|   |L\\/|/  |  | [__]");
    linhaCol(33, 34);
    printf("|  \\|||\\|\\  |  /");
    linhaCol(34, 34);
    printf("|           | /");
    linhaCol(35, 34);
    printf("|___________|/");

    // retornei à cor de texto BRANCA e fundo PRETO
    SetConsoleTextAttribute(hConsole, saved_attributes);
    // imprimi o texto na coordenada (18,60) usando a função linhaCol;
    linhaCol(18, 80);
    printf("| RECEBA SEU NULL |");

    // aqui criei outra caixa com a função box
    box(20, 62, 27, 116); // altura = 7, largura = 54

    /*atribui a função setlocale para conseguir usar acentuação no terminal, porém, por algum motivo que
    desconheço, no meu Dev C++ não funcionou. Mas eu deixei mesmo assim caso o problema fosse só aqui no meu
    notebook. */
    // setlocale(LC_ALL, "Portuguese");
    // mais uma vez combinei as funções linhaCol e printf para imprimir no local que eu queria
    linhaCol(22, 67);
    printf(" DERROTA! Voce nao conseguiu finalizar o jogo");
    linhaCol(23, 74);
    printf(" pois coletou todos os");
    textColor(RED, _BLACK);
    printf(" NAIPES");
    SetConsoleTextAttribute(hConsole, saved_attributes);
    printf("!");
    linhaCol(25, 74);
    printf("A sorte nao esteve a seu favor!");
    linhaCol(31, 84);
    // aqui fui intercalando as impressões com um tempo de 900 milisegundos
    printf("F");
    Sleep(900);
    printf("i");
    Sleep(900);
    printf("m");
    Sleep(900);
    printf(" d");
    Sleep(900);
    printf("e");
    Sleep(900);
    printf(" J");
    Sleep(900);
    printf("o");
    Sleep(900);
    printf("g");
    Sleep(900);
    printf("o");
    Sleep(900);
    printf("!");
    Sleep(900);
    //"desfiz" o setlocale anteriormente para não "bugar" as demais impressões do programa
    // setlocale(LC_ALL, "C");
    // levei o cursor para a coordenada dada apenas por questão estética
    linhaCol(42, 1);
}

// comentada
void corDaVez(int vezJogador)
{

    /* Função de Interface:
    Basicamente, ela muda a cor da plaquinha do jogador e do computador
    dependendo de quem é a vez da jogada. Quem joga fica com a plaquinha
    na cor vermelha.

    Como parâmetros da função, coloquei apenas dois inteiros [0 ou 1]. Um para o jogador e outro
    para o computador. */

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
    WORD saved_attributes;

    /* Salvar estado atual */
    GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
    saved_attributes = consoleInfo.wAttributes;

    if (vezJogador)
    {
        // define o texto na cor PRETA e o fundo na cor VERMELHA!
        textColor(BLACK, _RED);
        // a funcao linhaCol leva o cursor para as coordenadas (15,96) e imprime na tela o printf
        linhaCol(15, 116);
        printf("    COMPUTADOR    ");
        // essa função retorna ao estado salvo anteriormente, que seria o texto na cor BRANCA e o fundo PRETO
        SetConsoleTextAttribute(hConsole, saved_attributes);
        // aqui coloquei o curso nessa coordenada apenas por perfeição estética
        linhaCol(42, 1);

        // define o texto na cor PRETA e o fundo na cor VERDE!
        textColor(BLACK, _GREEN);
        // a funcao linhaCol leva o cursor para as coordenadas (42,95) e imprime na tela o printf
        linhaCol(42, 115);
        printf("      JOGADOR      ");
        // essa função retorna ao estado salvo anteriormente, que seria o texto na cor BRANCA e o fundo PRETO
        SetConsoleTextAttribute(hConsole, saved_attributes);
        // aqui coloquei o curso nessa coordenada apenas por perfeição estética
        linhaCol(42, 1);
    }
    else
    {
        // define o texto na cor PRETA e o fundo na cor VERDE!
        textColor(BLACK, _GREEN);
        // a funcao linhaCol leva o cursor para as coordenadas (15,96) e imprime na tela o printf
        linhaCol(15, 116);
        printf("    COMPUTADOR    ");
        // essa função retorna ao estado salvo anteriormente, que seria o texto na cor BRANCA e o fundo PRETO
        SetConsoleTextAttribute(hConsole, saved_attributes);
        // aqui coloquei o curso nessa coordenada apenas por perfeição estética
        linhaCol(42, 1);

        // define o texto na cor PRETA e o fundo na cor VERMELHA!
        textColor(BLACK, _RED);
        // a funcao linhaCol leva o cursor para as coordenadas (42,95) e imprime na tela o printf
        linhaCol(42, 115);
        printf("      JOGADOR      ");
        // essa função retorna ao estado salvo anteriormente, que seria o texto na cor BRANCA e o fundo PRETO
        SetConsoleTextAttribute(hConsole, saved_attributes);
        // aqui coloquei o curso nessa coordenada apenas por perfeição estética
        linhaCol(42, 1);
    }
}

void manual(int tela)
{

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
    WORD saved_attributes;

    /* Salvar estado atual */
    GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
    saved_attributes = consoleInfo.wAttributes;

    // Box exterior
    box(2, 25, 41, 138);

    int tecla;

    // primeiro gatinho
    textColor(YELLOW, _BLACK);
    linhaCol(10, 32);
    printf("^~^  ,");
    linhaCol(11, 31);
    printf("('Y') ),"); //-1
    linhaCol(12, 31);
    printf("/   \\/");
    linhaCol(13, 30);
    printf("(\\|||/)"); //-2

    // segundo gatinho
    linhaCol(7, 42);
    printf("\\    /\\");
    linhaCol(8, 43);
    printf(")  ( ')"); //+1
    linhaCol(9, 42);
    printf("(  /  )");
    linhaCol(10, 43);
    printf("\(__)|"); //+1

    // M
    textColor(LIGHTMAGENTA, _BLACK);
    linhaCol(6, 63);
    printf("%c   %c%c", TEXTURA, TEXTURA, TEXTURA);
    linhaCol(7, 63);
    printf("%c%c %c%c%c", TEXTURA, TEXTURA, TEXTURA, TEXTURA, TEXTURA);
    linhaCol(8, 63);
    printf("%c %c %c%c", TEXTURA, TEXTURA, TEXTURA, TEXTURA);
    linhaCol(9, 63);
    printf("%c   %c%c", TEXTURA, TEXTURA, TEXTURA);

    // A
    linhaCol(6, 71);
    printf(" %c%c%c", TEXTURA, TEXTURA, TEXTURA);
    linhaCol(7, 71);
    printf("%c %c%c", TEXTURA, TEXTURA, TEXTURA);
    linhaCol(8, 71);
    printf("%c%c%c%c", TEXTURA, TEXTURA, TEXTURA, TEXTURA);
    linhaCol(9, 71);
    printf("%c %c%c", TEXTURA, TEXTURA, TEXTURA);

    // N
    linhaCol(6, 77);
    printf("%c  %c%c", TEXTURA, TEXTURA, TEXTURA);
    linhaCol(7, 77);
    printf("%c%c %c%c", TEXTURA, TEXTURA, TEXTURA, TEXTURA);
    linhaCol(8, 77);
    printf("%c %c%c%c", TEXTURA, TEXTURA, TEXTURA, TEXTURA);
    linhaCol(9, 77);
    printf("%c  %c%c", TEXTURA, TEXTURA, TEXTURA);

    // U
    linhaCol(6, 84);
    printf("%c  %c%c", TEXTURA, TEXTURA, TEXTURA);
    linhaCol(7, 84);
    printf("%c  %c%c", TEXTURA, TEXTURA, TEXTURA);
    linhaCol(8, 84);
    printf("%c  %c%c", TEXTURA, TEXTURA, TEXTURA);
    linhaCol(9, 84);
    printf("%c%c%c%c", TEXTURA, TEXTURA, TEXTURA, TEXTURA);

    // A
    linhaCol(6, 91);
    printf(" %c%c%c", TEXTURA, TEXTURA, TEXTURA);
    linhaCol(7, 91);
    printf("%c %c%c", TEXTURA, TEXTURA, TEXTURA);
    linhaCol(8, 91);
    printf("%c%c%c%c", TEXTURA, TEXTURA, TEXTURA, TEXTURA);
    linhaCol(9, 91);
    printf("%c %c%c", TEXTURA, TEXTURA, TEXTURA);

    // L
    linhaCol(6, 97);
    printf("%c%c", TEXTURA, TEXTURA);
    linhaCol(7, 97);
    printf("%c%c", TEXTURA, TEXTURA);
    linhaCol(8, 97);
    printf("%c%c", TEXTURA, TEXTURA);
    linhaCol(9, 97);
    printf("%c%c%c%c", TEXTURA, TEXTURA, TEXTURA, TEXTURA);

    SetConsoleTextAttribute(hConsole, saved_attributes);

    linhaCol(34, 63);
    printf("[ %c | %c ] - Alternar  [ESC] - Retornar", SETA_ESQUERDA, SETA_DIREITA);
    SetConsoleTextAttribute(hConsole, saved_attributes);

    telas(0);
    escolhaTela(0);
}

void telas(int tela)
{

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
    WORD saved_attributes;

    /* Salvar estado atual */
    GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
    saved_attributes = consoleInfo.wAttributes;

    switch (tela)
    {
    case 0:
        box(15, 32, 30, 132);
        linhaCol(20, 73);
        textColor(LIGHTMAGENTA, _BLACK);
        printf("OBJETIVO DO JOGO");
        SetConsoleTextAttribute(hConsole, saved_attributes);
        linhaCol(23, 34);
        printf("O objetivo em Parade %c ficar com ", E_COM_ACENTO);
        textColor(RED, _BLACK);
        printf("MENOS");
        SetConsoleTextAttribute(hConsole, saved_attributes);
        printf(" pontos no final do jogo. Ele termina em duas situa%c%ces:", CEDILHA, O_COM_TIL);
        linhaCol(24, 42);
        printf("quando voc%c possuir cartas das 6 cores que existem no jogo ou quando", E_COM_TIL);
        linhaCol(25, 72);
        printf("o baralho terminar!");
        linhaCol(31, 79);
        printf("[");
        textColor(CYAN, _BLACK);
        printf("01");
        SetConsoleTextAttribute(hConsole, saved_attributes);
        printf("/04]");
        linhaCol(42, 1);
        break;
    case 1:
        box(15, 32, 30, 132);
        linhaCol(18, 78);
        textColor(LIGHTMAGENTA, _BLACK);
        printf("RODADAS");
        SetConsoleTextAttribute(hConsole, saved_attributes);
        linhaCol(20, 40);
        printf("Em sua vez, o jogador escolhe uma das cartas de sua m%co, que %c colocada no final da", A_COM_TIL, E_COM_ACENTO);
        linhaCol(21, 37);
        printf(" fila sobre a mesa. Em seguida, automaticamente s%co conferidas as cartas que dever%co ser", A_COM_TIL, A_COM_TIL);
        linhaCol(22, 55);
        printf("retiradas da mesa e colocadas em sua cole%c%co/galeria:", CEDILHA, A_COM_TIL);
        linhaCol(23, 38);
        printf("Primeiro as cartas de n%cmero ", U_COM_ACENTO);
        textColor(RED, _BLACK);
        printf("MENOR");
        SetConsoleTextAttribute(hConsole, saved_attributes);
        printf(" ou ");
        textColor(RED, _BLACK);
        printf("IGUAL ");
        SetConsoleTextAttribute(hConsole, saved_attributes);
        printf("a que voc%c jogou e depois as da ", E_COM_TIL);
        textColor(RED, _BLACK);
        printf("MESMA COR");
        SetConsoleTextAttribute(hConsole, saved_attributes);
        printf(",");
        linhaCol(24, 39);
        printf(" que n%co estejam ", A_COM_TIL);
        textColor(RED, _BLACK);
        printf("PROTEGIDAS");
        SetConsoleTextAttribute(hConsole, saved_attributes);
        printf(". O n%cmero da carta jogada protege a mesma quantidade de", U_COM_ACENTO);
        linhaCol(25, 41);
        printf("cartas do final da fila para o in%ccio. Ou seja, se voc%c jogou um 4, as primeiras", I_COM_ACENTO, E_COM_TIL);
        linhaCol(26, 59);
        printf(" quatro cartas do final da fila s%co ignoradas.", A_COM_TIL);
        linhaCol(27, 47);
        printf("Finalmente, o jogador compra uma carta do baralho, finalizando seu turno.");
        linhaCol(31, 79);
        printf("[");
        textColor(CYAN, _BLACK);
        printf("02");
        SetConsoleTextAttribute(hConsole, saved_attributes);
        printf("/04]");
        linhaCol(42, 1);
        break;
    case 2:
        box(15, 32, 30, 132);
        linhaCol(19, 68);
        textColor(LIGHTMAGENTA, _BLACK);
        printf("FINAL DE JOGO E PONTUA%cAO", CEDILHA_MAIUSCULA);
        SetConsoleTextAttribute(hConsole, saved_attributes);
        linhaCol(21, 42);
        printf("Quando o baralho terminar, voc%c joga um %cltimo turno, para que fique com quatro", E_COM_TIL, U_COM_ACENTO);
        linhaCol(22, 42);
        printf(" cartas na m%co. Depois disso, deve escolher ", A_COM_TIL);
        textColor(RED, _BLACK);
        printf("DUAS");
        SetConsoleTextAttribute(hConsole, saved_attributes);
        printf(" cartas para serem colocadas na");
        linhaCol(23, 40);
        printf("cole%c%co/galeria. Caso voc%c n%co tenha ganho o jogo, %c feita a contagem de pontos.",
               CEDILHA, A_COM_TIL, E_COM_TIL, A_COM_TIL, E_COM_ACENTO);
        linhaCol(24, 43);
        printf("Para isso, primeiro s%co comparadasas suas cartas com a do computador. Se voc%c",
               A_COM_TIL, E_COM_TIL);
        linhaCol(25, 50);
        printf("tiver mais cartas de uma determinada cor, cada uma valer%c ", A_COM_ACENTO);
        textColor(RED, _BLACK);
        printf("1 ponto.");
        SetConsoleTextAttribute(hConsole, saved_attributes);
        linhaCol(26, 56);
        printf(" Caso contr%crio, cada uma valer%c o pr%cprio n%cmero.",
               A_COM_ACENTO, A_COM_ACENTO, O_COM_ACENTO, U_COM_ACENTO);
        linhaCol(31, 79);
        printf("[");
        textColor(CYAN, _BLACK);
        printf("03");
        SetConsoleTextAttribute(hConsole, saved_attributes);
        printf("/04]");
        linhaCol(42, 1);
        break;
    case 3:
        box(15, 32, 30, 132);
        linhaCol(18, 72);
        textColor(LIGHTMAGENTA, _BLACK);
        printf("POSSIVEIS FINAIS");
        SetConsoleTextAttribute(hConsole, saved_attributes);
        linhaCol(20, 45);
        textColor(RED, _BLACK);
        printf("DERROTA:");
        SetConsoleTextAttribute(hConsole, saved_attributes);
        printf(" Coletar no m%cnimo uma carta de cada naipe na cole%c%co/galeria.", I_COM_ACENTO, CEDILHA, A_COM_TIL);
        linhaCol(22, 45);
        textColor(RED, _BLACK);
        printf("PONTUA%cAO:", CEDILHA_MAIUSCULA);
        SetConsoleTextAttribute(hConsole, saved_attributes);
        printf(" Zerar o baralho sem ter obtido a DERROTA.");
        linhaCol(24, 45);
        textColor(RED, _BLACK);
        printf("VITORIA:");
        SetConsoleTextAttribute(hConsole, saved_attributes);
        printf(" Zerar o baralho sem coletar nenhuma carta na cole%c%co/galeria.", CEDILHA, A_COM_TIL);
        linhaCol(26, 45);
        textColor(RED, _BLACK);
        printf("VITORIA PERFEITA:");
        SetConsoleTextAttribute(hConsole, saved_attributes);
        printf(" Zerar o baralho sem coletar nenhuma carta e possuir");
        linhaCol(27, 65);
        printf("ao menos duas cartas de n%cmero 0 em sua MAO.", U_COM_ACENTO);
        linhaCol(31, 79);
        printf("[");
        textColor(CYAN, _BLACK);
        printf("04");
        SetConsoleTextAttribute(hConsole, saved_attributes);
        printf("/04]");
        linhaCol(42, 1);
        break;
    }
}
// comentada
void escolhaTela(int indice)
{

    int tecla;
    // loop até o jogador apertar a tecla Esc
    do
    { // ESC
        do
        {
            tecla = getch();
            fflush(stdin);
        } while (tecla != ESC && tecla != ARROW_ESQUERDA && tecla != ARROW_DIREITA); // alternar

        // se a tecla digitada for -> e o indice for menor do que 3, ele incrementa
        if (tecla == ARROW_DIREITA && indice < 4)
            indice++;

        // se a tecla digitada for <- e o indice for maior do que 0, ele decrementa
        else if (tecla == ARROW_ESQUERDA && indice > 0)
            indice--;

        // imprime o indicador novamente
        telas(indice);
    } while (tecla != ESC);
    system("cls");
    menu(0);
    chamarJogo(escolhaMenu(0));
}

void aviso()
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
    WORD saved_attributes;

    /* Salvar estado atual */
    GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
    saved_attributes = consoleInfo.wAttributes;

    box(12, 60, 28, 107);
    textColor(LIGHTMAGENTA, _BLACK);
    linhaCol(14, 81);
    printf("AVISO!");
    SetConsoleTextAttribute(hConsole, saved_attributes);
    linhaCol(16, 67);
    printf("Antes de iniciar o jogo, verifique");
    linhaCol(17, 69);
    printf("a resolução do seu terminal.");
    linhaCol(19, 68);
    textColor(RED, _BLACK);
    printf("LARGURA MÍNIMA RECOMENDADA: 160");
    SetConsoleTextAttribute(hConsole, saved_attributes);
    linhaCol(21, 65);
    printf("Caso as suas configurações de largura");
    linhaCol(22, 67);
    printf("não estejam compatíveis, seu jogo");
    linhaCol(23, 70);
    printf("pode não rodar perfeitamente.");
    linhaCol(24, 75);
    textColor(LIGHTMAGENTA, _BLACK);
    printf("Obrigada e bom jogo!");
    SetConsoleTextAttribute(hConsole, saved_attributes);
    linhaCol(26, 75);
    printf("[ENTER] - Continuar");

    int tecla;

    do
    {
        tecla = getch();
        fflush(stdin);
    } while (tecla != ENTER);
}