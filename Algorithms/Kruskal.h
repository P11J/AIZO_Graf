#ifndef ALG_KRUSKAL
#define ALG_KRUSKAL

#include "Graphs/MatrixGraph.h"
#include "Graphs/ListGraph.h"

struct Krawedz
{
    int pocz, kon, waga;
};

struct Podzbior
{
    int poprzednik, rank;
};

class Alg_Kruskal
{
public:
    void Kruskal_matrix(MatrixGraph& graph, bool write);
    void Kruskal_list(ListGraph& graph, bool write);
private:
    int znajdz(Podzbior podzbiory[], int i);
    void zlacz(Podzbior subsets[], int x, int y);
};

#endif ALG_KRUSKAL


