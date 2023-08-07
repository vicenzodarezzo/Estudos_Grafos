# Aula 3 - Algoritmo de Fleury e Coloração de Grafos

# O que é o Algoritmo de Fleury

The Fleury algorithm is an algorithm for finding Eulerian paths and cycles in a graph. It was proposed by the Swiss mathematician Charles Fleury in 1883.

The algorithm works by iteratively **removing** edges from the graph, always choosing edges from bridges last to avoid separating the graph into multiple connected components. The algorithm can be implemented using a depth-first search or a breadth-first search.

The Fleury algorithm is particularly useful for solving problems involving the traversal of a graph along all edges (an Eulerian path) or visiting all vertices and returning to the starting vertex (an Eulerian cycle).

# Fluxograma:

### Algoritmo de Fleury simplificado

- Verifique se o grafo pode ser euleriano;
- Escolha um vértice de início - V1
- Entre os vértices adjascentes a V1:
    - Verifique se há uma aresta entre eles e se esta pode ser percorrida.
- Remova a aresta verificada
    - A remoção pode ser lógica ou pode ser diretamente na memória
- Se ainda houver arestas não percorridas, escolha o vértice de destino e repita o algoritmo

## Problema: Arestas de pontes

> Uma ponte (cut edge) é uma aresta que, caso seja removida, deixa o grafo desconexo. Portanto, caso essa aresta for percorrida no algoritmo de Fleury, comprometeriámos o funcionamento do algoritmo, caso ele ainda não tenha sido terminado. Logo, o que deve ser feito é uma verificação para que esse caso seja só executado em última instância.
> 

### Regra da Ponto

Dado um vértice e suas arestas, escolhemos uma destas. Se o vértice destino possuir grau 1, significa que tal aresta é uma aresta ponte. Logo devemos escolher outra aresta. Se essa for a única aresta que conecta o atual vértice a outros, temos o aval de percorrê-la, caso contrário, não.

- Começa em um vértice v1
- Escolhe uma aresta de v1 que ainda não foi marcada
- Se essa aresta não é ponte, seguimos. Senão, verificamos a próxima aresta até encontrar uma aresta válida ou o fim da lista de arestas. Se nenhuma das demais arestas é válida, percorremos a ponte.
- Removemos a aresta escolhida e movemos-nos ao próximo vértice
- Caso ainda não tenham sido todas percorridas, retorna à interação, porém, agora, com o vértice de destino

# Coloração de Grafos

## Problema:

Tendo em vista a disposição de objetos e a conexão entre eles, queremos colorir cada objeto, de modo que cada vizinho tenha uma cor diferente, utilizando o menor número de cores.

- Teorema das 4 cores: para grafos planares (grafos no plano cujas arestas não se cruzam) é necessário, no máximo, quatro cores para colorar o grafo.
    - Como verificar se um grafo é planar?
        
        [https://en.wikipedia.org/wiki/Planarity_testing](https://en.wikipedia.org/wiki/Planarity_testing)
        

O que vamos nos propor é tentar encontrar o número cromático de um grafo - quantidades de cores necessárias. Os algortimos que dispomos atualmente são de classe Não Polinomial de complexidade, baseada na tomada de decisões ótimas locais, e não globais (algoritmos gulosos)

## Algoritmo de Welsh-Powell

- Marque todos os vértices como incolores
- Criei uma lista dos vértices, ordenando-a conforme a ordem descrescente de grau do vértice
- Atribua uma cor ao primeiro vértice incolor da lista
- Percorra o restante da lista de vértices e atribua a mesma cor para o próximo vértice não adjascente ao vértice inicial. Faça isto até não conseguir preencher mais nenhum com essa cor
- troco de cor e retorno à interação até que todos os grafos estejam coloridos
-