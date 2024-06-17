#include "Kruskal.h"

#include <algorithm> 
#include <iostream>


// Implementacja metody Kruskal_list dla grafu reprezentowanego list�
void Alg_Kruskal::Kruskal_list(ListGraph& graph, bool write)
{
    int V = graph.vertices; // Liczba wierzcho�k�w w grafie
    int E = graph.edges; // Liczba kraw�dzi w grafie
    auto* krawedzie = new Krawedz[E]; // Dynamiczna alokacja pami�ci dla tablicy kraw�dzi

    int index = 0; // Indeks do dodawania kraw�dzi
    for (int u = 0; u < V; ++u)
    {
        for (int i = 0; i < graph.edgeCounts[u]; ++i)
        {
            krawedzie[index].pocz = u; // Ustawienie wierzcho�ka pocz�tkowego
            krawedzie[index].kon = graph.adjacencyList[u][i].first; // Ustawienie wierzcho�ka ko�cowego
            krawedzie[index].waga = graph.adjacencyList[u][i].second; // Ustawienie wagi kraw�dzi
            ++index; // Przej�cie do nast�pnego indeksu
        }
    }

    // Sortowanie kraw�dzi wed�ug wagi
    sort(krawedzie, krawedzie + E, [](Krawedz a, Krawedz b) {
        return a.waga < b.waga;
    });

    auto* podzbiory = new Podzbior[V]; // Dynamiczna alokacja pami�ci dla tablicy podzbior�w

    // Inicjalizacja podzbior�w - ka�dy wierzcho�ek jest swoim w�asnym poprzednikiem i ma rang� 0
    for (int v = 0; v < V; ++v)
    {
        podzbiory[v].poprzednik = v; // Ustawienie poprzednika
        podzbiory[v].rank = 0; // Ustawienie rangi
    }

    auto* wynik = new Krawedz[V]; // Dynamiczna alokacja pami�ci dla tablicy wynikowej MST
    int e = 0; // Indeks dla wynikowej tablicy kraw�dzi
    int i = 0; // Indeks dla posortowanych kraw�dzi

    // G��wna p�tla algorytmu Kruskala
    while (e < V - 1 && i < E)
    {
        Krawedz kolejna_krawedz = krawedzie[i++]; // Pobranie kolejnej kraw�dzi
        int x = znajdz(podzbiory, kolejna_krawedz.pocz); // Znalezienie zbioru dla wierzcho�ka pocz�tkowego
        int y = znajdz(podzbiory, kolejna_krawedz.kon); // Znalezienie zbioru dla wierzcho�ka ko�cowego

        // Je�li wierzcho�ki nie nale�� do tego samego zbioru, dodaj kraw�d� do MST
        if (x != y)
        {
            wynik[e++] = kolejna_krawedz; // Dodanie kraw�dzi do wyniku
            zlacz(podzbiory, x, y); // Po��czenie zbior�w
        }
    }

    // Wy�wietlenie wynik�w, je�li flaga write jest ustawiona na true
    if (write)
    {
        cout << "Krawedzie wchodzace w sklad minimalnego drzewa rozpinajacego (MST):\n";
        for (int j = 0; j < e; ++j)
        {
            cout << wynik[j].pocz << " -- " << wynik[j].kon << " == " << wynik[j].waga << endl;
        }
    }

    // Zwolnienie zaalokowanej pami�ci
    delete[] krawedzie;
    delete[] podzbiory;
    delete[] wynik;
}

// Implementacja metody Kruskal_matrix dla grafu reprezentowanego macierz�
void Alg_Kruskal::Kruskal_matrix(MatrixGraph& graph, bool write)
{
    int V = graph.vertices; // Liczba wierzcho�k�w w grafie
    int E = graph.edges; // Liczba kraw�dzi w grafie
    auto* krawedzie = new Krawedz[E]; // Dynamiczna alokacja pami�ci dla tablicy kraw�dzi

    int index = 0; // Indeks do dodawania kraw�dzi
    for (int u = 0; u < V; ++u)
    {
        for (int v = 0; v < V; ++v)
        {
            if (graph.incidenceMatrix[u][v] != 0)
            {
                krawedzie[index].pocz = u; // Ustawienie wierzcho�ka pocz�tkowego
                krawedzie[index].kon = v; // Ustawienie wierzcho�ka ko�cowego
                krawedzie[index].waga = graph.incidenceMatrix[u][v]; // Ustawienie wagi kraw�dzi
                ++index; // Przej�cie do nast�pnego indeksu
            }
        }
    }

    // Sortowanie kraw�dzi wed�ug wagi
    sort(krawedzie, krawedzie + E, [](Krawedz a, Krawedz b) {
        return a.waga < b.waga;
    });

    auto* podzbiory = new Podzbior[V]; // Dynamiczna alokacja pami�ci dla tablicy podzbior�w

    // Inicjalizacja podzbior�w - ka�dy wierzcho�ek jest swoim w�asnym poprzednikiem i ma rang� 0
    for (int v = 0; v < V; ++v)
    {
        podzbiory[v].poprzednik = v; // Ustawienie poprzednika
        podzbiory[v].rank = 0; // Ustawienie rangi
    }

    auto* wynik = new Krawedz[V]; // Dynamiczna alokacja pami�ci dla tablicy wynikowej MST
    int e = 0; // Indeks dla wynikowej tablicy kraw�dzi
    int i = 0; // Indeks dla posortowanych kraw�dzi

    // G��wna p�tla algorytmu Kruskala
    while (e < V - 1 && i < E)
    {
        Krawedz kolejna_krawedz = krawedzie[i++]; // Pobranie kolejnej kraw�dzi
        int x = znajdz(podzbiory, kolejna_krawedz.pocz); // Znalezienie zbioru dla wierzcho�ka pocz�tkowego
        int y = znajdz(podzbiory, kolejna_krawedz.kon); // Znalezienie zbioru dla wierzcho�ka ko�cowego

        // Je�li wierzcho�ki nie nale�� do tego samego zbioru, dodaj kraw�d� do MST
        if (x != y)
        {
            wynik[e++] = kolejna_krawedz; // Dodanie kraw�dzi do wyniku
            zlacz(podzbiory, x, y); // Po��czenie zbior�w
        }
    }

    // Wy�wietlenie wynik�w, je�li flaga write jest ustawiona na true
    if (write)
    {
        cout << "Krawedzie wchodzace w sklad minimalnego drzewa rozpinajacego (MST):\n";
        for (int j = 0; j < e; ++j)
        {
            cout << wynik[j].pocz << " -- " << wynik[j].kon << " == " << wynik[j].waga << endl;
        }
    }

    // Zwolnienie zaalokowanej pami�ci
    delete[] krawedzie;
    delete[] podzbiory;
    delete[] wynik;
}

// Funkcja pomocnicza do znajdowania zbioru elementu i
int Alg_Kruskal::znajdz(Podzbior podzbiory[], int i)
{
    // Znalezienie korzenia i ustawienie poprzednik�w w celu kompresji �cie�ki
    if (podzbiory[i].poprzednik != i)
    {
        podzbiory[i].poprzednik = znajdz(podzbiory, podzbiory[i].poprzednik);
    }
    return podzbiory[i].poprzednik;
}

// Funkcja pomocnicza do ��czenia dw�ch zbior�w x i y
void Alg_Kruskal::zlacz(Podzbior podzbiory[], int x, int y)
{
    int xroot = znajdz(podzbiory, x); // Znalezienie korzenia dla zbioru x
    int yroot = znajdz(podzbiory, y); // Znalezienie korzenia dla zbioru y

    // ��czenie drzew wed�ug rangi
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