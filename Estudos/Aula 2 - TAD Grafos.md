# Aula 2 - TAD Grafos

> Para representar um grafo em um tipo abstrato, existem algumas técnicas utilizadas que modelam a ideia descrita.
> 

## Matriz de adjacências

Matriz quadrada de magnitude de eixo igual à quantidade de elementos no grafo. O conteúdo de cada índice da matriz representa o valor associado à aresta do grafo.

Essa representação está sujeita a uma ordem entre os vértices. Se eles estão ordenados, temos uma matriz única. Entretanto, caso não haja essa ordem, existem várias matrizes diferentes equivalentes a um mesmo grafo.

Se o grafo não for orientado, temos uma matriz simétrica. Entretanto, podemos utilizar a ordem **(linhas, colunas)** para representar a orientação da aresta.

- **Custo** - O($n^2$)
- **Acesso** - O(1)
- Aloca a memória sem saber se ela será utilizada
- O custo de alteração do número de vértices é linearmente proporcional ao número de elementos

> Portanto, a matriz de adjacência é recomendada quando se tem um **********************grafo denso********************** - possui uma grande quantidade de arestas em relação ao número de elementos. Dessa forma, esse caso vai se aproximar ao uso completo do espaço alocado.
> 

## Lista de adjacências

Implementação de um vetor de listas lineares que representa as conexões que o vértice daquela posição possuí. Se assemelha à implementação da matriz, mas com algumas ressalvas a depender da natureza dessas listas.

- **Custo** - O(n + m) (sendo n o número de vértices e m o de arestas)
- **************Acesso**************  - O($d_i$) - [grau do vértice onde ocorre o acesso]
- Aloca a memória conforme a utilização
- Se a lista está ordenada, existe um custo de manutenção para a operação de inserção e remoção, porém a busca se torna de custo menor.
- Para grafos não ordenados, temos que sempre duplicar o número estruturas de arestas, pois essas aparecerão em duas listas diferentes, mesmo que representem a mesma ideia.

> Logo, essa modelagem é mais conveniente a grafos mais esparsos, isto é, com menos quantidade de arestas quando comparada ao número de vértices. Também é conveniente quando se precisa determinar rapidamente o grau de um vértice.
>