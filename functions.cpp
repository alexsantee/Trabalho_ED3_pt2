#include <bits/stdc++.h>
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
