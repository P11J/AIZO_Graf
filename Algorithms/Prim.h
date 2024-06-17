#ifndef ALG_PRIM
#define ALG_PRIM

#include "Graphs/MatrixGraph.h"
#include "Graphs/ListGraph.h"

// Definicja klasy Alg_Prim zawieraj�cej metody dla algorytmu Prima
class Alg_Prim
{
public:
    // Metoda implementuj�ca algorytm Prima dla grafu macierzowego
    static void Prim_matrix(MatrixGraph& graph, bool write);

    // Metoda implementuj�ca algorytm Prima dla grafu listowego
    static void Prim_list(ListGraph& graph, bool write);

private:
    // Metoda pomocnicza do znajdowania wierzcho�ka o minimalnym kluczu, kt�ry nie jest w MST
    static int minKey(const int key[], const bool inMST[], int vertices);
};

#endif // ALG_PRIM

