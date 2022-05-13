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
- [ ] Lista * criar()
- [ ] int inserirInicio(Lista *, struct carta)
- [ ] int removerQualquer(Lista *, struct carta) // Remove exatamente o cara passado
- [ ] int acessarIndice(Lista *, int) // Acessa indice específico
- [ ] int quantidade(Lista *)
- [ ] int somaValores(Lista *) // Soma os valores das cartas de uma lista

## Estruturas necessárias

### Estruturas necessárias no main:

- [ ] Mão (Lista *), sempre com cinco cartas: joga uma e compra uma.
- [ ] Mesa (Lista *), inicia com cinco cartas, mas varia no andar da partida.
- [x] Baralho (Pilha *), inicia com 66 cartas embaralhadas, depois distribui 5 pro jogador e 5 pra mesa.
- [ ] Coleção do Jogador (Lista **), um vetor de listas inicialmente vazias
- [ ] Coleção do Computador (Lista **), um vetor de listas inicialmente vazias

### Estrutura da carta:
- [x] int numero, número que varia de 0 a 10
- [x] char naipe, naipe/cor que varia de A a F