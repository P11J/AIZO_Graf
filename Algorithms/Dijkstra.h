#ifndef ALG_DIJKSTRA // Zapobiega wielokrotnemu dołączaniu pliku nagłówkowego
#define ALG_DIJKSTRA

#include "Graphs/MatrixGraph.h" // Dołączenie pliku nagłówkowego dla grafu reprezentowanego macierzą
#include "Graphs/ListGraph.h" // Dołączenie pliku nagłówkowego dla grafu reprezentowanego listą

// Definicja klasy Alg_Dijkstra zawierającej metody dla algorytmu Dijkstry
class Alg_Dijkstra
{
public:
    // Metoda implementująca algorytm Dijkstry dla grafu macierzowego
    void Dijkstra_matrix(MatrixGraph& graph, int start, int end, bool write);

    // Metoda implementująca algorytm Dijkstry dla grafu listowego
    void Dijkstra_list(ListGraph& graph, int start, int end, bool write);

private:
    // Metody pomocnicze do kopca
    void swap(int& a, int& b); // Metoda zamieniająca dwie liczby całkowite
    void heapify(int* pq, int* dist, int n, int i); // Metoda przywracająca własność kopca
    int extractMin(int* pq, int* dist, int& size); // Metoda usuwająca i zwracająca element minimalny z kopca
    void decreaseKey(int* pq, int* dist, int size, int vertex, int newDist); // Metoda zmniejszająca wartość klucza w kopcu

    // Metody pomocnicze do kopca dla par (int, int)
    void swap(My_pair<int, int>& a, My_pair<int, int>& b); // Metoda zamieniająca dwie pary
    void heapify(My_pair<int, int>* pq, int* dist, int n, int i); // Metoda przywracająca własność kopca dla par
    My_pair<int, int> extractMin(My_pair<int, int>* pq, int* dist, int& size); // Metoda usuwająca i zwracająca element minimalny z kopca dla par
    void decreaseKey(My_pair<int, int>* pq, int* dist, int size, int vertex, int newDist); // Metoda zmniejszająca wartość klucza w kopcu dla par
};

#endif // ALG_DIJKSTRA
