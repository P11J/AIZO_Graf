#include "Kruskal.h"

#include <algorithm> 
#include <iostream>


// Implementacja metody Kruskal_list dla grafu reprezentowanego list¹
void Alg_Kruskal::Kruskal_list(ListGraph& graph, bool write)
{
    int V = graph.vertices; // Liczba wierzcho³ków w grafie
    int E = graph.edges; // Liczba krawêdzi w grafie
    auto* krawedzie = new Krawedz[E]; // Dynamiczna alokacja pamiêci dla tablicy krawêdzi

    int index = 0; // Indeks do dodawania krawêdzi
    for (int u = 0; u < V; ++u)
    {
        for (int i = 0; i < graph.edgeCounts[u]; ++i)
        {
            krawedzie[index].pocz = u; // Ustawienie wierzcho³ka pocz¹tkowego
            krawedzie[index].kon = graph.adjacencyList[u][i].first; // Ustawienie wierzcho³ka koñcowego
            krawedzie[index].waga = graph.adjacencyList[u][i].second; // Ustawienie wagi krawêdzi
            ++index; // Przejœcie do nastêpnego indeksu
        }
    }

    // Sortowanie krawêdzi wed³ug wagi
    sort(krawedzie, krawedzie + E, [](Krawedz a, Krawedz b) {
        return a.waga < b.waga;
    });

    auto* podzbiory = new Podzbior[V]; // Dynamiczna alokacja pamiêci dla tablicy podzbiorów

    // Inicjalizacja podzbiorów - ka¿dy wierzcho³ek jest swoim w³asnym poprzednikiem i ma rangê 0
    for (int v = 0; v < V; ++v)
    {
        podzbiory[v].poprzednik = v; // Ustawienie poprzednika
        podzbiory[v].rank = 0; // Ustawienie rangi
    }

    auto* wynik = new Krawedz[V]; // Dynamiczna alokacja pamiêci dla tablicy wynikowej MST
    int e = 0; // Indeks dla wynikowej tablicy krawêdzi
    int i = 0; // Indeks dla posortowanych krawêdzi

    // G³ówna pêtla algorytmu Kruskala
    while (e < V - 1 && i < E)
    {
        Krawedz kolejna_krawedz = krawedzie[i++]; // Pobranie kolejnej krawêdzi
        int x = znajdz(podzbiory, kolejna_krawedz.pocz); // Znalezienie zbioru dla wierzcho³ka pocz¹tkowego
        int y = znajdz(podzbiory, kolejna_krawedz.kon); // Znalezienie zbioru dla wierzcho³ka koñcowego

        // Jeœli wierzcho³ki nie nale¿¹ do tego samego zbioru, dodaj krawêdŸ do MST
        if (x != y)
        {
            wynik[e++] = kolejna_krawedz; // Dodanie krawêdzi do wyniku
            zlacz(podzbiory, x, y); // Po³¹czenie zbiorów
        }
    }

    // Wyœwietlenie wyników, jeœli flaga write jest ustawiona na true
    if (write)
    {
        cout << "Krawedzie wchodzace w sklad minimalnego drzewa rozpinajacego (MST):\n";
        for (int j = 0; j < e; ++j)
        {
            cout << wynik[j].pocz << " -- " << wynik[j].kon << " == " << wynik[j].waga << endl;
        }
    }

    // Zwolnienie zaalokowanej pamiêci
    delete[] krawedzie;
    delete[] podzbiory;
    delete[] wynik;
}

// Implementacja metody Kruskal_matrix dla grafu reprezentowanego macierz¹
void Alg_Kruskal::Kruskal_matrix(MatrixGraph& graph, bool write)
{
    int V = graph.vertices; // Liczba wierzcho³ków w grafie
    int E = graph.edges; // Liczba krawêdzi w grafie
    auto* krawedzie = new Krawedz[E]; // Dynamiczna alokacja pamiêci dla tablicy krawêdzi

    int index = 0; // Indeks do dodawania krawêdzi
    for (int u = 0; u < V; ++u)
    {
        for (int v = 0; v < V; ++v)
        {
            if (graph.incidenceMatrix[u][v] != 0)
            {
                krawedzie[index].pocz = u; // Ustawienie wierzcho³ka pocz¹tkowego
                krawedzie[index].kon = v; // Ustawienie wierzcho³ka koñcowego
                krawedzie[index].waga = graph.incidenceMatrix[u][v]; // Ustawienie wagi krawêdzi
                ++index; // Przejœcie do nastêpnego indeksu
            }
        }
    }

    // Sortowanie krawêdzi wed³ug wagi
    sort(krawedzie, krawedzie + E, [](Krawedz a, Krawedz b) {
        return a.waga < b.waga;
    });

    auto* podzbiory = new Podzbior[V]; // Dynamiczna alokacja pamiêci dla tablicy podzbiorów

    // Inicjalizacja podzbiorów - ka¿dy wierzcho³ek jest swoim w³asnym poprzednikiem i ma rangê 0
    for (int v = 0; v < V; ++v)
    {
        podzbiory[v].poprzednik = v; // Ustawienie poprzednika
        podzbiory[v].rank = 0; // Ustawienie rangi
    }

    auto* wynik = new Krawedz[V]; // Dynamiczna alokacja pamiêci dla tablicy wynikowej MST
    int e = 0; // Indeks dla wynikowej tablicy krawêdzi
    int i = 0; // Indeks dla posortowanych krawêdzi

    // G³ówna pêtla algorytmu Kruskala
    while (e < V - 1 && i < E)
    {
        Krawedz kolejna_krawedz = krawedzie[i++]; // Pobranie kolejnej krawêdzi
        int x = znajdz(podzbiory, kolejna_krawedz.pocz); // Znalezienie zbioru dla wierzcho³ka pocz¹tkowego
        int y = znajdz(podzbiory, kolejna_krawedz.kon); // Znalezienie zbioru dla wierzcho³ka koñcowego

        // Jeœli wierzcho³ki nie nale¿¹ do tego samego zbioru, dodaj krawêdŸ do MST
        if (x != y)
        {
            wynik[e++] = kolejna_krawedz; // Dodanie krawêdzi do wyniku
            zlacz(podzbiory, x, y); // Po³¹czenie zbiorów
        }
    }

    // Wyœwietlenie wyników, jeœli flaga write jest ustawiona na true
    if (write)
    {
        cout << "Krawedzie wchodzace w sklad minimalnego drzewa rozpinajacego (MST):\n";
        for (int j = 0; j < e; ++j)
        {
            cout << wynik[j].pocz << " -- " << wynik[j].kon << " == " << wynik[j].waga << endl;
        }
    }

    // Zwolnienie zaalokowanej pamiêci
    delete[] krawedzie;
    delete[] podzbiory;
    delete[] wynik;
}

// Funkcja pomocnicza do znajdowania zbioru elementu i
int Alg_Kruskal::znajdz(Podzbior podzbiory[], int i)
{
    // Znalezienie korzenia i ustawienie poprzedników w celu kompresji œcie¿ki
    if (podzbiory[i].poprzednik != i)
    {
        podzbiory[i].poprzednik = znajdz(podzbiory, podzbiory[i].poprzednik);
    }
    return podzbiory[i].poprzednik;
}

// Funkcja pomocnicza do ³¹czenia dwóch zbiorów x i y
void Alg_Kruskal::zlacz(Podzbior podzbiory[], int x, int y)
{
    int xroot = znajdz(podzbiory, x); // Znalezienie korzenia dla zbioru x
    int yroot = znajdz(podzbiory, y); // Znalezienie korzenia dla zbioru y

    // £¹czenie drzew wed³ug rangi
    if (podzbiory[xroot].rank < podzbiory[yroot].rank)
    {
        podzbiory[xroot].poprzednik = yroot;
    }
    else if (podzbiory[xroot].rank > podzbiory[yroot].rank)
    {
        podzbiory[yroot].poprzednik = xroot;
    }
    else
    {
        podzbiory[yroot].poprzednik = xroot;
        podzbiory[xroot].rank++;
    }
}