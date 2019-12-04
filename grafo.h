#include <bits/stdc++.h>

using namespace std;

struct aresta{
    string cidadeDestino;  //Nome da cidade destino (id do vertice)
    string estadoDestino;
    int distancia;
    string tempo;
};

//estrutura de vertice para armazenar no grafo
struct vertice{
    string cidadeOrigem;                //Nome da cidade de origem (id do vertice)
    string estadoOrigem;
    vector<aresta> arestas;       //Cidades destino do vertice (LISTA ORDENADA)
};

//Define uma estrutura de grafo por lista de adjacencia
//A lista esta ORDENADA por nome da cidade de origem
struct grafo{
    vector<vertice> vertices;
};

bool isVLess(struct vertice v1, struct vertice v2);

bool isALess(struct aresta a1, struct aresta a2);