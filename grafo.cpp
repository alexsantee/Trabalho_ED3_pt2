#include <bits/stdc++.h>
#include "grafo.h"

using namespace std;

bool isVLess(struct vertice v1, struct vertice v2)
{
    int x = v1.cidadeOrigem.compare(v2.cidadeOrigem);

    if(x < 0)
        return true;
    else
        return false;
}

bool isALess(struct aresta a1, struct aresta a2)
{
    int x = a1.cidadeDestino.compare(a2.cidadeDestino);

    if(x < 0)
        return true;
    else
        return false;
}