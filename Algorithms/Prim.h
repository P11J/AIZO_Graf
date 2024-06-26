#ifndef ALG_PRIM
#define ALG_PRIM

#include "Graphs/MatrixGraph.h"
#include "Graphs/ListGraph.h"

// Definicja klasy Prim zawierającej metody dla algorytmu Prima
class Prim
{
public:
    // Metoda implementująca algorytm Prima dla grafu macierzowego
    static void primMatrix(MatrixGraph& graph);

    // Metoda implementująca algorytm Prima dla grafu listowego
    static void primList(ListGraph& graph);

private:
    // Metoda pomocnicza do znajdowania wierzchołka o minimalnym kluczu, który nie jest w MST
    static int minKey(const int key[], const bool inMST[], int vertices);

    static void displayList(int vertices, int* predecessor, int* key);

    static void displayMatrix(int vertices, int* predecessor, int* key);
};

#endif // ALG_PRIM

