// Daniel Figueiredo Macedo - 14A - 201820276
// Pedro Carvalho Pereira - 14A - 201820265
// A ser corrigido no perfil Daniel Macedo

#include <iostream>
#include <algorithm>
using namespace std;
#define TAM 100000

typedef struct
{
    int v1, v2, c;
} parVertice;

void ligar(int x, int y, int conjuntoVertices[TAM][1])
{

    if (conjuntoVertices[x][1] > conjuntoVertices[y][1])
        conjuntoVertices[y][0] = x;

    else
    {
        conjuntoVertices[x][0] = y;
        if (conjuntoVertices[x][1] == conjuntoVertices[y][1])
            conjuntoVertices[y][1] = conjuntoVertices[y][1] + 1;
    }
}

void ligarReverso(int x, int y, int reversoConjAux[TAM][1])
{

    if (reversoConjAux[x][1] < reversoConjAux[y][1])
        reversoConjAux[y][0] = x;

    else
    {
        reversoConjAux[x][0] = y;
        if (reversoConjAux[x][1] == reversoConjAux[y][1])
            reversoConjAux[y][1] = reversoConjAux[y][1] + 1;
    }
}

int encontraConjunto(int conjuntoVertices[TAM][1], int x)
{

    int noh = x;
    int pai = conjuntoVertices[noh][0];

    while (noh != pai)
    {
        noh = pai;
        pai = conjuntoVertices[noh][0];
    }

    conjuntoVertices[x][0] = pai;
    return pai;
}

int main()
{
    int resposta1, resposta2;
    parVertice arvMin[TAM];
    parVertice arvMax[TAM];
    parVertice xy[TAM];
    int conjuntoVertices[TAM][1];

    int x, y, m, n, custo = 0;

    cin >> x >> y;

    if (x != 0 or y != 0)
    {

        do
        {
            for (int i = 1; i <= y; i++)
            {
                cin >> m >> n >> custo;
                xy[i].v1 = m;
                xy[i].v2 = n;
                xy[i].c = custo;
                if (m == ' ' or n == ' ' or custo == ' ')
                {
                    break;
                }
            }

            for (int i = 1; i <= x; i++)
            {
                conjuntoVertices[i][0] = i;
                conjuntoVertices[i][1] = 0;
            }

            int auxv1, auxv2, auxcusto, conju, conjv;
            int n_arestas = 0;

            for (int i = 1; i <= y; i++)
            {
                for (int j = 1; j <= y - i; j++)
                {
                    if (xy[j].c > xy[j + 1].c)
                    {
                        auxv1 = xy[j].v1;
                        auxv2 = xy[j].v2;
                        auxcusto = xy[j].c;
                        xy[j].v1 = xy[j + 1].v1;
                        xy[j].v2 = xy[j + 1].v2;
                        xy[j].c = xy[j + 1].c;
                        xy[j + 1].v1 = auxv1;
                        xy[j + 1].v2 = auxv2;
                        xy[j + 1].c = auxcusto;
                    }
                }
            }
            int contador = 1;

            for (int i = 1; i <= y - 1; i++)
            {
                conju = encontraConjunto(conjuntoVertices, xy[i].v1);
                conjv = encontraConjunto(conjuntoVertices, xy[i].v2);
                if (conju != conjv)
                {
                    arvMin[contador].v1 = xy[i].v1;
                    arvMin[contador].v2 = xy[i].v2;
                    arvMin[contador].c = xy[i].c;
                    contador++;
                    n_arestas++;
                    if (n_arestas != x)
                    {
                        ligar(conju, conjv, conjuntoVertices);
                    }
                }
            }
            for (int i = 1; i <= n_arestas; i++)
            {
                resposta1 += arvMin[i].c;
            }

            int contnormal = 1;
            int contreverso = y;
            parVertice reversoAux;
            int reversoConjAux[TAM][1];

            while (contnormal < contreverso)
            {
                reversoAux = xy[contnormal];
                xy[contnormal] = xy[contreverso];
                xy[contreverso] = reversoAux;

                contnormal++;
                contreverso--;
            }

            n_arestas = 0;
            contador = 1;

            for (int i = 1; i <= x; i++)
            {
                reversoConjAux[i][0] = i;
                reversoConjAux[i][1] = 0;
            }

            for (int i = 1; i <= y; i++)
            {
                conju = encontraConjunto(reversoConjAux, xy[i].v1);
                conjv = encontraConjunto(reversoConjAux, xy[i].v2);

                if (conju != conjv)
                {
                    arvMax[contador].v1 = xy[i].v1;
                    arvMax[contador].v2 = xy[i].v2;
                    arvMax[contador].c = xy[i].c;
                    contador++;
                    n_arestas++;
                    if (n_arestas != x)
                    {
                        ligarReverso(conju, conjv, reversoConjAux);
                    }
                }
            }

            for (int i = 1; i <= n_arestas; i++)
            {
                resposta2 += arvMax[i].c;
            }
            cout << resposta2 - resposta1 << endl;
            resposta2 = 0;
            resposta1 = 0;

        } while (cin >> x >> y and (x != 0 or y != 0));
    }
}                     