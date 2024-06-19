#include "Prim.h" // Do³¹czenie pliku nag³ówkowego dla algorytmu Prima

#include <iostream> // Do³¹czenie biblioteki wejœcia-wyjœcia
#include <iomanip> // Do³¹czenie biblioteki dla manipulacji strumieniami wejœcia-wyjœcia

// Implementacja metody primList dla grafu reprezentowanego list¹
void Prim::primList(ListGraph& graph)
{
    int vertices = graph.vertices; // Liczba wierzcho³ków w grafie

    // Dynamiczna alokacja pamiêci dla tablicy list s¹siedztwa
    auto*** adjacencyList = new MyPair<int, int>** [vertices];
    for (int i = 0; i < vertices; ++i)
    {
        adjacencyList[i] = new MyPair<int, int>* [graph.edgeCounts[i]]; // Alokacja dla krawêdzi wychodz¹cych z wierzcho³ka
        for (int j = 0; j < graph.edgeCounts[i]; ++j)
        {
            adjacencyList[i][j] = &graph.adjacencyList[i][j]; // Inicjalizacja wskaŸnika do listy s¹siedztwa
        }
    }

    // Dynamiczna alokacja pamiêci dla tablicy poprzedników, kluczy i tablicy MST
    int* predecessor = new int[vertices];
    int* key = new int[vertices];
    bool* inMST = new bool[vertices];

    // Inicjalizacja tablicy poprzedników, kluczy i tablicy MST
    for (int i = 0; i < vertices; ++i)
    {
        predecessor[i] = -1; // Inicjalizacja poprzednika jako -1, co oznacza brak poprzednika
        key[i] = INT_MAX; // Inicjalizacja klucza jako nieskoñczonoœæ
        inMST[i] = false; // Inicjalizacja MST jako false
    }

    int u = 0; // Zmienna przechowuj¹ca wierzcho³ek u
    int v = 0; // Zmienna przechowuj¹ca wierzcho³ek v
    int weight = 0; // Zmienna przechowuj¹ca wagê krawêdzi

    key[0] = 0; // Ustawienie klucza dla wierzcho³ka startowego

    // G³ówna pêtla algorytmu Prima
    for (int i = 0; i < vertices - 1; ++i)
    {
        u = minKey(key, inMST, vertices); // Znalezienie wierzcho³ka o minimalnym kluczu, który nie jest w MST
        inMST[u] = true; // Dodanie wierzcho³ka u do MST

        // Przegl¹d s¹siadów wierzcho³ka u
        for (int j = 0; j < graph.edgeCounts[u]; ++j)
        {
            MyPair<int, int>* neighbor = adjacencyList[u][j]; // Pobranie s¹siada wierzcho³ka u
            v = neighbor->first; // Pobranie numeru wierzcho³ka s¹siada
            weight = neighbor->second; // Pobranie wagi krawêdzi do s¹siada

            // Aktualizacja klucza i poprzednika s¹siada v, jeœli warunki s¹ spe³nione
            if (!inMST[v] && weight < key[v])
            {
                predecessor[v] = u; // Ustawienie poprzednika
                key[v] = weight; // Zaktualizowanie klucza
            }
        }
    }

    // Wyœwietlenie wyników

    displayList(vertices, predecessor, key);


    // Zwolnienie zaalokowanej pamiêci dla tablicy list s¹siedztwa
    for (int i = 0; i < vertices; ++i)
    {
        delete[] adjacencyList[i];
    }
    delete[] adjacencyList;
    delete[] predecessor;
    delete[] key;
    delete[] inMST;
}

void Prim::displayList(int vertices, int* predecessor, int* key){
    cout << "Krawedz: Waga" << endl;
    for (int i = 1; i < vertices; ++i)
    {
        if (predecessor[i] != -1)
        {
            cout << setw(3) << predecessor[i] << ":" << i << setw(5) << key[i] << endl; // Wyœwietlenie krawêdzi i jej wagi
        }
    }
}

// Implementacja dla grafu reprezentowanego macierz¹
void Prim::primMatrix(MatrixGraph& graph)
{
    int vertices = graph.vertices; // Liczba wierzcho³ków w grafie
    int edges = graph.edges; // Liczba krawêdzi w grafie

    // Dynamiczna alokacja pamiêci dla tablicy poprzedników, kluczy i tablicy MST
    int* predecessor = new int[vertices];
    int* key = new int[vertices];
    bool* inMST = new bool[vertices];

    // Inicjalizacja tablicy poprzedników, kluczy i tablicy MST
    for (int i = 0; i < vertices; ++i)
    {
        predecessor[i] = -1; // Inicjalizacja poprzednika jako -1, co oznacza brak poprzednika
        key[i] = INT_MAX; // Inicjalizacja klucza jako nieskoñczonoœæ
        inMST[i] = false; // Inicjalizacja MST jako false
    }

    key[0] = 0; // Ustawienie klucza dla wierzcho³ka startowego

    // G³ówna pêtla algorytmu Prima
    for (int count = 0; count < vertices - 1; ++count)
    {
        int u = minKey(key, inMST, vertices); // Znalezienie wierzcho³ka o minimalnym kluczu, który nie jest w MST
        inMST[u] = true; // Dodanie wierzcho³ka u do MST

        // Przegl¹d wszystkich krawêdzi w grafie
        for (int j = 0; j < edges; ++j)
        {
            // Sprawdzenie, czy wierzcho³ek u jest koñcem krawêdzi
            if (graph.incidenceMatrix[u][j] == 1)
            {
                int v = -1; // Zmienna przechowuj¹ca numer s¹siada

                // Znalezienie wierzcho³ka v, który jest drugim koñcem krawêdzi
                for (int i = 0; i < vertices; ++i)
                {
                    if (graph.incidenceMatrix[i][j] == 1 && i != u)
                    {
                        v = i; // Ustawienie numeru s¹siada
                        break;
                    }
                }

                // Aktualizacja klucza i poprzednika s¹siada v, jeœli warunki s¹ spe³nione
                if (v != -1 && !inMST[v] && graph.weightsMatrix[j] < key[v])
                {
                    key[v] = graph.weightsMatrix[j]; // Zaktualizowanie klucza
                    predecessor[v] = u; // Ustawienie poprzednika
                }
            }
        }
    }

    // Wyœwietlenie wyników
    displayMatrix(vertices, predecessor, key);

    // Zwolnienie zaalokowanej pamiêci
    delete[] predecessor;
    delete[] key;
    delete[] inMST;
}

void Prim::displayMatrix(int vertices, int* predecessor, int* key){
    cout << "Krawedz: Waga" << endl;
    for (int i = 1; i < vertices; ++i)
    {
        if (predecessor[i] != -1)
        {
            cout << setw(3) << predecessor[i] << ":" << i << setw(5) << key[i] << endl; // Wyœwietlenie krawêdzi i jej wagi
        }
    }
}

// Implementacja metody minKey do znajdowania wierzcho³ka o minimalnym kluczu
int Prim::minKey(const int key[], const bool inMST[], int vertices)
{
    int min = INT_MAX; // Inicjalizacja minimalnej wartoœci jako nieskoñczonoœæ
    int minIndex = -1; // Inicjalizacja indeksu minimalnej wartoœci jako -1

    // Przegl¹d wszystkich wierzcho³ków
    for (int v = 0; v < vertices; ++v)
    {
        // Jeœli wierzcho³ek nie jest w MST i jego klucz jest mniejszy ni¿ aktualne minimum
        if (!inMST[v] && key[v] < min)
        {
            min = key[v]; // Aktualizacja minimalnej wartoœci
            minIndex = v; // Aktualizacja indeksu minimalnej wartoœci
        }
    }

    return minIndex; // Zwrócenie indeksu wierzcho³ka o minimalnym kluczu
}
