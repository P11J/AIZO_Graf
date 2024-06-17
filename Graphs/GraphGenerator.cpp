#include "GraphGenerator.h"

#include <iostream>
#include <random>

using namespace std;

// Konstruktor klasy Graph inicjalizuj�cy warto�ci
Graph::Graph() : vertices(0), edges(0), startVertices(nullptr), endVertices(nullptr), weights(nullptr)
{
    // Alokacja pami�ci dla tablicy wierzcho�k�w pocz�tkowych, ko�cowych oraz wag
    startVertices = new int[edges];
    endVertices = new int[edges];
    weights = new int[edges];
}

// Destruktor klasy Graph zwalniaj�cy pami��
Graph::~Graph()
{
    delete[] startVertices; // Zwolnienie pami�ci dla tablicy wierzcho�k�w pocz�tkowych
    delete[] endVertices; // Zwolnienie pami�ci dla tablicy wierzcho�k�w ko�cowych
    delete[] weights; // Zwolnienie pami�ci dla tablicy wag
}

// Metoda sprawdzaj�ca, czy graf jest poprawny
bool Graph::isGraphValid() const
{
    // Graf jest poprawny, je�li wszystkie tablice s� niepuste
    return startVertices != nullptr && endVertices != nullptr && weights != nullptr;
}

// Metoda generuj�ca graf o zadanej liczbie wierzcho�k�w i g�sto�ci
void Graph::generateGraph(int vertices2, float density)
{
    std::random_device rd; // Urz�dzenie losuj�ce
    std::mt19937 gen(rd()); // Generator liczb losowych
    std::uniform_real_distribution<float> distribution((float)1, (float)vertices2); // Rozk�ad jednostajny dla wag kraw�dzi

    this->vertices = vertices2; // Ustawienie liczby wierzcho�k�w
    edges = static_cast<int>(density * vertices2 * (vertices2 - 1) / 2); // Obliczenie liczby kraw�dzi na podstawie g�sto�ci

    // Alokacja pami�ci dla tablicy wierzcho�k�w pocz�tkowych, ko�cowych oraz wag
    startVertices = new int[edges];
    endVertices = new int[edges];
    weights = new int[edges];

    // Generowanie minimalnego drzewa rozpinaj�cego
    bool* visited = new bool[vertices2]; // Tablica odwiedzonych wierzcho�k�w
    visited[0] = true; // Oznaczenie zerowego wierzcho�ka jako odwiedzonego

    // Inicjalizacja tablicy odwiedzonych wierzcho�k�w
    for (int i = 1; i < vertices2; ++i)
    {
        visited[i] = false; // Ustawienie wszystkich wierzcho�k�w jako nieodwiedzonych
    }

    int* stack = new int[vertices2]; // Stos do przechowywania wierzcho�k�w podczas DFS
    int stackTop = -1; // Indeks wierzcho�ka na szczycie stosu

    stack[++stackTop] = 0; // Dodanie zerowego wierzcho�ka na stos

    int edgeCount = 0; // Licznik kraw�dzi
    while (stackTop >= 0 && edgeCount < vertices2 - 1)
    {
        int currentVertex = stack[stackTop--]; // Pobranie wierzcho�ka ze szczytu stosu

        // Przegl�d s�siad�w bie��cego wierzcho�ka
        for (int i = vertices2 - 1; i >= 0; --i)
        {
            // Je�li bie��cy wierzcho�ek nie jest r�wny s�siadowi i s�siad nie zosta� odwiedzony
            if (currentVertex != i && !visited[i])
            {
                startVertices[edgeCount] = currentVertex; // Ustawienie wierzcho�ka pocz�tkowego kraw�dzi
                endVertices[edgeCount] = i; // Ustawienie wierzcho�ka ko�cowego kraw�dzi
                weights[edgeCount] = distribution(gen); // Ustawienie wagi kraw�dzi
                edgeCount++; // Zwi�kszenie licznika kraw�dzi

                stack[++stackTop] = i; // Dodanie s�siada na stos
                visited[i] = true; // Oznaczenie s�siada jako odwiedzonego
            }
        }
    }

    delete[] stack; // Zwolnienie pami�ci stosu

    // Dodanie pozosta�ych kraw�dzi, aby osi�gn�� ��dan� g�sto�� i zapewni� sp�jno�� grafu
    for (int i = 1; i < vertices2; ++i)
    {
        // Je�li osi�gni�to maksymaln� liczb� kraw�dzi, przerwij p�tl�
        if (edgeCount >= edges)
            break;

        // Je�li wierzcho�ek nie zosta� odwiedzony
        if (!visited[i])
        {
            int startV = std::uniform_int_distribution<int>(0, i - 1)(gen); // Losowanie wierzcho�ka pocz�tkowego
            startVertices[edgeCount] = startV; // Ustawienie wierzcho�ka pocz�tkowego kraw�dzi
            endVertices[edgeCount] = i; // Ustawienie wierzcho�ka ko�cowego kraw�dzi
            weights[edgeCount] = distribution(gen); // Ustawienie wagi kraw�dzi
            edgeCount++; // Zwi�kszenie licznika kraw�dzi

            visited[i] = true; // Oznaczenie wierzcho�ka jako odwiedzonego
        }
    }

    // Dodanie pozosta�ych kraw�dzi, aby osi�gn�� ��dan� g�sto��
    while (edgeCount < edges)
    {
        int startV = std::uniform_int_distribution<int>(0, vertices2 - 1)(gen); // Losowanie wierzcho�ka pocz�tkowego
        int endV = std::uniform_int_distribution<int>(0, vertices2 - 1)(gen); // Losowanie wierzcho�ka ko�cowego
        if (startV != endV)
        {
            startVertices[edgeCount] = startV; // Ustawienie wierzcho�ka pocz�tkowego kraw�dzi
            endVertices[edgeCount] = endV; // Ustawienie wierzcho�ka ko�cowego kraw�dzi
            weights[edgeCount] = distribution(gen); // Ustawienie wagi kraw�dzi
            edgeCount++; // Zwi�kszenie licznika kraw�dzi
        }
    }
    delete[] visited; // Zwolnienie pami�ci tablicy odwiedzonych wierzcho�k�w
}

