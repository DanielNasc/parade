# Projeto da cadeira de Algoritmos e Estruturas de Dados 1

## Para fazer:

Segundo Roberto, essas são as funções mínimas do TAD para o projeto funcionar. Todas deverão ser implementadas.

### Pilha dinâmica (Baralho)

- [x] Pilha * criar()
- [x] int inserir(Pilha *, struct carta)
- [x] int remover(Pilha *, struct carta *) // Já remove e acessa
- [x] void embaralhar(Pilha *) 
- [x] int tamanho(Pilha *) 

## Lista Dinâmica
- [x] Lista * criar()
- [x] int inserirInicio(Lista *, struct carta)
- [x] int removerQualquer(Lista *, struct carta) // Remove exatamente o cara passado
- [x] int acessarIndice(Lista *, int) // Acessa indice específico 
- [x] int quantidade(Lista *)
- [x] int somaValores(Lista *) // Soma os valores das cartas de uma lista

## Estruturas necessárias

### Estruturas necessárias no main:

- [x] Mão (Lista *), sempre com cinco cartas: joga uma e compra uma.
- [x] Mesa (Lista *), inicia com cinco cartas, mas varia no andar da partida.
- [x] Baralho (Pilha *), inicia com 66 cartas embaralhadas, depois distribui 5 pro jogador e 5 pra mesa.
- [x] Coleção do Jogador (Lista **), um vetor de listas inicialmente vazias
- [x] Coleção do Computador (Lista **), um vetor de listas inicialmente vazias

### Estrutura da carta:
- [x] int numero, número que varia de 0 a 10
- [x] char naipe, naipe/cor que varia de A a F

## Nossa nota
- [x] Boas práticas - 1.5 - Vários trechos desse projeto podem ser feitos na força bruta, replicagem eterna de código e outras má práticas. Faça um código generalizado, compreensível e sem gambiarras.
- [x] Preparação - 1.5 - Tudo inicializado corretamente (Mão, Mesa, Coleções e Baralho) e aleatoriamente quando for o caso (Mão, Mesa e Baralho). São 66 cartas ao todo: 6 cores (recomendo usar letras A - F) e 11 números (0 - 10), uma carta de cada combinação (cor e número).
- [x] Validação - .5 - Permitir apenas ações que sigam as regras. Isto é, jogador só pode escolher cartas da mão válidas.
- [x] Implementar TAD corretamente - 2.0 - Respeitar todos os conceitos de TAD, propriedades e implementar corretamente todas as estruturas listadas neste documento.
- [x] Turno - 1.5 - Vez do Jogador e depois vez do Computador. Jogador joga uma carta da Mão e adquire uma nova do Baralho, depois Computador joga a carta do topo do Baralho. Cartas coletadas vão para as respectivas Coleções de quem fez a jogada.
- [x] Tela da partida - 1.5 - Imprimir o tabuleiro corretamente com todas as informações necessárias e todas as opções possíveis.
- [x] Final da Partida - Saber quando terminar a partida e indicar corretamente se o jogador perdeu, fez pontos, venceu ou venceu perfeitamente, sendo respectivamente: ter todas as cores na coleção, jogou até ficar com as 4 cartas e baixar 2 na mesa, jogou até ficar com 4 cartas e na coleção tinha zero pontos, jogou até ficar com 4 cartas e na coleção tinha zero pontos e na mão tinha dois zeros. Dizer a pontuação do jogador no segundo caso de fim de partida.