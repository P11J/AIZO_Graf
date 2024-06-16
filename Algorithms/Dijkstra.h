#ifndef ALG_DIJKSTRA // Zapobiega wielokrotnemu do��czaniu pliku nag��wkowego
#define ALG_DIJKSTRA

#include "Graphs/MatrixGraph.h" // Do��czenie pliku nag��wkowego dla grafu reprezentowanego macierz�
#include "Graphs/ListGraph.h" // Do��czenie pliku nag��wkowego dla grafu reprezentowanego list�

// Definicja klasy Alg_Dijkstra zawieraj�cej metody dla algorytmu Dijkstry
class Alg_Dijkstra
{
public:
    // Metoda implementuj�ca algorytm Dijkstry dla grafu macierzowego
    void Dijkstra_matrix(MatrixGraph& graph, int start, int end, bool write);

    // Metoda implementuj�ca algorytm Dijkstry dla grafu listowego
    void Dijkstra_list(ListGraph& graph, int start, int end, bool write);

private:
    // Metody pomocnicze do kopca
    void swap(int& a, int& b); // Metoda zamieniaj�ca dwie liczby ca�kowite
    void heapify(int* pq, int* dist, int n, int i); // Metoda przywracaj�ca w�asno�� kopca
    int extractMin(int* pq, int* dist, int& size); // Metoda usuwaj�ca i zwracaj�ca element minimalny z kopca
    void decreaseKey(int* pq, int* dist, int size, int vertex, int newDist); // Metoda zmniejszaj�ca warto�� klucza w kopcu

    // Metody pomocnicze do kopca dla par (int, int)
    void swap(My_pair<int, int>& a, My_pair<int, int>& b); // Metoda zamieniaj�ca dwie pary
    void heapify(My_pair<int, int>* pq, int* dist, int n, int i); // Metoda przywracaj�ca w�asno�� kopca dla par
    My_pair<int, int> extractMin(My_pair<int, int>* pq, int* dist, int& size); // Metoda usuwaj�ca i zwracaj�ca element minimalny z kopca dla par
    void decreaseKey(My_pair<int, int>* pq, int* dist, int size, int vertex, int newDist); // Metoda zmniejszaj�ca warto�� klucza w kopcu dla par
};

#endif // ALG_DIJKSTRA
