#include "estrutura.h"

TCel *novo(int ddd, int telefone, int identificador)
{
    TCel *n = NULL;
    while (n == NULL)
        n = malloc(sizeof(TCel));
    n->identificador = identificador;
    n->ddd = ddd;
    n->telefone = telefone;
    n->prox = NULL;
    return n;
}

void insere(TCel **prim, int identificador, int ddd, int telefone)
{
    if ((*prim) == NULL)
    {
        *prim = novo(identificador, ddd, telefone);
        return;
    }
    else
        insere(&((*prim)->prox), chave);
}

void elimina_lista(TCel *prim)
{
    if (prim == NULL)
    {
        return;
    }
    else
    {
        elimina_lista(prim->prox);
        free(prim);
    }
}

TCel *busca(TCel *prim, int identificador)
{
    if (prim == NULL)
    {
        return NULL;
    }
    else if (identificador == prim->identificador)
    {
        return prim;
    }
    else
    {
        busca(prim->prox, identificador);
    }
}