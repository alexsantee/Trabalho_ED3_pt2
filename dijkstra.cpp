#include <set>
#include <map>
#include <string>

#include "constants.h"
#include "grafo.h"
#include "functions.h"

//tipo auxiliar para uso no Dijkstra
//guarda vertice, distancia e antecessor
typedef tuple<vertice*,int,string> vd;

struct ordem_nome{
    bool operator() (vd v1, vd v2) const{
        return (get<0>(v1)->cidadeOrigem < get<0>(v2)->cidadeOrigem);
    }
};

//Para usar no mapa nomeOrigem->vertice
typedef pair<string,vd> vmap;

//Calcula o menor caminho para todas as cidades a partir de uma origem
//utiliza o algoritmo de Dijkstra na implementacao
//recebe o grafo e o nome da cidade de origem e os enderecos de retorno
//retorna por endereco um vetor com as distancias e o vetor de antecessores
//retorna 0 em execucao correta e diferente em erro
int menor_caminho(struct grafo *grafo, string cidadeOrigem,
                    vector<int> *distancias, vector<string> *antecessores){

    //Verifica validade das entradas
    if(grafo == NULL || distancias == NULL || antecessores == NULL){
        //vetor nulo recebido
        return 1;
    } else if (cidadeOrigem.empty()){
        //nome de origem vazio        
        return 2;
    }

    //Inicializa variaveis
    map<string,vd> a_processar;
    set<vd, ordem_nome> processados;

    bool origemValida = false;
    //Inicializa vertices a processar, junto com as distancias e antecessores
    for(unsigned int i = 0; i < grafo->vertices.size(); i++){
        vd v;
        string nome_cidade;
        //A cidade de origem e inicializada com distancia 0
        if(grafo->vertices[i].cidadeOrigem == cidadeOrigem){
            v = vd(&(grafo->vertices[i]), 0, "");
            origemValida = true;
        }
        //A cidade de destino e inicializaca com distancia infinita
        else {
            v = vd(&(grafo->vertices[i]), infinito, "");
        }
        //Insere na lista de vertices a processar
        nome_cidade = get<0>(v)->cidadeOrigem;
        a_processar.insert(vmap(nome_cidade,v));
    }

    //Verifica se cidade pedida foi encontrada
    if(!origemValida){
        return 3;
    }
    
    //Enquanto houverem vertices a processar
    while(!a_processar.empty()){

        //E POSSIVEL ORDENAR POR DISTANCIA?
        //Encontra vertice com menor distacia da origem
        vmap min = (*a_processar.begin());  //min = primeiro vertice
        for(vmap v : a_processar){
            if(get<1>(v.second) < get<1>(min.second))   //compara distancias
                min = v;
        }
        
        //Retira o minimo da lista de vertices a processar
        a_processar.erase(min.first);
        processados.insert(min.second);

        //Atualiza distancias dos vertices vizinhos a processar
        for(aresta a : get<0>(min.second)->arestas){
            //Se o vertice destino ainda falta processar
            if(a_processar.find(a.cidadeDestino) != a_processar.end()){
                int nova_distancia;
                //nova_distancia = distancia ate min + min->v
                nova_distancia = get<1>(min.second) + a.distancia;
                //se nova_distancia menor que a ultima conhecida
                //substitui distancia e antecessor
                if(nova_distancia < get<1>(a_processar.find(a.cidadeDestino)->second)){
                    get<1>(a_processar.find(a.cidadeDestino)->second) = nova_distancia;
                    get<2>(a_processar.find(a.cidadeDestino)->second) = min.first; 
                }
            }
        }
    }
    
    //Coloca as variaveis de retorno
    distancias->clear();
    distancias->reserve(grafo->vertices.size());
    antecessores->clear();
    antecessores->reserve(grafo->vertices.size());
    for(vd v : processados){
        distancias->push_back(get<1>(v));
        antecessores->push_back(get<2>(v));
    }

    return 0;
}
