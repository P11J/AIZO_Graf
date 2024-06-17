#ifndef ALG_PRIM
#define ALG_PRIM

#include "Graphs/MatrixGraph.h"
#include "Graphs/ListGraph.h"

// Definicja klasy Alg_Prim zawierającej metody dla algorytmu Prima
class Alg_Prim
{
public:
    // Metoda implementująca algorytm Prima dla grafu macierzowego
    static void Prim_matrix(MatrixGraph& graph, bool write);

    // Metoda implementująca algorytm Prima dla grafu listowego
    static void Prim_list(ListGraph& graph, bool write);

private:
    // Metoda pomocnicza do znajdowania wierzchołka o minimalnym kluczu, który nie jest w MST
    static int minKey(const int key[], const bool inMST[], int vertices);
};

#endif // ALG_PRIM

