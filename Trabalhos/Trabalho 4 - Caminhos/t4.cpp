// Organização Computacional em Grafos - Trabalho 4
// Enzo Nunes Sedenho - 13671810
// Gabriel da Costa Merlin - 12544420
// Vicenzo D'Arezzo Zilio - 13671790

#include <iostream>
#include <bits/stdc++.h>
#include <list>
#include <stack>
#include <vector>

using namespace std;

typedef pair<int, int> int_pair;
#define ORIGEM 0
#define NIL -1

class Grafo
{
    int num_vertices;            // Numero de vertices
    int num_arestas;             // Numero de arestas
    list<int_pair> *links;       // Arestas na forma (destino, peso)

    public:
        Grafo(int num_v, int num_a);                     // Construtor
        void Conecta(int origem, int destino, int peso); // Adiciona uma aresta no grafo
        int Dijkstra(int origem, int destino);           // Algoritmo de Dijkstra
        int Prim(int origem, int destino);               // Algoritmo de Prim
    
    private:
        // Retorna a distância entre duas cidades
        int busca_dist(list<pair<int, int>> lista, int destino);
        // Calcula o custo da rota VIP
        int custo_vip(vector<int> antecessores, vector<int> dist, int destino);
        // Calcula o custo da rota padrao
        int custo_padrao(vector<int> antecessores, int origem);
};

// Construtor
Grafo::Grafo(int num_v, int num_a)
{
    // Inicializando as variaveis
    this->num_vertices = num_v;
    this->num_arestas = num_a;

    // Alocando memória para a lista de adjacencias
    links = new list<int_pair>[num_v + 1];
}

// Adiciona uma aresta no grafo bidericional
void Grafo::Conecta(int origem, int destino, int peso)
{   
    // Cada aresta aparece duas vezes na lista, tendo em vista que precisamos
    //  ser capazes de computá-la independentemente da orientação de acesso
    links[origem].push_back(make_pair(destino, peso));
    links[destino].push_back(make_pair(origem, peso));
}

// Retorna a distância entre duas cidades
int Grafo::busca_dist(list<int_pair> lista, int destino)
{
    int dist = NIL;

    // Percorrendo a lista de adjacências da cidade
    for(const auto &v : lista)
    {
        // Caso a cidade buscada seja encontrada, obtemos a distância
        if(v.first == destino)
        {
            dist = v.second;
            break;
        }
    }
    // Retornando a distância
    return dist;
}

// Calcula o custo da rota padrão
int Grafo::custo_padrao(vector<int> antecessores, int origem)
{
    int total = 0;

    // Iterando os vértices do grafo
    for(int i = 0; i < num_vertices; i++)
    {
        // Caso o vértice atual não seja a origem
        if(i != origem)
        {
            // Calculando a distância entre a cidade atual e sua antecessora na rota
            // e adicionando-a a distancia total
            int dist_anterior = busca_dist(links[i], antecessores[i]);
            total += dist_anterior;
        }
    }
    // Retornando a distância total
    return total;
}

// Calcula o custo da rota VIP
int Grafo::custo_vip(vector<int> antecessores, vector<int> dist, int destino)
{
    // Inicializando o numero de cidades visitadas como 1 (cidade destino)
    int cidades_visitadas = 1;
    int atual = antecessores[destino];

    // Visitando cada cidade da rota VIP 
    while(antecessores[atual] != NIL) // Enquanto houver antecessora
    {
        atual = antecessores[atual];
        cidades_visitadas++; // Incrementando o numero de cidades visitadas
    }
    // Contabilizando a cidade de origem
    cidades_visitadas++;

    // Calculando a distância VIP conforme especificado
    return (dist[destino] * (num_vertices - cidades_visitadas));
}

// Algoritmo de Dijkstra utilizado para representar a rota VIP
int Grafo::Dijkstra(int origem, int destino)
{
    // Vetor de distâncias (inicializado como INT MAX)
    vector<int> dist(num_vertices, INT_MAX);
    // Fila de prioridade 
    priority_queue<int_pair, vector<int_pair>, greater<int_pair>> pq;
    // Vetor de antecessores (inicializado como NIL)
    vector<int> antecessores(num_vertices, NIL);

    // Adicionando a origem na fila de prioridade e no vetor de distancias
    dist[origem] = 0;
    pq.push(make_pair(origem, 0));

    // Enquanto houverem cidades na fila de prioridade
    while (!pq.empty())
    {
        // Visitando a próxima cidade da fila de prioridade
        int atual = pq.top().first;
        pq.pop();

        // Percorrendo as cidades vizinhas
        for (const auto &v : links[atual])
        {
            int vertice = v.first; // Cidade vizinha
            int peso = v.second;   // Custo da aresta vizinha

            // Caso a aresta deva ser relaxada
            if (dist[vertice] > dist[atual] + peso)
            {
                // Relaxando a aresta
                dist[vertice] = dist[atual] + peso;
                
                // Adicionando a cidade vizinha na fila de prioridade 
                pq.push(make_pair(vertice, dist[vertice]));
                
                // Adicionando a cidade atual no vetor de antecessores
                antecessores[vertice] = atual;
            }
        }
    }
    // Calculando e retornando o custo da rota VIP
    return custo_vip(antecessores, dist, destino);
}

// Algoritmo de Prim utilizado para representar a rota padrão
int Grafo::Prim(int origem, int destino)
{
    // Fila de prioridade de arestas, representando o par ordenado : (int custo, int destino) 
    priority_queue<int_pair, vector<int_pair>, greater<int_pair>> pq;

    // Vetor de antecessores (inicializado como NIL)
    vector<int> antecessores(num_vertices, NIL);
    // Vetor de distâncias (inicializado como INT MAX)
    vector<int> dist(num_vertices, INT_MAX);
    // Vetor booleano que informa a presença (ou ausência) de uma cidade na fila de prioridade
    vector<bool> inPQ(num_vertices, true);

    // Montando a fila de prioridade
    pq.push(make_pair(0, origem));

    // Enquanto houverem cidades na fila de prioridade
    while(!pq.empty())
    {
        // Visitando a próxima cidade na fila de prioridade
        int atual = pq.top().second;
        pq.pop();

        // Iterando a lista de adjacências do vértice retirado para relaxar suas arestas,
        // caso esta represente um ganho local de custo ao vértice de destino
        for(auto v : links[atual])
        {
            int vertice = v.first; // Cidade vizinha
            int peso = v.second; // Custo da aresta vizinha

            if(inPQ[vertice])
            {
                // Relaxamento condicional
                if(peso < dist[vertice])
                {
                    // Relaxando a aresta : inserindo-a na fila de prioridade
                    pq.push(make_pair(peso, vertice));
                    dist[vertice] = peso;
                }

                // Adicionando a cidade atual no vetor de antecessores (caminho) e retirando-o da MST
                antecessores[vertice] = atual;
            }
        }
        // Tendo a decisão ótima local computada para o vértice atual, o logicamente retiramos da fila
        // de prioridade
        inPQ[atual] = false;
    }

    // Calculando e retornando o custo da rota padrão
    return custo_padrao(antecessores, origem);
}

int main(int argc, char *argv[])
{
    int num_v, num_a;
    int origem, destino, peso;
    int cidade_destino;

    // Lendo o numero de vertices e arestas
    scanf("%d %d", &num_v, &num_a);

    // Criando o Grafo
    Grafo g(num_v, num_a);

    // Lendo as arestas e atribuíndo-as ao grafo
    for(int i = 0; i < num_a; i++)
    {
        scanf("%d %d %d", &origem, &destino, &peso);
        g.Conecta(origem, destino, peso);
    }
    scanf(" %d", &cidade_destino); // Lendo o destino da rota
    
    // Calculando as distâncias padrão e VIP
    int custo_vip = g.Dijkstra(ORIGEM, cidade_destino);
    int custo_padrao = g.Prim(ORIGEM, cidade_destino);

    // Imprimindo a rota mais vantajosa e seu custo
    if(custo_vip > custo_padrao) // Caso a rota padrão seja mais vantajosa
    {
        cout << "PADRAO" << endl;
        cout << custo_padrao << endl;
    }
    else if(custo_vip < custo_padrao) // Caso a rota VIP seja mais vantajosa
    {
        cout << "VIP" << endl;
        cout << custo_vip << endl;
    }
    else // Caso as rotas tenham o mesmo custo
    {
        cout << "NDA" << endl;
        cout << custo_vip << endl;
    }
    return 0;
}