#include "Prim.h" // Do��czenie pliku nag��wkowego dla algorytmu Prima

#include <iostream> // Do��czenie biblioteki wej�cia-wyj�cia
#include <iomanip> // Do��czenie biblioteki dla manipulacji strumieniami wej�cia-wyj�cia

// Implementacja metody primList dla grafu reprezentowanego list�
void Prim::primList(ListGraph& graph)
{
    int vertices = graph.vertices; // Liczba wierzcho�k�w w grafie

    // Dynamiczna alokacja pami�ci dla tablicy list s�siedztwa
    auto*** adjacencyList = new MyPair<int, int>** [vertices];
    for (int i = 0; i < vertices; ++i)
    {
        adjacencyList[i] = new MyPair<int, int>* [graph.edgeCounts[i]]; // Alokacja dla kraw�dzi wychodz�cych z wierzcho�ka
        for (int j = 0; j < graph.edgeCounts[i]; ++j)
        {
            adjacencyList[i][j] = &graph.adjacencyList[i][j]; // Inicjalizacja wska�nika do listy s�siedztwa
        }
    }

    // Dynamiczna alokacja pami�ci dla tablicy poprzednik�w, kluczy i tablicy MST
    int* predecessor = new int[vertices];
    int* key = new int[vertices];
    bool* inMST = new bool[vertices];

    // Inicjalizacja tablicy poprzednik�w, kluczy i tablicy MST
    for (int i = 0; i < vertices; ++i)
    {
        predecessor[i] = -1; // Inicjalizacja poprzednika jako -1, co oznacza brak poprzednika
        key[i] = INT_MAX; // Inicjalizacja klucza jako niesko�czono��
        inMST[i] = false; // Inicjalizacja MST jako false
    }

    int u = 0; // Zmienna przechowuj�ca wierzcho�ek u
    int v = 0; // Zmienna przechowuj�ca wierzcho�ek v
    int weight = 0; // Zmienna przechowuj�ca wag� kraw�dzi

    key[0] = 0; // Ustawienie klucza dla wierzcho�ka startowego

    // G��wna p�tla algorytmu Prima
    for (int i = 0; i < vertices - 1; ++i)
    {
        u = minKey(key, inMST, vertices); // Znalezienie wierzcho�ka o minimalnym kluczu, kt�ry nie jest w MST
        inMST[u] = true; // Dodanie wierzcho�ka u do MST

        // Przegl�d s�siad�w wierzcho�ka u
        for (int j = 0; j < graph.edgeCounts[u]; ++j)
        {
            MyPair<int, int>* neighbor = adjacencyList[u][j]; // Pobranie s�siada wierzcho�ka u
            v = neighbor->first; // Pobranie numeru wierzcho�ka s�siada
            weight = neighbor->second; // Pobranie wagi kraw�dzi do s�siada

            // Aktualizacja klucza i poprzednika s�siada v, je�li warunki s� spe�nione
            if (!inMST[v] && weight < key[v])
            {
                predecessor[v] = u; // Ustawienie poprzednika
                key[v] = weight; // Zaktualizowanie klucza
            }
        }
    }

    // Wy�wietlenie wynik�w

    displayList(vertices, predecessor, key);


    // Zwolnienie zaalokowanej pami�ci dla tablicy list s�siedztwa
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
            cout << setw(3) << predecessor[i] << ":" << i << setw(5) << key[i] << endl; // Wy�wietlenie kraw�dzi i jej wagi
        }
    }
}

// Implementacja dla grafu reprezentowanego macierz�
void Prim::primMatrix(MatrixGraph& graph)
{
    int vertices = graph.vertices; // Liczba wierzcho�k�w w grafie
    int edges = graph.edges; // Liczba kraw�dzi w grafie

    // Dynamiczna alokacja pami�ci dla tablicy poprzednik�w, kluczy i tablicy MST
    int* predecessor = new int[vertices];
    int* key = new int[vertices];
    bool* inMST = new bool[vertices];

    // Inicjalizacja tablicy poprzednik�w, kluczy i tablicy MST
    for (int i = 0; i < vertices; ++i)
    {
        predecessor[i] = -1; // Inicjalizacja poprzednika jako -1, co oznacza brak poprzednika
        key[i] = INT_MAX; // Inicjalizacja klucza jako niesko�czono��
        inMST[i] = false; // Inicjalizacja MST jako false
    }

    key[0] = 0; // Ustawienie klucza dla wierzcho�ka startowego

    // G��wna p�tla algorytmu Prima
    for (int count = 0; count < vertices - 1; ++count)
    {
        int u = minKey(key, inMST, vertices); // Znalezienie wierzcho�ka o minimalnym kluczu, kt�ry nie jest w MST
        inMST[u] = true; // Dodanie wierzcho�ka u do MST

        // Przegl�d wszystkich kraw�dzi w grafie
        for (int j = 0; j < edges; ++j)
        {
            // Sprawdzenie, czy wierzcho�ek u jest ko�cem kraw�dzi
            if (graph.incidenceMatrix[u][j] == 1)
            {
                int v = -1; // Zmienna przechowuj�ca numer s�siada

                // Znalezienie wierzcho�ka v, kt�ry jest drugim ko�cem kraw�dzi
                for (int i = 0; i < vertices; ++i)
                {
                    if (graph.incidenceMatrix[i][j] == 1 && i != u)
                    {
                        v = i; // Ustawienie numeru s�siada
                        break;
                    }
                }

                // Aktualizacja klucza i poprzednika s�siada v, je�li warunki s� spe�nione
                if (v != -1 && !inMST[v] && graph.weightsMatrix[j] < key[v])
                {
                    key[v] = graph.weightsMatrix[j]; // Zaktualizowanie klucza
                    predecessor[v] = u; // Ustawienie poprzednika
                }
            }
        }
    }

    // Wy�wietlenie wynik�w
    displayMatrix(vertices, predecessor, key);

    // Zwolnienie zaalokowanej pami�ci
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
            cout << setw(3) << predecessor[i] << ":" << i << setw(5) << key[i] << endl; // Wy�wietlenie kraw�dzi i jej wagi
        }
    }
}

// Implementacja metody minKey do znajdowania wierzcho�ka o minimalnym kluczu
int Prim::minKey(const int key[], const bool inMST[], int vertices)
{
    int min = INT_MAX; // Inicjalizacja minimalnej warto�ci jako niesko�czono��
    int minIndex = -1; // Inicjalizacja indeksu minimalnej warto�ci jako -1

    // Przegl�d wszystkich wierzcho�k�w
    for (int v = 0; v < vertices; ++v)
    {
        // Je�li wierzcho�ek nie jest w MST i jego klucz jest mniejszy ni� aktualne minimum
        if (!inMST[v] && key[v] < min)
        {
            min = key[v]; // Aktualizacja minimalnej warto�ci
            minIndex = v; // Aktualizacja indeksu minimalnej warto�ci
        }
    }

    return minIndex; // Zwr�cenie indeksu wierzcho�ka o minimalnym kluczu
}
