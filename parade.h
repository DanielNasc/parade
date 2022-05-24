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

// LISTA ===========================================

bool inserirInicio(ListaCarta *, Carta *);
bool inicializarMao(ListaCarta *, Baralho *);
bool removerQualquerCartaValida(ListaCarta *, Galeria *, Carta *);
bool removerPorNaipe(ListaCarta *, Carta *);
bool removerPorNumero(ListaCarta *, Carta *);

Carta *primeiraCartaAposBloqueio(ListaCarta *, int);
Carta *removerIndice(ListaCarta *, int);

int quantidadeCartasLista(ListaCarta *);

void imprimirLista(ListaCarta *);

// COLECAO =======================================
bool inicializarGaleria(Galeria *);
bool inserirColecao(Colecao *, Carta *);
bool inserirNaGaleria(Galeria *, Carta *);
int somaValoresColecao(Colecao *);

void imprimirGaleria(Galeria *);

// MESA =======================================
bool inserirFim(ListaCarta *, Carta *);
bool inicializarMesa(ListaCarta *, Baralho *);
