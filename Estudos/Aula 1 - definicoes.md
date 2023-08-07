# Aula 1 - definições

# O que é Grafo

A graph is a mathematical structure used to model pairwise relations between objects. A graph consists of a set of vertices (also called nodes) and a set of edges connecting pairs of vertices. Graphs can be used to represent a wide range of real-world phenomena, including social networks, transportation systems, and computer networks.

## Grafo Orientado:

> Grafo orientado é todo grafo que elenca uma ordem ao conjunto das arestas, de forma que a aresta (x,y) leve apenas de x para y, de forma que, diferentemente do grafo normal, ir de y para x através dela não é valido.
> 

### Grau de entrada e saída:

> Grau é a quantidade de arestas que um vértice possuí. Quando o grafo é ordenado, precisamos diferenciar esse dado em dois aspectos: ************Grau de entrada -************ quantas arestas levam a x; ******Grau de saídas -****** quantas arestas saem de x.
> 
- Sink: um vértice com d_out = 0
- Source: um vértice d_in  = 0

## Grafo Valorado:

> Todo grafo cujas arestas estão associadas a um valor.
> 

## Vértices e arestas

> O número de vértices de um grafo é chamado de **Ordem** - V(g) - enquanto o número de arestas é é representado por A(g)
> 

## Algumas Definições:

### Multigrafo

Um grafo em que existe um par de vértices que é conectador por mais de uma aresta. Por exemplo, se um vértice a pode ser atingido a partir de b percorrendo uma aresta de valor 2 e outra de valor 7.

### Grafo Completo

É um grafo em que todos os vértices são adjascentes, logo, ele possuí todas as arestas possíveis para ligar os vértices.

# Caminhos e Propriedades:

> Caminho de x a y é uma sequência de arestas que corresponde a uma sequência de vértices adjascentes que levam de x até y. O comprimento de um caminho é dado pelo número de arestas que ele percorre, ou seja:
> 

Comprimento Caminho de N vértices = N - 1

- ************************************Caminhos simples:************************************ aqueles que não repetem vértices
- ************Ciclo:************ aqueles que saem e retornam ao mesmo vértice
    - Grafos cíclicos são aqueles apresentam pelo menos um ciclo

## Grafos conexos:

> Um grafo é dado como conexo se, e somente se, para qualquer par de vértices, existe pelo menos um caminho que os conectem. ******************************************Atencão, caminho é diferente de arestas!******************************************
> 

### Grafos fortemente conectados

> Falamos que um grafo ******************ORIENTADO****************** é fortemente conectado quando, para qualquer par de vértices (A, B), existe um caminho que saia de A levando a B e um que saia B de lavando a A.
> 

## Caminho Euleriano

> Um caminho que contém todas as arestas do grafo, passando por cada uma delas apenas uma vez.
> 

### Grafo euleriano:

Ciclo euleriano é um grafo que apresenta um caminho euleriano cíclico. Chamamos de grafo euleriano todo grado que é um ciclo euleriano.

- ******Propriedade:****** esses grafos apresentam sempre um grau par para cada vértice.

## Caminho Hamiltoniano:

> Um caminho que contém todos os vértices de um grafo, passando por cada vértice apenas uma vez.
> 

### Grafo hamiltoniano:

Grafo hamiltoniano é todo grafo que equivale a um caminho hamiltoniano cíclico

## Grafos Bipartidos

> Grafos bipartidos são grafos em que podemos dividir seus vértices em dois conjuntos e que as arestas levam um vértice de um conjunto para um vértice de outro conjunto, praticamente como uma ou mais funções.
> 

![Captura de Tela 2023-05-15 às 17.21.49.png](Aula%201%20-%20definic%CC%A7o%CC%83es%202f9667f467d845b5858ea7b3bffe8ef6/Captura_de_Tela_2023-05-15_as_17.21.49.png)

## Grafo Complementar

> Dado um grafo g, g’ será o grafo complementar a g se ele for formado pelos mesmos vértices, estes agora ligados pelas arestas que poderiam, mas não estão presentes no grafo anterior. Portanto, se a aresta existe em g, não existe em g’ ; se a aresta não existe em g, exister em g’ .
> 

## Subgrafo gerador

> Subgrafo gerador é um grafo menor que outro grafo g e está contido em g. Portanto g pode ser gerador a partir dele através do acréscimo de novas arestas
> 
- Devem ter o mesmo número de vértices
- Os conjuntos de aresta devem se relacionar através de pertinência.

### Subgrafo induzido

> É um subgrafo formado através da seleção de alguns vértices de um grafo g, levando todas as arestas que os conectam junto.
> 

### Hipergrafo

> Um grafo em que é a uma híper-aresta. Isto é, uma aresta que conecta mais do que apenas 2 grafos. Por exempo, em que as arestas são funcões que vão além da união de dois conjuntos singulares.
> 

# Isomorfismo

> Isomorfismo é uma propriedade de um conjunto de grafos que podem ser equivalentes. Isso é, se existe correspondência entre seus vértices e arestas e a relação de incidência de um vértice a outro através de uma aresta específica seja preservada.
> 

![Captura de Tela 2023-05-15 às 17.26.29.png](Aula%201%20-%20definic%CC%A7o%CC%83es%202f9667f467d845b5858ea7b3bffe8ef6/Captura_de_Tela_2023-05-15_as_17.26.29.png)

- Verificar isomorfismo é um problema da computação, porém existem alguns detalhes que podemos considerar para verificar se dois grafos não são isomorfos, como:
    - Verificar se os graus dos vértices são os mesmos entre os grafos 1 e 2
    - Compare os vértices adjacentes ao vértice inicial em ambos os grafos. Se os vértices adjacentes têm o mesmo número de arestas e não foram rotulados ainda, atribua rótulos correspondentes a eles. Por exemplo, se o vértice adjacente ao vértice inicial no primeiro grafo tem três arestas e ainda não foi rotulado, atribua o rótulo "C" a ele. Em seguida, encontre o vértice adjacente correspondente no segundo grafo que também tenha três arestas e atribua o rótulo correspondente a ele (no caso, "D").