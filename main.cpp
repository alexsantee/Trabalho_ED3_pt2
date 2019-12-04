#include <bits/stdc++.h>
#include "constants.h"
#include "functions.cpp"
#include "funcionalidades.cpp"
#include "grafo.cpp"

int main()
{
    int op;
    string nomebin;
    struct grafo grafo;

    scanf("%d", &op);

    switch (op)
    {
    case 9:
        cin >> nomebin;
        funcionalidade9(nomebin, &grafo);
        break;
    
    default:
        break;
    }
}