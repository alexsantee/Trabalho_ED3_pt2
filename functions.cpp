#include <bits/stdc++.h>
#include <string.h>
#include "constants.h"
#include "functions.h"
#include "grafo.h"

using namespace std;

//Le um registro a partir de um binario e guarda em reg
int leregbin(FILE *fp, struct registro * reg)
{
    char c = SEPARADOR_REGISTRO;
    int i = 0;

    //Percorre lixo da memoria
    while(c == SEPARADOR_REGISTRO)
        if(fread(&c, sizeof(char), 1, fp) == 0)
            return 0;

    //Le campos de tamanho fixo
    //estado de origem
    reg->estadoOrigem[0] = c;
    fread(&(reg->estadoOrigem[1]), sizeof(char), 1, fp);
    reg->estadoOrigem[2] = '\0';
    //estado de destino
    fread(reg->estadoDestino, sizeof(char), 2, fp);
    reg->estadoDestino[2] = '\0';
    fread(&(reg->distancia), sizeof(int), 1, fp);

    //Le campos de tamanho variavel
    //cidade de origem
    fread(&c, sizeof(char), 1, fp);
    while (c != SEPARADOR_CAMPO)
    {
        reg->cidadeOrigem[i] = c;
        fread(&c, sizeof(char), 1, fp);
        i++;
    }
    reg->cidadeOrigem[i] = '\0';
    //cidade de destino
    i = 0;
    fread(&c, sizeof(char), 1, fp);
    while (c != SEPARADOR_CAMPO)
    {
        reg->cidadeDestino[i] = c;
        fread(&c, sizeof(char), 1, fp);
        i++;
    }
    reg->cidadeDestino[i]='\0';
    //tempo de viagem
    i = 0;
    fread(&c, sizeof(char), 1, fp);
    while(c != SEPARADOR_CAMPO)
    {
        reg->tempoViagem[i] = c;
        fread(&c, sizeof(char), 1, fp);
        i++;
    }
    reg->tempoViagem[i] = '\0';

    return 1;
}

//zera todo o struct registro para reuso
void limpa_reg(struct registro *reg)
{
    strcpy(reg->estadoOrigem,"");
    strcpy(reg->estadoDestino,"");
    reg->distancia = 0;
    strcpy(reg->cidadeOrigem,"");
    strcpy(reg->cidadeDestino,"");
    strcpy(reg->tempoViagem,"");
}


void inserenografo(struct registro reg, struct grafo * grafo)
{
    int i = 0;
    bool achou_orig = false;
    bool achou_dest = false;
    //Iterador percorre o vetor de vertices do grafo procurando por um vertice com a mesma cidade origem do reg
    for(struct vertice v : grafo->vertices) 
    {
        if(v.cidadeOrigem == reg.cidadeOrigem)   //Compara cidade origem do reg com cidade origem do vertice
        {                                                   //Se encontrou
            struct aresta a;                                //Cria nova aresta e preenche com os dados do registro    
            a.cidadeDestino = reg.cidadeDestino;
            a.distancia = reg.distancia;
            a.estadoDestino = reg.estadoDestino;
            a.tempo = reg.tempoViagem;
            grafo->vertices.at(i).arestas.push_back(a);     //insere aresta no vertice correspondente
            sort(grafo->vertices.at(i).arestas.begin(), grafo->vertices.at(i).arestas.end());  //ordena vetor de arestas por ordem alfabética
            achou_orig = true;
            break;
        }
        i++;
    }

    //Caso não encontre nenhum vertice de mesmo nome é necessario criar novo vertice
    if(!achou_orig)
    {
        //Cria nova aresta e preenche com os dados do registro
        struct aresta a;                   
        a.cidadeDestino = reg.cidadeDestino;
        a.distancia = reg.distancia;
        a.estadoDestino = reg.estadoDestino;
        a.tempo = reg.tempoViagem;
        //Cria novo vertice e preenche com os dados do registro
        struct vertice v;
        v.cidadeOrigem = reg.cidadeOrigem;
        v.estadoOrigem = reg.estadoOrigem;
        //Insere aresta no vertice criado
        v.arestas.push_back(a);
        sort(v.arestas.begin(), v.arestas.end());
        //Insere vertice no vetor de vertices do grafo
        grafo->vertices.push_back(v);
        sort(grafo->vertices.begin(), grafo->vertices.end());   //Ordena vetor de vertices do grafo
    }

    //Insere aresta simetrica - CTRL+C CTRL+V de codigo!!!
    i = 0;
    for(struct vertice v : grafo->vertices)
    {
        if(v.cidadeOrigem == reg.cidadeDestino)
        {
            struct aresta a;
            a.cidadeDestino = reg.cidadeOrigem;
            a.distancia = reg.distancia;
            a.estadoDestino = reg.estadoOrigem;
            a.tempo = reg.tempoViagem;
            grafo->vertices.at(i).arestas.push_back(a);     //insere aresta no vertice correspondente
            sort(grafo->vertices.at(i).arestas.begin(), grafo->vertices.at(i).arestas.end());  //ordena vetor de arestas por ordem alfabética
            achou_dest = true;
            break;
        }
        i++;
    }

    if(!achou_dest)
    {
        struct aresta a;
        a.cidadeDestino = reg.cidadeOrigem;
        a.distancia = reg.distancia;
        a.estadoDestino = reg.estadoOrigem;
        a.tempo = reg.tempoViagem;
        struct vertice v;
        v.cidadeOrigem = reg.cidadeDestino;
        v.estadoOrigem = reg.estadoDestino;
        v.arestas.push_back(a);                 //Insere aresta no vertice criado
        sort(v.arestas.begin(), v.arestas.end(), isALess);
        grafo->vertices.push_back(v);           //Insere vertice no vetor de vertices do grafo
        sort(grafo->vertices.begin(), grafo->vertices.end(), isVLess);   //Ordena vetor de vertices do grafo
    }
}

void print_grafo(struct grafo grafo)
{
	//Iterador que percorre vetor de vertices do grafo
    for(struct vertice v : grafo.vertices)
    {
		//Printa cidade origem e estado origem do vertice
        cout << v.cidadeOrigem << " " << v.estadoOrigem;
		//Iterador que percorre vetor de arestas do vertice
        for(struct aresta a : v.arestas)
        {
            if(a.tempo.compare("\0") == 0)
                cout << " " << a.cidadeDestino << " " << a.estadoDestino << " " << a.distancia;
            else
				//Printa cidade dest, estado dest, dist e tempo da aresta
                cout << " " << a.cidadeDestino << " " << a.estadoDestino << " " << a.distancia << " " << a.tempo;
        }
		//Pula linha no fim do vetor de arestas;
        cout << endl;
    }
}

void print_reg(int RRN, struct registro *reg)
{
    cout << 
    RRN << " " << 
    reg->estadoOrigem << " " << reg->estadoDestino << " " <<
    reg->distancia << " " << 
    reg->cidadeOrigem << " " << reg->cidadeDestino << " " <<
    reg->tempoViagem << 
    endl;
}

//tipo auxiliar para uso no Dijkstra
//guarda vertice, distancia e antecessor
typedef tuple<vertice*,int,string> vd;

struct ordem_nome{
    bool operator() (vd v1, vd v2) const{
        return (get<0>(v1)->cidadeOrigem < get<0>(v2)->cidadeOrigem);
    }
};

struct ordem_V{
    bool operator() (vertice v1, vertice v2) const{
        return (v1.cidadeOrigem < v2.cidadeOrigem);
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

    //Inicializa vertices a processar, junto com as distancias e antecessores
    for(unsigned int i = 0; i < grafo->vertices.size(); i++){
        vd v;
        string nome_cidade;
        //A cidade de origem e inicializada com distancia 0
        if(grafo->vertices[i].cidadeOrigem == cidadeOrigem){
            v = vd(&(grafo->vertices[i]), 0, "");
        }
        //A cidade de destino e inicializaca com distancia infinita
        else {
            v = vd(&(grafo->vertices[i]), infinito, "");
        }
        //Insere na lista de vertices a processar
        nome_cidade = get<0>(v)->cidadeOrigem;
        a_processar.insert(vmap(nome_cidade,v));
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

grafo * arvore_geradora(struct grafo *grafo, string valorcampo)
{
    struct registro reg;
    struct grafo *MST;
    set<vertice, ordem_V> B, N;
    for(vertice v : grafo->vertices)
    {
        if(v.cidadeOrigem.compare(valorcampo) == 0)
            B.insert(v);

        N.insert(v);
    }
    if(B.empty())
    {
        cout << "Cidade inexistente." << endl;
        return NULL;
    }
    while(B != N)
    {
        int dist;
        int min = infinito;
        struct vertice n;
        for(vertice v : grafo->vertices)
        {
            if(B.find(v) != B.end())
            {
                for(vertice u : grafo->vertices)
                {
                    dist = isAdj(v, u);
                    if(dist != -1)
                    {
                        if(N.find(u) != N.end() && B.find(u) == B.end())
                        {
                            if(min > dist)
                            {
                                if (isVLess(u,v))
                                {
                                    strcpy(reg.cidadeOrigem, u.cidadeOrigem.c_str());
                                    strcpy(reg.estadoOrigem, u.estadoOrigem.c_str());
                                    strcpy(reg.cidadeDestino, v.cidadeOrigem.c_str());
                                    strcpy(reg.estadoDestino, v.estadoOrigem.c_str());
                                    reg.distancia = dist;
                                }else
                                {
                                    strcpy(reg.cidadeOrigem, v.cidadeOrigem.c_str());
                                    strcpy(reg.estadoOrigem, v.estadoOrigem.c_str());
                                    strcpy(reg.cidadeDestino, u.cidadeOrigem.c_str());
                                    strcpy(reg.estadoDestino, u.estadoOrigem.c_str());
                                    reg.distancia = dist;                    
                                }
                                n = v;
                                min = dist;
                            }
                        }
                    }
                }
            }
        }
        B.insert(n);
        inserenografo(reg, MST);
    }
    return MST;
}

bool isSetEqual(set<vertice> a1, set<vertice> a2)
{
    bool achou = true;
    for(vertice v : a1)
    {
        if(!achou)
            return false;
        achou = false;
        for(vertice u : a2)
        {
            if(v.cidadeOrigem == u.cidadeOrigem)
            {
                achou = true;
                break;
            }
        }
    }

    return true;
}

int isAdj(struct vertice v1, struct vertice v2)
{
    for(aresta a : v1.arestas)
    {
        if(a.cidadeDestino == v2.cidadeOrigem)
            return a.distancia;
    }

    return -1;
}
