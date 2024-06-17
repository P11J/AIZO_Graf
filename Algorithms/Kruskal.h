#ifndef ALG_KRUSKAL
#define ALG_KRUSKAL

#include "Graphs/MatrixGraph.h"
#include "Graphs/ListGraph.h"

// Struktura reprezentuj¹ca krawêdŸ w grafie
struct Krawedz
{
    int pocz; // Wierzcho³ek pocz¹tkowy
    int kon; // Wierzcho³ek koñcowy
    int waga; // Waga krawêdzi
};

// Struktura reprezentuj¹ca podzbiór dla algorytmu Union-Find
struct Podzbior
{
    int poprzednik; // Rodzic w zbiorze
    int rank; // Ranga w zbiorze
};

// Definicja klasy Alg_Kruskal zawieraj¹cej metody dla algorytmu Kruskala
class Alg_Kruskal
{
public:
    // Metoda implementuj¹ca algorytm Kruskala dla grafu macierzowego
    void Kruskal_matrix(MatrixGraph& graph, bool write);

    // Metoda implementuj¹ca algorytm Kruskala dla grafu listowego
    void Kruskal_list(ListGraph& graph, bool write);

private:
    // Funkcja pomocnicza do znajdowania zbioru elementu i
    int znajdz(Podzbior podzbiory[], int i);

    // Funkcja pomocnicza do ³¹czenia dwóch zbiorów x i y
    void zlacz(Podzbior subsets[], int x, int y);
};

#endif // ALG_KRUSKAL
