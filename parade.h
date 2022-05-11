#include <stdbool.h>

typedef struct carta Carta;
typedef struct baralho Baralho;

#define QTD_MAX_CARTAS 66
#define QTD_NAIPES 6
#define MAIOR_NUMERO_CARTA 10

Carta *criarCarta(int, char);
Baralho *criarBaralho();

bool inserir(Baralho *, Carta *);
bool enfiarCartasNoBaralho(Baralho *);
bool embaralhar(Baralho *);

void imprimirBaralho(Baralho *);