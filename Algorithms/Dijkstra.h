#ifndef ALG_DIJKSTRA // Zapobiega wielokrotnemu do³¹czaniu pliku nag³ówkowego
#define ALG_DIJKSTRA

#include "Graphs/MatrixGraph.h" // Do³¹czenie pliku nag³ówkowego dla grafu reprezentowanego macierz¹
#include "Graphs/ListGraph.h" // Do³¹czenie pliku nag³ówkowego dla grafu reprezentowanego list¹

// Definicja klasy Alg_Dijkstra zawieraj¹cej metody dla algorytmu Dijkstry
class Alg_Dijkstra
{
public:
    // Metoda implementuj¹ca algorytm Dijkstry dla grafu macierzowego
    void Dijkstra_matrix(MatrixGraph& graph, int start, int end, bool write);

    // Metoda implementuj¹ca algorytm Dijkstry dla grafu listowego
    void Dijkstra_list(ListGraph& graph, int start, int end, bool write);

private:
    // Metody pomocnicze do kopca
    void swap(int& a, int& b); // Metoda zamieniaj¹ca dwie liczby ca³kowite
    void heapify(int* pq, int* dist, int n, int i); // Metoda przywracaj¹ca w³asnoœæ kopca
    int extractMin(int* pq, int* dist, int& size); // Metoda usuwaj¹ca i zwracaj¹ca element minimalny z kopca
    void decreaseKey(int* pq, int* dist, int size, int vertex, int newDist); // Metoda zmniejszaj¹ca wartoœæ klucza w kopcu

    // Metody pomocnicze do kopca dla par (int, int)
    void swap(My_pair<int, int>& a, My_pair<int, int>& b); // Metoda zamieniaj¹ca dwie pary
    void heapify(My_pair<int, int>* pq, int* dist, int n, int i); // Metoda przywracaj¹ca w³asnoœæ kopca dla par
    My_pair<int, int> extractMin(My_pair<int, int>* pq, int* dist, int& size); // Metoda usuwaj¹ca i zwracaj¹ca element minimalny z kopca dla par
    void decreaseKey(My_pair<int, int>* pq, int* dist, int size, int vertex, int newDist); // Metoda zmniejszaj¹ca wartoœæ klucza w kopcu dla par
};

#endif // ALG_DIJKSTRA
