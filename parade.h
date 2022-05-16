#include <stdbool.h>
#include <inttypes.h>

typedef struct carta Carta;
typedef struct baralho Baralho;
typedef struct listaCarta ListaCarta;
typedef struct colecao Colecao;
typedef struct galeria Galeria;

#define QTD_MAX_CARTAS 66
#define QTD_NAIPES 6
#define MAIOR_NUMERO_CARTA 10
#define QTD_LOOPS_EMBARALHAR 200
#define QTD_LOOPS_PREENCHER_MAO 5

Carta *criarCarta(int, char);
Baralho *criarBaralho();
ListaCarta *criarLista();
Colecao *criarColecao(char);
Galeria *criarGaleria();

// BARALHO =======================================

bool inserir(Baralho *, Carta *);
bool enfiarCartasNoBaralho(Baralho *);
bool embaralhar(Baralho *);
bool jogarNoMeio(Baralho *, int);

uint8_t tamanhoBaralho(Baralho *);

void imprimirBaralho(Baralho *);

Carta *removerTopo(Baralho *); 

// MAO ===========================================

bool inserirNaMao(ListaCarta *, Baralho *);
bool preencherMaoInicioJogo(ListaCarta *, Baralho *);

void imprimirMao(ListaCarta *mao);

// COLECAO =======================================
bool inicializarGaleria(Galeria *);
