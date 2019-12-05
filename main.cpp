#include <bits/stdc++.h>
#include "constants.h"
#include "functions.h"
#include "funcionalidades.h"
#include "grafo.h"

int main()
{
    int op;
    string nomebin;
    struct grafo grafo;

    cin >> op;

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
