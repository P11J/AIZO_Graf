#ifndef ALG_DIJKSTRA
#define ALG_DIJKSTRA

#include "Graphs/MatrixGraph.h"
#include "Graphs/ListGraph.h"


class Dijkstra
{
public:
    // Metoda implementuj�ca algorytm Dijkstry dla grafu macierzowego
    void dijkstraMatrix(MatrixGraph& graph, int startVertex, int endVertex);

    // Metoda implementuj�ca algorytm Dijkstry dla grafu listowego
    void dijkstraList(ListGraph& graph, int startVertex, int endVertex);

private:
    // Metody pomocnicze do kopca
    static void swap(int& a, int& b); // Metoda zamieniaj�ca dwie liczby ca�kowite
    void heapify(int* priorityQueue, int* distance, int n, int i); // Metoda przywracaj�ca w�asno�� kopca
    int extractMin(int* priorityQueue, int* distance, int& size); // Metoda usuwaj�ca i zwracaj�ca element minimalny z kopca
    static void decreaseKey(int* priorityQueue, int* distance, int size, int vertex, int newDistance); // Metoda zmniejszaj�ca warto�� klucza w kopcu

    // Metody pomocnicze do kopca dla par (int, int)
    static void swap(MyPair<int, int>& a, MyPair<int, int>& b); // Metoda zamieniaj�ca dwie pary
    void heapify(MyPair<int, int>* priorityQueue, int* distance, int n, int i); // Metoda przywracaj�ca w�asno�� kopca dla par
    MyPair<int, int> extractMin(MyPair<int, int>* priorityQueue, int* distance, int& size); // Metoda usuwaj�ca i zwracaj�ca element minimalny z kopca dla par
    static void decreaseKey(MyPair<int, int>* priorityQueue, int* distance, int size, int vertex, int newDistance); // Metoda zmniejszaj�ca warto�� klucza w kopcu dla par
};

#endif // ALG_DIJKSTRA
