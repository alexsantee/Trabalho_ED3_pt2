#include <bits/stdc++.h>
#include "constants.h"
#include "functions.h"
#include "grafo.h"

using namespace std;

int leregbin(FILE *fp, struct registro * reg)
{
    char c = SEPARADOR_REGISTRO;
    int i = 0;

    while(c == SEPARADOR_REGISTRO)
        if(fread(&c, sizeof(char), 1, fp) == 0)
            return 0;

    reg->estadoOrigem[0] = c;
    fread(&(reg->estadoOrigem[1]), sizeof(char), 1, fp);
    reg->estadoOrigem[2] = '\0';
    fread(reg->estadoDestino, sizeof(char), 2, fp);
    reg->estadoDestino[2] = '\0';
    fread(&(reg->distancia), sizeof(int), 1, fp);

    fread(&c, sizeof(char), 1, fp);
    while (c != SEPARADOR_CAMPO)
    {
        reg->cidadeOrigem[i] = c;
        fread(&c, sizeof(char), 1, fp);
        i++;
    }
    reg->cidadeOrigem[i] = '\0';
    i = 0;
    fread(&c, sizeof(char), 1, fp);
    while (c != SEPARADOR_CAMPO)
    {
        reg->cidadeDestino[i] = c;
        fread(&c, sizeof(char), 1, fp);
        i++;
    }
    reg->cidadeDestino[i]='\0';
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
    for(struct vertice v : grafo->vertices) //Iterador percorre o vetor de vertices do grafo procurando por um vertice com a mesma cidade origem do reg
    {
        if(v.cidadeOrigem.compare(reg.cidadeOrigem) == 0)   //Compara cidade origem do reg com cidade origem do vertice
        {                                                   //Se encontrou
            struct aresta a;                                //Cria nova aresta e preenche com os dados do registro    
            a.cidadeDestino = reg.cidadeDestino;
            a.distancia = reg.distancia;
            a.estadoDestino = reg.estadoOrigem;
            a.tempo = reg.tempoViagem;
            v.arestas.push_back(a);                         //insere aresta no vertice correspondente
            sort(v.arestas.begin(), v.arestas.end(), isALess);           //ordena vetor de arestas por ordem alfabética
            return;
        }
    }                                       //Caso não encontre nenhum vertice de mesmo nome é necessario criar novo vertice
    struct aresta a;                        //Cria nova aresta e preenche com os dados do registro
    a.cidadeDestino = reg.cidadeDestino;
    a.distancia = reg.distancia;
    a.estadoDestino = reg.estadoOrigem;
    a.tempo = reg.tempoViagem;
    struct vertice v;                       //Cria novo vertice e preenche com os dados do registro
    v.cidadeOrigem = reg.cidadeOrigem;
    v.estadoOrigem = reg.estadoOrigem;
    v.arestas.push_back(a);                 //Insere aresta no vertice criado
    grafo->vertices.push_back(v);           //Insere vertice no vetor de vertices do grafo
    sort(grafo->vertices.begin(), grafo->vertices.end(), isVLess);   //Ordena vetor de vertices do grafo
    return;
}

void print_grafo(struct grafo grafo)
{
    for(struct vertice v : grafo.vertices)  //Iterador que percorre vetor de vertices do grafo
    {
        printf("%s %s", v.cidadeOrigem.c_str(), v.estadoOrigem.c_str());    //Printa cidade origem e estado origem do vertice
        for(struct aresta a : v.arestas)    //Iterador que percorre vetor de arestas do vertice
        {
            printf(" %s %s %d %s", a.cidadeDestino.c_str(), a.estadoDestino.c_str(), a.distancia, a.tempo.c_str()); //Printa cidade dest, estado dest, dist e tempo da aresta
        }
        printf("\n");   //Pula linha no fim do vetor de arestas;
    }
}