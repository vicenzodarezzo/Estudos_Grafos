# Aplicações da busca em Profundidade

# Ordenação topológica

> O problema aqui é tentar gerar uma ordenação a partir de um grafo acíclico direcionado. O objetivo seria relacionar linearmente um par de vértices criando uma ordem de precedência
> 

Um exemplo de aplicação seria a execução de tarefas cujas relações identificam a interpendência entre elas. Dessa forma, a ordenação topológica.

## Grafos Acíclicos

Grafos acíclicos são um pré-requisito para que possamos realizar uma ordenação entre os vértices. Isto acontece pois, em caso de ciclos, a aresta de retorno nos impede de estabelecer uma ordem de precedência entre dois vértices.

## Implementação

O algortimo que vai ser utilizado para produzir uma sequencia baseada na conectividade entre os vértices é a BFS.

```jsx
REALIZA A BFS:
-> Se o vertice foi processado (todos suas componentes foram percorridas) :
Adiciona-o à pilha de ordenação topológica
```

Assim como a BFS, a ordenação topológica varia com base no vértice de início e na heurística de escolha das arestas a serem percorridas.

<aside>
💡 Complexidade. = O(V + A)

</aside>

# Componentes fortemente conexas (CFC)

> O objetivo é conseguir utilizar algoritmos simples para identificar componentes fortemente conexas em um grafo orientado.
> 

## Grafo Transposto

Grafo transposto é aquele formado a partir de um grafo original, trocando a orientação de suas arestas.

Observe que uma propriedade do grafo transposto e seu original é que ambos compartilham as mesmas componentes fortemente conexas. Logo podemos usar essa comparação para obtê-las

## Utilização da DFS

A ideia aqui é, primeiro de tudo, determinar os tempos de descobrimento de cada vértice para que possamos escolher por onde começar o algoritmo. Logo, tendo em vista que começaremos dos últimos a serem processados, transpomos o grafo - para estudar seu retorno - e começamos a DFS a partir dos mais processados, de modo vértices já processados não são mais acessados e nem inseridos em novas árvores

Logo, nesta segunda busca, cada árvore de busca representa uma CFC.

```jsx
-> gera o grafo transposto
-> Realizar a busca em profundidade para determinar o tempo de processamento
	 de cada vértice.
-> busca em profundidade no grafo transposta a partir do último vértice
   descoberto, reiniciando esse processo sempre que quiser
-> Cada árvore da segunda busca será uma componente conexa do grafo
```

## Algoritmo de Tarjan

Um algoritmo alternativo para a descoberta de CFC que leva em consideração a propagação de informações através de arestas de retorno na busca em profundidade. 

### Requisitos:

- Uma pilha
- Um valor para representar cada vértice - no caso iremos considerar o tempo de descoberta, nessa versão

### Definição de um Low-Value

Low value vai representar um valor obtido por uma operação que será executada toda vez que um vértice é processado. Ela será:

Ao processar um vértice, verificamos todos os tempos de descobrimento dos vértices que estão conectados por arestas divergentes do atual. Se um desses vértices destino tem um tempo de low_value menor do que o tempo de descobrimento do vértice atual, tornamos o low_value do vértice atual igual a este valor, senão fazemos-o igual ao tempo de descobrimento deste vertice.

Dessa forma, as arestas de retorno vão propagar o tempo de descobrimento para o low-value de todos seus vértices fortemente conexos.

Vértices com low-values equivalentes a seu tempo de descobrimento serão pais de uma nova componente fortemente conexa

### Algoritmo

Portanto, o algoritmo consiste em verificar os vértices que tem o mesmo valor de Low

```python
-> Empilha-se o vértice de inicio

-> enquanto a pilha não estiver vazia:
	-> recursão na adjascência
	-> calcula o low-value
	-> Se o low-value é igual ao tempo de descobrimento :
			-> desempilha todos os vértices até encontrar este, 
			-> esta sequencia representa um CFC
```