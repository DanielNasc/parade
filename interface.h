#include <stdbool.h>

// Nome da cor da letra
typedef enum cor_letras
{
    BLACK,
    BLUE,
    GREEN,
    CYAN,
    RED,
    MAGENTA,
    BROWN,
    LIGHTGRAY,
    DARKGRAY,
    LIGHTBLUE,
    LIGHTGREEN,
    LIGHTCYAN,
    LIGHTRED,
    LIGHTMAGENTA,
    YELLOW,
    WHITE
} CorLetras;

// Nome da cor do fundo
typedef enum cor_fundo
{
    _BLACK = 0,
    _GREEN = 32,
    _RED = 64,
    _MAGENTA = 80,
    _WHITE = 240
} CorFundo;

// Funções básicas
void imprimeCaixa(int, int, int, int);

// Funções mudança de cor
void corCarta(char);
void corTurno(bool);

// interface ================================================================
void menu(int);