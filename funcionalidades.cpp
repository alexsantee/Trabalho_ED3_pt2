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
        cout << "Falha no carregamento do arquivo." << endl;
        exit(0);
    }

    fread(&cab.status, sizeof(char), 1, fp);
    if(cab.status != '1')
    {
        cout << "Falha no carregamento do arquivo." << endl;
        exit(0);
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
    //le grafo do arquivo
    funcionalidade9(nomebin, grafo);

    //realiza algoritmo de Dijkstra
    vector <int> distancias;
    vector <string> antecessores;
    int status;
    status = menor_caminho(grafo, valorcampo, &distancias, &antecessores);

    //imprime saida
    //erros
    if(status == 1 || status == 2){
        cout << "Falha na execução da funcionalidade." << endl; return;}
    else if(status == 3){
        cout << "Cidade inexistente." << endl; return;}
    //resultado
    else{   //status == 0(ok)
        vertice * v_org = NULL;     //origem do algoritmo
        vertice * v_cur = NULL;     //cidade atual da impressao
        vertice * v_ant = NULL;     //antecessor de atual

        v_org = procura_vertice(valorcampo, grafo);
        if(v_org == NULL) {cout << "Cidade inexistente." << endl; return;}
        //imprime cada vertice
        for(unsigned int i = 0; i<grafo->vertices.size(); i++){
            v_cur = &(grafo->vertices[i]);
            v_ant = procura_vertice(antecessores[i], grafo);
            if (v_ant != NULL){
                cout <<
                    v_org->cidadeOrigem << " " <<
                    v_org->estadoOrigem << " " <<
                    v_cur->cidadeOrigem << " " <<
                    v_cur->estadoOrigem << " " <<
                    distancias[i] << " " <<
                    v_ant->cidadeOrigem << " " <<
                    v_ant->estadoOrigem << endl;
            }

        }

    }
}

void funcionalidade11(string nomebin, string nomecampo, string valorcampo, struct grafo *grafo)
{   
    //Le grafo do arquivo
    funcionalidade9(nomebin, grafo);

    vector<int> antecessores;
    arvore_geradora(grafo, valorcampo, &antecessores);
    for(int i : antecessores){
    cout << i << endl;
    }
}
