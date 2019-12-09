#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <bits/stdc++.h>
#include "grafo.h"

using namespace std;

int leregbin(FILE *fp, struct registro * reg);

void limpa_reg(struct registro *reg);

void inserenografo(struct registro reg, struct grafo * grafo);

void insereNdirec(struct registro reg, struct grafo * grafo);

void print_grafo(struct grafo grafo);

void print_reg(int RRN, struct registro *reg);

vertice *procura_vertice(string cidadeOrigem, grafo *grafo);

int menor_caminho(struct grafo *grafo, string cidadeOrigem,
                    vector<int> *distancias, vector<string> *antecessores);

//trinca (destino, distancia, tempo)
typedef tuple<int, int, string> sucessor;

int arvore_geradora(struct grafo *grafo, string valorcampo, vector<vector<sucessor>> *sucessores);

bool isSetEqual(set<struct vertice, struct ordem_V> a1, set<struct vertice, struct ordem_V> a2);

int isAdj(struct vertice v1, struct vertice v2, char * tempo);

#endif
