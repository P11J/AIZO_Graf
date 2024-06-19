#include "Kruskal.h"

#include <algorithm> 
#include <iostream>


// Implementacja dla grafu reprezentowanego list�
void Kruskal::kruskalList(ListGraph& graph)
{
    int vertices = graph.vertices; // Liczba wierzcho�k�w w grafie
    int edgesCount = graph.edges; // Liczba kraw�dzi w grafie
    auto* edges = new Edge[edgesCount]; // Dynamiczna alokacja pami�ci dla tablicy kraw�dzi

    int index = 0; // Indeks do dodawania kraw�dzi
    for (int u = 0; u < vertices; ++u)
    {
        for (int i = 0; i < graph.edgeCounts[u]; ++i)
        {
            edges[index].startVertex = u; // Ustawienie wierzcho�ka pocz�tkowego
            edges[index].endVertex = graph.adjacencyList[u][i].first; // Ustawienie wierzcho�ka ko�cowego
            edges[index].weight = graph.adjacencyList[u][i].second; // Ustawienie wagi kraw�dzi
            ++index; // Przej�cie do nast�pnego indeksu
        }
    }

    // Sortowanie kraw�dzi wed�ug wagi
    sort(edges, edges + edgesCount, [](Edge a, Edge b) {
        return a.weight < b.weight;
    });

    auto* subsets = new Subset[vertices]; // Dynamiczna alokacja pami�ci dla tablicy podzbior�w

    // Inicjalizacja podzbior�w - ka�dy wierzcho�ek jest swoim w�asnym poprzednikiem i ma rang� 0
    for (int v = 0; v < vertices; ++v)
    {
        subsets[v].predecessor = v; // Ustawienie poprzednika
        subsets[v].rank = 0; // Ustawienie rangi
    }

    auto* result = new Edge[vertices]; // Dynamiczna alokacja pami�ci dla tablicy wynikowej MST
    int e = 0; // Indeks dla wynikowej tablicy kraw�dzi
    int i = 0; // Indeks dla posortowanych kraw�dzi

    // G��wna p�tla algorytmu Kruskala
    while (e < vertices - 1 && i < edgesCount)
    {
        Edge nextEdge = edges[i++]; // Pobranie kolejnej kraw�dzi
        int x = findSet(subsets, nextEdge.startVertex); // Znalezienie zbioru dla wierzcho�ka pocz�tkowego
        int y = findSet(subsets, nextEdge.endVertex); // Znalezienie zbioru dla wierzcho�ka ko�cowego

        // Je�li wierzcho�ki nie nale�� do tego samego zbioru, dodaj kraw�d� do MST
        if (x != y)
        {
            result[e++] = nextEdge; // Dodanie kraw�dzi do wyniku
            join(subsets, x, y); // Po��czenie zbior�w
        }
    }

    // Wy�wietlenie wynik�w

    displayList(result, e);


    // Zwolnienie zaalokowanej pami�ci
    delete[] edges;
    delete[] subsets;
    delete[] result;
}

void Kruskal::displayList(Edge* result, int e){
    cout << "Krawedzie wchodzace w sklad minimalnego drzewa rozpinajacego (MST):\n";
    for (int j = 0; j < e; ++j)
    {
        cout << result[j].startVertex << " -- " << result[j].endVertex << " == " << result[j].weight << endl;
    }
}

// Implementacja metody kruskalMatrix dla grafu reprezentowanego macierz�
void Kruskal::kruskalMatrix(MatrixGraph& graph)
{
    int vertices = graph.vertices; // Liczba wierzcho�k�w w grafie
    int edgesCount = graph.edges; // Liczba kraw�dzi w grafie
    auto* edges = new Edge[edgesCount]; // Dynamiczna alokacja pami�ci dla tablicy kraw�dzi

    int index = 0; // Indeks do dodawania kraw�dzi
    for (int u = 0; u < vertices; ++u)
    {
        for (int v = 0; v < vertices; ++v)
        {
            if (graph.incidenceMatrix[u][v] != 0)
            {
                edges[index].startVertex = u; // Ustawienie wierzcho�ka pocz�tkowego
                edges[index].endVertex = v; // Ustawienie wierzcho�ka ko�cowego
                edges[index].weight = graph.incidenceMatrix[u][v]; // Ustawienie wagi kraw�dzi
                ++index; // Przej�cie do nast�pnego indeksu
            }
        }
    }

    // Sortowanie kraw�dzi wed�ug wagi
    sort(edges, edges + edgesCount, [](Edge a, Edge b) {
        return a.weight < b.weight;
    });

    auto* subsets = new Subset[vertices]; // Dynamiczna alokacja pami�ci dla tablicy podzbior�w

    // Inicjalizacja podzbior�w - ka�dy wierzcho�ek jest swoim w�asnym poprzednikiem i ma rang� 0
    for (int v = 0; v < vertices; ++v)
    {
        subsets[v].predecessor = v; // Ustawienie poprzednika
        subsets[v].rank = 0; // Ustawienie rangi
    }

    auto* result = new Edge[vertices]; // Dynamiczna alokacja pami�ci dla tablicy wynikowej MST
    int e = 0; // Indeks dla wynikowej tablicy kraw�dzi
    int i = 0; // Indeks dla posortowanych kraw�dzi

    // G��wna p�tla algorytmu Kruskala
    while (e < vertices - 1 && i < edgesCount)
    {
        Edge nextEdge = edges[i++]; // Pobranie kolejnej kraw�dzi
        int x = findSet(subsets, nextEdge.startVertex); // Znalezienie zbioru dla wierzcho�ka pocz�tkowego
        int y = findSet(subsets, nextEdge.endVertex); // Znalezienie zbioru dla wierzcho�ka ko�cowego

        // Je�li wierzcho�ki nie nale�� do tego samego zbioru, dodaj kraw�d� do MST
        if (x != y)
        {
            result[e++] = nextEdge; // Dodanie kraw�dzi do wyniku
            join(subsets, x, y); // Po��czenie zbior�w
        }
    }

    // Wy�wietlenie wynik�w

    displayMatrix(result, e);


    // Zwolnienie zaalokowanej pami�ci
    delete[] edges;
    delete[] subsets;
    delete[] result;
}

void Kruskal::displayMatrix(Edge* result, int e){
    cout << "Krawedzie wchodzace w sklad minimalnego drzewa rozpinajacego (MST):\n";
    for (int j = 0; j < e; ++j)
    {
        cout << result[j].startVertex << " -- " << result[j].endVertex << " == " << result[j].weight << endl;
    }
}

// Funkcja pomocnicza do znajdowania zbioru elementu i
int Kruskal::findSet(Subset subsets[], int i)
{
    // Znalezienie korzenia i ustawienie poprzednik�w w celu kompresji �cie�ki
    if (subsets[i].predecessor != i)
    {
        subsets[i].predecessor = findSet(subsets, subsets[i].predecessor);
    }
    return subsets[i].predecessor;
}

// Funkcja pomocnicza do ��czenia dw�ch zbior�w x i y
void Kruskal::join(Subset subsets[], int x, int y)
{
    int xroot = findSet(subsets, x); // Znalezienie korzenia dla zbioru x
    int yroot = findSet(subsets, y); // Znalezienie korzenia dla zbioru y

    // ��czenie drzew wed�ug rangi
    if (subsets[xroot].rank < subsets[yroot].rank)
    {
        subsets[xroot].predecessor = yroot;
    }
    else if (subsets[xroot].rank > subsets[yroot].rank)
    {
        subsets[yroot].predecessor = xroot;
    }
    else
    {
        subsets[yroot].predecessor = xroot;
        subsets[xroot].rank++;
    }
}