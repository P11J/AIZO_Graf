#ifndef ALG_KRUSKAL
#define ALG_KRUSKAL

#include "Graphs/MatrixGraph.h"
#include "Graphs/ListGraph.h"

// Struktura reprezentuj¹ca krawêdŸ w grafie
struct Edge
{
    int startVertex; // Wierzcho³ek pocz¹tkowy
    int endVertex; // Wierzcho³ek koñcowy
    int weight; // Waga krawêdzi
};

// Struktura reprezentuj¹ca podzbiór dla algorytmu Union-Find
struct Subset
{
    int predecessor; // Rodzic w zbiorze
    int rank; // Ranga w zbiorze
};

// Definicja klasy Kruskal zawieraj¹cej metody dla algorytmu Kruskala
class Kruskal
{
public:
    // Metoda implementuj¹ca algorytm Kruskala dla grafu macierzowego
    void kruskalMatrix(MatrixGraph& graph);

    // Metoda implementuj¹ca algorytm Kruskala dla grafu listowego
    void kruskalList(ListGraph& graph);

private:
    // Funkcja pomocnicza do znajdowania zbioru elementu i
    int findSet(Subset subsets[], int i);

    // Funkcja pomocnicza do ³¹czenia dwóch zbiorów x i y
    void join(Subset subsets[], int x, int y);

    static void displayList(Edge* result, int e);

    static void displayMatrix(Edge* result, int e);
};

#endif // ALG_KRUSKAL
