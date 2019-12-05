#include <bits/stdc++.h>

using namespace std;

int leregbin(FILE *fp, struct registro * reg);

void limpa_reg(struct registro *reg);

void inserenografo(struct registro reg, struct grafo * grafo);

void print_grafo(struct grafo grafo);

void print_reg(int RRN, struct registro *reg);

int menor_caminho(struct grafo *grafo, string cidadeOrigem,
                    vector<int> *distancias, vector<string> *antecessores);

