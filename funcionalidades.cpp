#include <bits/stdc++.h>
#include "constants.h"
#include "functions.cpp"
#include "grafo.cpp"

using namespace std;

void funcionalidade9(string nomebin, struct grafo * grafo)
{
    struct registro reg;
    struct cabecalho cab;
    FILE * fp = fopen(nomebin.c_str(), "rb");
    if(fp == NULL)
    {
        printf("Falha na execução da funcionalidade.\n");
        return;
    }

    fread(&cab.status, sizeof(char), 1, fp);
    if(cab.status != '1')
    {
        printf("Falha na execução da funcionalidade.\n");
        return;
    }
    
    fread(&cab.numeroVertices, sizeof(int), 1, fp);
    fread(&cab.numeroArestas, sizeof(int), 1, fp);
    fread(cab.dataUltimaCompactacao, sizeof(char), 10, fp);

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
    print_grafo(*grafo);
    return;
}