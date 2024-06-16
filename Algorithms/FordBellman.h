
#ifndef ALG_FORD_BELLMAN
#define ALG_FORD_BELLMAN

#include "Graphs/MatrixGraph.h"
#include "Graphs/ListGraph.h"

class FordBellman
{
public:
    // Metoda implementuj¹ca algorytm Forda-Bellmana dla grafu macierzowego
    void Ford_Bellman_matrix(MatrixGraph& graph, int start, int end, bool write);

    // Metoda implementuj¹ca algorytm Forda-Bellmana dla grafu listowego
    void Ford_Bellman_list(ListGraph& graph, int start, int end, bool write);
};
#endif //ALG_FORD_BELLMAN


