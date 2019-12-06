#include <bits/stdc++.h>
#include "constants.h"
#include "functions.h"
#include "funcionalidades.h"
#include "grafo.h"
#include "helper.h"

int main()
{
    int op;
    string nomebin;
    string nomecampo;
    char valorcampo[TAM_VAR];
    struct grafo grafo;

    cin >> op;

    switch (op)
    {
    case 9:
        cin >> nomebin;
        funcionalidade9(nomebin, &grafo);
        //Mostra grafo na tela
        print_grafo(grafo);
        break;
    
    case 10:
        cin >> nomebin;
        cin >> nomecampo;
        scan_quote_string(valorcampo);
        funcionalidade10(nomebin, nomecampo, valorcampo, &grafo);
        break;

    /*case 11:
        cin >> nomebin;
        cin >> nomecampo;
        scan_quote_string(valorcampo);
        funcionalidade11(nomebin, nomecampo, valorcampo, &grafo);
        break;*/

    default:
        break;
    }
}
