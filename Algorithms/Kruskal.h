#ifndef ALG_KRUSKAL
#define ALG_KRUSKAL

#include "Graphs/MatrixGraph.h"
#include "Graphs/ListGraph.h"

// Struktura reprezentuj�ca kraw�d� w grafie
struct Krawedz
{
    int pocz; // Wierzcho�ek pocz�tkowy
    int kon; // Wierzcho�ek ko�cowy
    int waga; // Waga kraw�dzi
};

// Struktura reprezentuj�ca podzbi�r dla algorytmu Union-Find
struct Podzbior
{
    int poprzednik; // Rodzic w zbiorze
    int rank; // Ranga w zbiorze
};

// Definicja klasy Alg_Kruskal zawieraj�cej metody dla algorytmu Kruskala
class Alg_Kruskal
{
public:
    // Metoda implementuj�ca algorytm Kruskala dla grafu macierzowego
    void Kruskal_matrix(MatrixGraph& graph, bool write);

    // Metoda implementuj�ca algorytm Kruskala dla grafu listowego
    void Kruskal_list(ListGraph& graph, bool write);

private:
    // Funkcja pomocnicza do znajdowania zbioru elementu i
    int znajdz(Podzbior podzbiory[], int i);

    // Funkcja pomocnicza do ��czenia dw�ch zbior�w x i y
    void zlacz(Podzbior subsets[], int x, int y);
};

#endif // ALG_KRUSKAL
