# Estudo de Subgrafos Geradores

> Subgrafo gerador é um subgrafo tal que o conjunto de vértices do grafo e do subgrafo são equivalentes. De modo que somente as arestas sejam apenas elas um subconjunto oriundo do grafo.
> 

# Subgrafo gerador de custo mínimo

Dado um grafo não orientado, o subgrafo gerador de custo mínimo será o subgrafo conexo cuja soma dos valores associados às arestas é a mínima possível dentro do subconjunto de grafos geradores.

## O subgrafo gerador é uma árvore

Obser que, se precisamos que um grafo não orientado seja conexo, e queremos diminuir ao máximo o número de arestas do modelo, basta que apenas existam as areas de avanço ao longo do grafo, tornando ele uma árvore.

A aplicação desse problema representa a maneira mais eficiente de estabelecer conectividade entre os vértices.

# Como encontrar uma árvore geradora mínima?

> A centralidade dessa heurística consiste em deicidir, a partir de um vértice, qual aresta será inserida na árvore.
> 

## Algoritmo Genérico

```nasm
A = vazio
Enquato A não define ua árvore geradora:
	Encontre uma aresta seguar para conectar A a um vértice já não contido nele

## Aresta segura é uma aresta que manterá as características alemijadas pelo algoritmo

```

### Condição Invariante:

A cada interação, a árvore obtida até o momento é subconjuto de uma árvore geradora.

## Definição de conceitos para o algoritmo

### Corte

Um corte de um grafo não direcionado é uma partição de V, tal que corte A = (A : V -A). 

Um corte respeita o cunjunto A se nenhuma aresta que parte e chega em vértices de A cruza o corte. Utilizamos esses conceitos para determin ar a segurança de uma arestas. Uma aresta que crusa o corte e tem o menor custo dentre as demais arestas que se ligam àquele vértice é chamada de aresta leve.

Se T é uma árvore geradora mínima e há um corte que respeita T,  a aresta leve é uma aresta segura para T

# Algoritmo de Prim

Utiliza uma Fila de Prioridade : Uma heap ordenada conforme uma propriedade.

A fila de prioridade é utilizada para representar todas a arestas que cruzam o corte. E as operações realizadas na heap tem custo de log(n).

Ela é construída inicializando-a como vazia e, a medida que encontramos um novo vértice, inserimos todas as suas arestas na fila, de forma que a escolhida para atravessar o corte seja o topo, desde que esta leve a um vértice não visitado (percorra o corte).

```nasm
MST-PRIM:
Setup:
	cria uma array parent[V] inicializando com NIL
	cria um minHeap H de tamanho A para representar a fila de prioridade
	
	Insere as arestas do primeiro vértice em H, marcando-o como visitado

LOOP:
Enquanto a heap não está vazia:
	A = topo da heap
	D = destino(A)
	
	Se D não foi visitado :
		Insere as listas de D em H
		Marca D como visitado
		Adiciona V na lista de parents
		contadores++

```

### Complexidade

<aside>
💡 O(|A| + |V|) * log(V))

</aside>

# Algoritmo de Kruskal

Gera uma heap de prioridade a partir das arestas e vai conectando os vértices com base na aresta de maior prioridade para a gerar a árvore. Observe que quanto mais arestas, pior, portanto, essa implmenetação é menos eficiente para grafos mais densos.

```nasm
Definir os conjuntos iniciais : S - árvores unitárias triviais
inserir as arestas em uma heap de prioridade
Enquanto houver arestas na heap:
	(v,w) = remove aresta da fila 
	se v pertence a S1 e w pertence a S2 tal que a interseção entre S1 e S2 é vazia
		S3 = S1 união S2

```

### Complexidade:

<aside>
💡 **O(A *  log(V))**

</aside>