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
    funcionalidade9(nomebin, grafo);
    vector <int> distancias;
    vector <string> antecessores;
    menor_caminho(grafo, valorcampo, &distancias, &antecessores);
    //PRINT DE DEBUGGING-------------------------------------------------------
    for(string s : antecessores){
        cout << s << " ";
    }
    cout << endl;
    for(int i : distancias){
        cout << i << " ";
    }
    cout << endl;

}

/*void funcionalidade11(string nomebin, string nomecampo, string valorcampo, struct grafo *grafo)
{
    struct grafo * MST;
    funcionalidade9(nomebin, grafo);
    MST = arvore_geradora(grafo, valorcampo);
    print_grafo(*MST);
}*/
