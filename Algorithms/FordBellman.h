
#ifndef ALG_FORD_BELLMAN
#define ALG_FORD_BELLMAN

#include "Graphs/MatrixGraph.h"
#include "Graphs/ListGraph.h"

class FordBellman
{
public:
    // Metoda implementuj¹ca algorytm Forda-Bellmana dla grafu macierzowego
    static void fordBellmanMatrix(MatrixGraph& graph, int startVertex, int endVertex);

    // Metoda implementuj¹ca algorytm Forda-Bellmana dla grafu listowego
    static void fordBellmanList(ListGraph& graph, int startVertex, int endVertex);

    static void displayList(int startVertex, int endVertex, int* distance, int* predecessors);

    static void displayMatrix(int startVertex, int endVertex, int* distance, int* predecessors);
};
#endif //ALG_FORD_BELLMAN


