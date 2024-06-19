#include "Kruskal.h"

#include <algorithm> 
#include <iostream>


// Implementacja dla grafu reprezentowanego list¹
void Kruskal::kruskalList(ListGraph& graph)
{
    int vertices = graph.vertices; // Liczba wierzcho³ków w grafie
    int edgesCount = graph.edges; // Liczba krawêdzi w grafie
    auto* edges = new Edge[edgesCount]; // Dynamiczna alokacja pamiêci dla tablicy krawêdzi

    int index = 0; // Indeks do dodawania krawêdzi
    for (int u = 0; u < vertices; ++u)
    {
        for (int i = 0; i < graph.edgeCounts[u]; ++i)
        {
            edges[index].startVertex = u; // Ustawienie wierzcho³ka pocz¹tkowego
            edges[index].endVertex = graph.adjacencyList[u][i].first; // Ustawienie wierzcho³ka koñcowego
            edges[index].weight = graph.adjacencyList[u][i].second; // Ustawienie wagi krawêdzi
            ++index; // Przejœcie do nastêpnego indeksu
        }
    }

    // Sortowanie krawêdzi wed³ug wagi
    sort(edges, edges + edgesCount, [](Edge a, Edge b) {
        return a.weight < b.weight;
    });

    auto* subsets = new Subset[vertices]; // Dynamiczna alokacja pamiêci dla tablicy podzbiorów

    // Inicjalizacja podzbiorów - ka¿dy wierzcho³ek jest swoim w³asnym poprzednikiem i ma rangê 0
    for (int v = 0; v < vertices; ++v)
    {
        subsets[v].predecessor = v; // Ustawienie poprzednika
        subsets[v].rank = 0; // Ustawienie rangi
    }

    auto* result = new Edge[vertices]; // Dynamiczna alokacja pamiêci dla tablicy wynikowej MST
    int e = 0; // Indeks dla wynikowej tablicy krawêdzi
    int i = 0; // Indeks dla posortowanych krawêdzi

    // G³ówna pêtla algorytmu Kruskala
    while (e < vertices - 1 && i < edgesCount)
    {
        Edge nextEdge = edges[i++]; // Pobranie kolejnej krawêdzi
        int x = findSet(subsets, nextEdge.startVertex); // Znalezienie zbioru dla wierzcho³ka pocz¹tkowego
        int y = findSet(subsets, nextEdge.endVertex); // Znalezienie zbioru dla wierzcho³ka koñcowego

        // Jeœli wierzcho³ki nie nale¿¹ do tego samego zbioru, dodaj krawêdŸ do MST
        if (x != y)
        {
            result[e++] = nextEdge; // Dodanie krawêdzi do wyniku
            join(subsets, x, y); // Po³¹czenie zbiorów
        }
    }

    // Wyœwietlenie wyników

    displayList(result, e);


    // Zwolnienie zaalokowanej pamiêci
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

// Implementacja metody kruskalMatrix dla grafu reprezentowanego macierz¹
void Kruskal::kruskalMatrix(MatrixGraph& graph)
{
    int vertices = graph.vertices; // Liczba wierzcho³ków w grafie
    int edgesCount = graph.edges; // Liczba krawêdzi w grafie
    auto* edges = new Edge[edgesCount]; // Dynamiczna alokacja pamiêci dla tablicy krawêdzi

    int index = 0; // Indeks do dodawania krawêdzi
    for (int u = 0; u < vertices; ++u)
    {
        for (int v = 0; v < vertices; ++v)
        {
            if (graph.incidenceMatrix[u][v] != 0)
            {
                edges[index].startVertex = u; // Ustawienie wierzcho³ka pocz¹tkowego
                edges[index].endVertex = v; // Ustawienie wierzcho³ka koñcowego
                edges[index].weight = graph.incidenceMatrix[u][v]; // Ustawienie wagi krawêdzi
                ++index; // Przejœcie do nastêpnego indeksu
            }
        }
    }

    // Sortowanie krawêdzi wed³ug wagi
    sort(edges, edges + edgesCount, [](Edge a, Edge b) {
        return a.weight < b.weight;
    });

    auto* subsets = new Subset[vertices]; // Dynamiczna alokacja pamiêci dla tablicy podzbiorów

    // Inicjalizacja podzbiorów - ka¿dy wierzcho³ek jest swoim w³asnym poprzednikiem i ma rangê 0
    for (int v = 0; v < vertices; ++v)
    {
        subsets[v].predecessor = v; // Ustawienie poprzednika
        subsets[v].rank = 0; // Ustawienie rangi
    }

    auto* result = new Edge[vertices]; // Dynamiczna alokacja pamiêci dla tablicy wynikowej MST
    int e = 0; // Indeks dla wynikowej tablicy krawêdzi
    int i = 0; // Indeks dla posortowanych krawêdzi

    // G³ówna pêtla algorytmu Kruskala
    while (e < vertices - 1 && i < edgesCount)
    {
        Edge nextEdge = edges[i++]; // Pobranie kolejnej krawêdzi
        int x = findSet(subsets, nextEdge.startVertex); // Znalezienie zbioru dla wierzcho³ka pocz¹tkowego
        int y = findSet(subsets, nextEdge.endVertex); // Znalezienie zbioru dla wierzcho³ka koñcowego

        // Jeœli wierzcho³ki nie nale¿¹ do tego samego zbioru, dodaj krawêdŸ do MST
        if (x != y)
        {
            result[e++] = nextEdge; // Dodanie krawêdzi do wyniku
            join(subsets, x, y); // Po³¹czenie zbiorów
        }
    }

    // Wyœwietlenie wyników

    displayMatrix(result, e);


    // Zwolnienie zaalokowanej pamiêci
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
    // Znalezienie korzenia i ustawienie poprzedników w celu kompresji œcie¿ki
    if (subsets[i].predecessor != i)
    {
        subsets[i].predecessor = findSet(subsets, subsets[i].predecessor);
    }
    return subsets[i].predecessor;
}

// Funkcja pomocnicza do ³¹czenia dwóch zbiorów x i y
void Kruskal::join(Subset subsets[], int x, int y)
{
    int xroot = findSet(subsets, x); // Znalezienie korzenia dla zbioru x
    int yroot = findSet(subsets, y); // Znalezienie korzenia dla zbioru y

    // £¹czenie drzew wed³ug rangi
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