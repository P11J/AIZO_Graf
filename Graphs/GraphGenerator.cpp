#include "GraphGenerator.h"

#include <iostream>
#include <random>

using namespace std;

// Konstruktor klasy Graph inicjalizuj¹cy wartoœci
Graph::Graph() : vertices(0), edges(0), startVertices(nullptr), endVertices(nullptr), weights(nullptr)
{
    // Alokacja pamiêci dla tablicy wierzcho³ków pocz¹tkowych, koñcowych oraz wag
    startVertices = new int[edges];
    endVertices = new int[edges];
    weights = new int[edges];
}

// Destruktor klasy Graph zwalniaj¹cy pamiêæ
Graph::~Graph()
{
    delete[] startVertices; // Zwolnienie pamiêci dla tablicy wierzcho³ków pocz¹tkowych
    delete[] endVertices; // Zwolnienie pamiêci dla tablicy wierzcho³ków koñcowych
    delete[] weights; // Zwolnienie pamiêci dla tablicy wag
}

// Metoda sprawdzaj¹ca, czy graf jest poprawny
bool Graph::isGraphValid() const
{
    // Graf jest poprawny, jeœli wszystkie tablice s¹ niepuste
    return startVertices != nullptr && endVertices != nullptr && weights != nullptr;
}

// Metoda generuj¹ca graf o zadanej liczbie wierzcho³ków i gêstoœci
void Graph::generateGraph(int vertices2, float density)
{
    std::random_device rd; // Urz¹dzenie losuj¹ce
    std::mt19937 gen(rd()); // Generator liczb losowych
    std::uniform_real_distribution<float> distribution((float)1, (float)vertices2); // Rozk³ad jednostajny dla wag krawêdzi

    this->vertices = vertices2; // Ustawienie liczby wierzcho³ków
    edges = static_cast<int>(density * vertices2 * (vertices2 - 1) / 2); // Obliczenie liczby krawêdzi na podstawie gêstoœci

    // Alokacja pamiêci dla tablicy wierzcho³ków pocz¹tkowych, koñcowych oraz wag
    startVertices = new int[edges];
    endVertices = new int[edges];
    weights = new int[edges];

    // Generowanie minimalnego drzewa rozpinaj¹cego
    bool* visited = new bool[vertices2]; // Tablica odwiedzonych wierzcho³ków
    visited[0] = true; // Oznaczenie zerowego wierzcho³ka jako odwiedzonego

    // Inicjalizacja tablicy odwiedzonych wierzcho³ków
    for (int i = 1; i < vertices2; ++i)
    {
        visited[i] = false; // Ustawienie wszystkich wierzcho³ków jako nieodwiedzonych
    }

    int* stack = new int[vertices2]; // Stos do przechowywania wierzcho³ków podczas DFS
    int stackTop = -1; // Indeks wierzcho³ka na szczycie stosu

    stack[++stackTop] = 0; // Dodanie zerowego wierzcho³ka na stos

    int edgeCount = 0; // Licznik krawêdzi
    while (stackTop >= 0 && edgeCount < vertices2 - 1)
    {
        int currentVertex = stack[stackTop--]; // Pobranie wierzcho³ka ze szczytu stosu

        // Przegl¹d s¹siadów bie¿¹cego wierzcho³ka
        for (int i = vertices2 - 1; i >= 0; --i)
        {
            // Jeœli bie¿¹cy wierzcho³ek nie jest równy s¹siadowi i s¹siad nie zosta³ odwiedzony
            if (currentVertex != i && !visited[i])
            {
                startVertices[edgeCount] = currentVertex; // Ustawienie wierzcho³ka pocz¹tkowego krawêdzi
                endVertices[edgeCount] = i; // Ustawienie wierzcho³ka koñcowego krawêdzi
                weights[edgeCount] = distribution(gen); // Ustawienie wagi krawêdzi
                edgeCount++; // Zwiêkszenie licznika krawêdzi

                stack[++stackTop] = i; // Dodanie s¹siada na stos
                visited[i] = true; // Oznaczenie s¹siada jako odwiedzonego
            }
        }
    }

    delete[] stack; // Zwolnienie pamiêci stosu

    // Dodanie pozosta³ych krawêdzi, aby osi¹gn¹æ ¿¹dan¹ gêstoœæ i zapewniæ spójnoœæ grafu
    for (int i = 1; i < vertices2; ++i)
    {
        // Jeœli osi¹gniêto maksymaln¹ liczbê krawêdzi, przerwij pêtlê
        if (edgeCount >= edges)
            break;

        // Jeœli wierzcho³ek nie zosta³ odwiedzony
        if (!visited[i])
        {
            int startV = std::uniform_int_distribution<int>(0, i - 1)(gen); // Losowanie wierzcho³ka pocz¹tkowego
            startVertices[edgeCount] = startV; // Ustawienie wierzcho³ka pocz¹tkowego krawêdzi
            endVertices[edgeCount] = i; // Ustawienie wierzcho³ka koñcowego krawêdzi
            weights[edgeCount] = distribution(gen); // Ustawienie wagi krawêdzi
            edgeCount++; // Zwiêkszenie licznika krawêdzi

            visited[i] = true; // Oznaczenie wierzcho³ka jako odwiedzonego
        }
    }

    // Dodanie pozosta³ych krawêdzi, aby osi¹gn¹æ ¿¹dan¹ gêstoœæ
    while (edgeCount < edges)
    {
        int startV = std::uniform_int_distribution<int>(0, vertices2 - 1)(gen); // Losowanie wierzcho³ka pocz¹tkowego
        int endV = std::uniform_int_distribution<int>(0, vertices2 - 1)(gen); // Losowanie wierzcho³ka koñcowego
        if (startV != endV)
        {
            startVertices[edgeCount] = startV; // Ustawienie wierzcho³ka pocz¹tkowego krawêdzi
            endVertices[edgeCount] = endV; // Ustawienie wierzcho³ka koñcowego krawêdzi
            weights[edgeCount] = distribution(gen); // Ustawienie wagi krawêdzi
            edgeCount++; // Zwiêkszenie licznika krawêdzi
        }
    }
    delete[] visited; // Zwolnienie pamiêci tablicy odwiedzonych wierzcho³ków
}

