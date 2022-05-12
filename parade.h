#include <stdbool.h>

typedef struct carta Carta;
typedef struct baralho Baralho;

#define QTD_MAX_CARTAS 66
#define QTD_NAIPES 6
#define MAIOR_NUMERO_CARTA 10
#define QTD_LOOPS_EMBARALHAR 200

Carta *criarCarta(int, char);
Baralho *criarBaralho();

bool inserir(Baralho *, Carta *);
bool enfiarCartasNoBaralho(Baralho *);
bool embaralhar(Baralho *);
bool jogarNoMeio(Baralho *, int);

void imprimirBaralho(Baralho *);