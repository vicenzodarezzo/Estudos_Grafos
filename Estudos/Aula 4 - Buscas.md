# Aula 4 - Buscas

# Busca em Largura (BFS)

> Busca é uma maneira de percorrer os componentes conexos de um grafo, aplicando ou não uma estrutura condicional para encontrar ou obter uma informação
> 

O método utilizado aqui é utilizar as distâncias dos demais vértice em relação a um ponto de partida. Percorre-se primeiro os conectados a ele, depois percorre-se os que distam um vértice do pont inicial, depois 2 e etc até não houver mais vértices a se visitar.

Para realizar a busca tomamos uma notação:

- Vértices brancos: o estado de início, padrão
- Vértice cinza : quando um vértice branco é visitado pela primeira vez, ele se torna cinza
- Vértice preto : quando um vértice já tem todos seus vértices adjascentes visitados, ele se torna preto

Também utilizamos uma fila para poder enfileirar os vértices não visitados

## Algoritmo:

- Seja que uma fila, torne o vértice incial como cinza e inicialize a distância como zero
- Enfilere o primeiro vértice
- Enquanto a fila não está vazia
    - Desenfilere o início da fila e incremente a distância
    - Para cada aresta desse vértice
        - Se o vértice não é cinza
            - O torne cinza e enfilere-o

### Informações:

- Usa a estrutura auxiliar de fila
- Organiza o grafo com base nas distâncias descobertas dos vértices em relação ao início - avanço concêntrico.
- É útil para problemas de menores caminhos por conta das distâncias

# Busca em Profundidade (DFS)

> É um processo que se baseia no mesmo princípio da anterior: percorrer todo o grafo colorindo os vértices em branco, cinza e preto. Porém, a busca DFS em especial, toda vez que encontra outro vértice, reinicia o processo de DFS, de forma que sejam empilhadas as rotinas até encontrar o fim. Com o fim atingido a cauda de recursão termina de realizar o processo e da início às próximas ramificações - Backtracking
> 

A busca DFS, como utiliza uma pilha, pode ser implementada interativamente (com auxílio de uma pilha) ou recursivamente.

### Algoritmo recursivo

- Torne o vértice cinza
- Para todos os vértices adjascentes:
    - se o vértice é branco, torne-o cinza e chame a recurssão nele
    - senão torne-o preto

### Algoritmo interativo

- Empilhe o primeiro vértice
- Enquanto a pilha não está vazia:
    - v = topo da pilja
    - se v é branco, torne o cinza e o empilja
    - senão torne-o preto

## Complexidade

Repare que a complexidade da busca não é simplismente n, sendo n o número de vértices. Repare que, para cada adjacência do vértice, a chama recursiva ou o emiplhamento é realizado. Logo devemos adicionar o número de arestas à esta conta, tendo em vista que a recursão será chamada com base nas conexões - arestas - do vértice analisado.

$$
C = O( n_v + a)
$$

## Aplicações

Ordenação topoloógica dos vértices do grafo

Achar componentes fortemente conexas de um grafo

Categorizar arestas do grafo

- aresta de árvore : está na árvore de busca em profundidade - árvore gerada pelo DFS
- aresta de retorna : se conecta um vértice ao seu ancestral
- aresta de avanço : se conecta um vértice ao seu sucessor
- aresta de cruzamento : aresta não planar - presente me gráficos não planares
-