#include <set>
#include <map>
#include <string>
#include <tuple>
#include <vector>

#include "constants.h"
#include "grafo.h"
#include "functions.h"

using namespace std;

typedef pair<string,int> imap;

int arvore_geradora(struct grafo *grafo, string valorcampo, vector<vector<sucessor>> *sucessores)
{
    //Prepara retorno do vetor de sucessores
    sucessores->resize(grafo->vertices.size());
    for(unsigned int i = 0; i < sucessores->size(); i++){
        (*sucessores)[i].clear();
    }

    //Mapa de indices do vetor de adjacencias <nome do vertice,indice no vetor>
    map<string,int> mapa_i;
    for(unsigned int i = 0; i < grafo->vertices.size(); i++){
        mapa_i.insert( imap(grafo->vertices[i].cidadeOrigem, i) );
    }
    
    //B sao vertices da arvore minima
    set<int> B;

    //inicializa o conjunto B
    map<string,int>::iterator it = mapa_i.find(valorcampo);
    if(it != mapa_i.end()){   //cidade esta na lista
        B.insert(it->second);
    }
    else{
        //Cidade inexistente.
        return 1;
    }

    //Enquanto existem vertices fora da arvore insere mais
    while(B.size() < grafo->vertices.size()){
        //dados da menor aresta
        string min_tempo;
        int min_dist = infinito;
        int origem, destino;
        //para todo vertice da arvore atual
        for(int i : B){
            //procura menor aresta
            for(aresta a : grafo->vertices[i].arestas){
                //se vertice a adicionar nao esta na arvore considera adicao
                if(B.find(mapa_i[a.cidadeDestino]) == B.end()){
                    //se aresta nova eh menor substitui
                    if(a.distancia < min_dist){
                        origem = i;
                        destino = mapa_i[a.cidadeDestino];
                        min_tempo = a.tempo;
                        min_dist = a.distancia;
                    }
                }
            }
        }
        //insere vertice mais proximo na arvore e atualiza vetor de sucessores
        B.insert(destino);
        (*sucessores)[origem].push_back(sucessor(destino, min_dist, min_tempo));
    }

    return 0;
}
