# Cálculo do menor caminho de origem única a destino único

> Para o problema de menor caminho, temos duas situações básicas, com arestas simples e com arestas valoradas. Para arestas simples, como aprendemos, podemos obter o menor caminho entre dois vértices através da busca em largura, pois o comprimento do caminho é determinado pelo número de arestas.
> 

# Função de custo de um caminho

A princípio, o custo de uma caminho é simplismente a soma dos valores dentro de um caminho. Porém, devemos tomar cuidado com alguns detalhes a depender da modelagem, como por exemplo:

- Presença de caminhos negativos:
    
    Existe o caso em que posso percorrer um caminho negativo quantas vezes quiser para diminuir o custo do caminho, o que causaria uma perda semântica do caminho
    
- Presença de ciclos:
    
    Se há ciclos no caminho, sabemos que ele não faz parte do menor caminho
    

# Relaxamento de Arestas

### Custo de Caminho d(x)

Nomeando um vértice inicial, d(x) é um valor associado a cada vértice (x) que representa o menor caminho do vértice atual até o nomeado.

### Estimativa Padrão

Levemos em consideração que todos os custos de caminhos são infinitos a princípio.

## Ato de relaxar

Relaxar uma aresta consiste em verifica se é possível utilizar tal aresta para diminuir d(x) sendo x seu vértice de destino.

```nasm
Em uma aresta (u,v) valorada :

se d[v] + d[u] + custo(u,v)
	d[v] = d[u] + custo(u,v)
	antecessor[v] = u

```

# Algoritmo de Dijkstra

Um algoritmo de caminho mais curto, dado um vértice inicial, para grafos com ciclos e valores apenas positivos.

Esse caminho considera que voltar por um vértice já percorrido não tem custo adicional para o caminho.

A ideia aqui é manter um vetor que armazena a menor distância entre o vértice inicial e os demais vértices do grafo, de forma que, toda vez que encontrarmos um caminho menor para aquele vértice, atualizemos os valores no vetor.

### Relaxamento de aresta

Toda vez que percorremos uma aresta, analisamos se esse novo caminho consegueria reduzir a distância do vértice de destino:

d(V_inicial) + peso Aresta < d(V_destino) ? Se sim, trocamos a d(V_destino) := Relaxar a aresta

Caso queira armazenar o caminho, ao relaxar, atualizamos o antecessor do vértice destino para o vértice de origem da aresta.

## Método

```nasm
Setup :
	Inicia-se um vetor de distância e um vetor de antecessores,
	o primeiro com valores infinitos e o segundo com valores nulos.
	Inicia-se uma fila de prioridade (f) com os vértice, ponderando pela distancia

iniciando pelo V inicial
relaxa as arestas de V

enquanto F nao vazia:
	Retira um vértice de F 
	Soma-o ao caminho
	Para cada aresta do vértice :
		relaxamento
```

## Algoritmo Guloso:

> Algoritmo que toma decisões localmente ótimas, de modo que, a solução final seja geralmente ótima. De modo que o algoritmo não tenta prever o que vai acontecer no futuro para além da interação ou recursão atual.
> 

A complexidade do algoritmo vai depender da implementação da fila de prioridade. Em uma heap binária, sua complexidade fica de O((n+a)*log(n))  tendo piores desempenhos para grafos mais densos.

# Algoritmo de Bellman-Ford

> Um algoritmo que se propõe a estudar o mesmo que o de dikstra : caminhos de origem única a um destino único. Porém, a melhoria é que podemos usar esse algoritmo para grafos com pesos negativos sobre as arestas
> 

## Detecção de ciclos negativos

Uma aplicação desse algoritmo é detectar que vértices formam um ciclo negativo, o que pode nos fornescer a informação de quais vértices no grago terão distância de infinito negativo do vértice inicial.

- Esse fenômeno pode acontecer quando um vértice tem uma aresta negativa direcionada a si mesmo ou quando um caminho cíclico de vértices tem a soma de seus pesos como um número negativo.

## Método:

```python
Cria-se um vetor de distâncias incializado com o valor de infinito
Cria-se um vetor de antecessores para armazenar o caminho
Inicia-se no vértice inicial

Para N_Vertces - 1 vezes:
	Para cada aresta no grafo:
		tenta relaxar a aresta
```

Para detectar ciclos negativos, basta rodar a interação pela última vez. Se uma aresta for novamente relaxada, significa que o vértice de destino é ligado a um ciclo negativo.

```python
Para cada aresta no grafo:
		Se capaz de relaxar a aresta :
			Destino = - infinito
```

### Complexidade

Esse algortimo tem uma complexidade maior do que o dikstra e não pode ser melhorado através de filas de prioridade : O(V x A)

# Algoritmo baseado em ordenação topológica

> Um algoritmo que leva como requisito a ordenação topológica do grafo, de modo que sejamos capazes de dectar o caminho mínimo de um vértice para o outro, mesmo em um grafo com pesos negativos. Isso tudo, desde que não hajam ciclcos no grafo.
> 

```python
-> Ordena topologicamente o grafo

-> Inicializa um vetor de distância e antecessores como infinito e NIL

-> Para cada vértice na ordem:
	Relaxa as arestas do vértice 
```

A complexidade em tempo seria O( V * A)