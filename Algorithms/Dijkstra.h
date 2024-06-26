#ifndef ALG_DIJKSTRA
#define ALG_DIJKSTRA

#include "Graphs/MatrixGraph.h"
#include "Graphs/ListGraph.h"


class Dijkstra
{
public:
    // Metoda implementująca algorytm Dijkstry dla grafu macierzowego
    void dijkstraMatrix(MatrixGraph& graph, int startVertex, int endVertex);

    // Metoda implementująca algorytm Dijkstry dla grafu listowego
    void dijkstraList(ListGraph& graph, int startVertex, int endVertex);

private:
    // Metody pomocnicze do kopca
    static void swap(int& a, int& b); // Metoda zamieniająca dwie liczby całkowite
    void heapify(int* priorityQueue, int* distance, int n, int i); // Metoda przywracająca własność kopca
    int extractMin(int* priorityQueue, int* distance, int& size); // Metoda usuwająca i zwracająca element minimalny z kopca
    static void decreaseKey(int* priorityQueue, int* distance, int size, int vertex, int newDistance); // Metoda zmniejszająca wartość klucza w kopcu

    // Metody pomocnicze do kopca dla par (int, int)
    static void swap(MyPair<int, int>& a, MyPair<int, int>& b); // Metoda zamieniająca dwie pary
    void heapify(MyPair<int, int>* priorityQueue, int* distance, int n, int i); // Metoda przywracająca własność kopca dla par
    MyPair<int, int> extractMin(MyPair<int, int>* priorityQueue, int* distance, int& size); // Metoda usuwająca i zwracająca element minimalny z kopca dla par
    static void decreaseKey(MyPair<int, int>* priorityQueue, int* distance, int size, int vertex, int newDistance); // Metoda zmniejszająca wartość klucza w kopcu dla par

    static void displayList(int vertices, int* distance);
    static void displayMatrix(int* distance, int startVertex, int endVertex, int* predecessors);
};

#endif // ALG_DIJKSTRA
