#include <bits/stdc++.h>
#include "constants.h"
#include "functions.h"
#include "funcionalidades.h"
#include "grafo.h"

using namespace std;

//Gera um grafo com base na leitura de um arquivo binario
//recebe nome do arquivo e grafo em que registrar de entrada
void funcionalidade9(string nomebin, struct grafo * grafo)
{
    struct registro reg;
    struct cabecalho cab;
    FILE * fp = fopen(nomebin.c_str(), "rb");
    //Abre o arquivo e verifica sua integridade
    if(fp == NULL)
    {
        cout << "Falha na execução da funcionalidade." << endl;
        return;
    }

    fread(&cab.status, sizeof(char), 1, fp);
    if(cab.status != '1')
    {
        cout << "Falha na execução da funcionalidade." << endl;
        return;
    }
    
    //Registra metadados
    fread(&cab.numeroVertices, sizeof(int), 1, fp);
    fread(&cab.numeroArestas, sizeof(int), 1, fp);
    fread(cab.dataUltimaCompactacao, sizeof(char), 10, fp);
    
    //Insere no grafo caso nao marcado como removido
    int RRN;
    for(RRN = 0; leregbin(fp, &reg); RRN++)
    {
        if(reg.estadoOrigem[0] != INDICA_REMOVIDO)
        {
            inserenografo(reg, grafo);
        }
        limpa_reg(&reg);
    }

    fclose(fp);
    return;
}

void funcionalidade10(string nomebin, string nomecampo, string valorcampo, struct grafo *grafo)
{
    struct aresta dist[grafo->vertices.size()];
    struct vertice ant[grafo->vertices.size()];
    struct aresta menor;
    menor.distancia = 100000;
    funcionalidade9(nomebin, grafo);
    int i = 0;
    for(vertice v : grafo->vertices)
    {
        if(v.cidadeOrigem == valorcampo)
        {
            for(aresta a : v.arestas)
            {
                if(a.distancia < menor.distancia)
                    menor = a;
            }
        }
        i++;
    }
}