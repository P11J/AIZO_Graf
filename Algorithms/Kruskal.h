#ifndef ALG_KRUSKAL
#define ALG_KRUSKAL

#include "Graphs/MatrixGraph.h"
#include "Graphs/ListGraph.h"

// Struktura reprezentuj�ca kraw�d� w grafie
struct Edge
{
    int startVertex; // Wierzcho�ek pocz�tkowy
    int endVertex; // Wierzcho�ek ko�cowy
    int weight; // Waga kraw�dzi
};

// Struktura reprezentuj�ca podzbi�r dla algorytmu Union-Find
struct Subset
{
    int predecessor; // Rodzic w zbiorze
    int rank; // Ranga w zbiorze
};

// Definicja klasy Kruskal zawieraj�cej metody dla algorytmu Kruskala
class Kruskal
{
public:
    // Metoda implementuj�ca algorytm Kruskala dla grafu macierzowego
    void kruskalMatrix(MatrixGraph& graph);

    // Metoda implementuj�ca algorytm Kruskala dla grafu listowego
    void kruskalList(ListGraph& graph);

private:
    // Funkcja pomocnicza do znajdowania zbioru elementu i
    int findSet(Subset subsets[], int i);

    // Funkcja pomocnicza do ��czenia dw�ch zbior�w x i y
    void join(Subset subsets[], int x, int y);

    static void displayList(Edge* result, int e);

    static void displayMatrix(Edge* result, int e);
};

#endif // ALG_KRUSKAL
