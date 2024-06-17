#include "Dijkstra.h"

#include <iostream>
#include <algorithm>

// Implementacja dla grafu reprezentowanego list�

void Dijkstra::dijkstraList(ListGraph& graph, int startVertex, int endVertex)
{
    int vertices = graph.vertices; // Liczba wierzcho�k�w w grafie
    int* distance = new int[vertices]; // Tablica odleg�o�ci od wierzcho�ka startowego
    bool* sptSet = new bool[vertices]; // Tablica �ledz�ca wierzcho�ki w zbiorze SPT (Shortest Path Tree)
    auto* priorityQueue = new MyPair<int, int>[vertices]; // Kolejka priorytetowa przechowuj�ca pary (wierzcho�ek, odleg�o��)

    // Inicjalizacja tablic
    for (int i = 0; i < vertices; i++)
    {
        distance[i] = INT_MAX; // Ustawienie wszystkich odleg�o�ci na niesko�czono��
        sptSet[i] = false; // Ustawienie, �e �aden wierzcho�ek nie jest jeszcze w SPT
        priorityQueue[i] = MyPair<int, int>(i, distance[i]); // Dodanie pary (wierzcho�ek, odleg�o��) do kolejki
    }

    distance[startVertex] = 0; // Ustawienie odleg�o�ci pocz�tkowej na 0
    priorityQueue[startVertex].second = 0; // Aktualizacja odleg�o�ci w kolejce priorytetowej

    int size = vertices; // Rozmiar kolejki priorytetowej

    // G��wna p�tla algorytmu Dijkstry
    for (int count = 0; count < vertices - 1; count++)
    {
        heapify(priorityQueue, distance, size, 0); // Przywracanie w�asno�ci kopca
        int u = priorityQueue[0].first; // Pobranie wierzcho�ka z minimaln� odleg�o�ci�
        sptSet[u] = true; // Dodanie wierzcho�ka do zbioru SPT
        priorityQueue[0] = priorityQueue[size - 1]; // Usuni�cie wierzcho�ka z kolejki priorytetowej
        size--; // Zmniejszenie rozmiaru kolejki

        // Przegl�danie s�siad�w wierzcho�ka u
        for (int j = 0; j < graph.edgeCounts[u]; j++)
        {
            int v = graph.adjacencyList[u][j].first; // S�siaduj�cy wierzcho�ek
            int weight = graph.adjacencyList[u][j].second; // Waga kraw�dzi
            // Aktualizacja odleg�o�ci, je�li znaleziono kr�tsz� �cie�k�
            if (!sptSet[v] && distance[u] != INT_MAX && distance[u] + weight < distance[v])
            {
                distance[v] = distance[u] + weight; // Aktualizacja odleg�o�ci
                // Aktualizacja odleg�o�ci w kolejce priorytetowej
                for (int k = 0; k < size; k++)
                {
                    if (priorityQueue[k].first == v)
                    {
                        priorityQueue[k].second = distance[v];
                        break;
                    }
                }
                heapify(priorityQueue, distance, size, 0); // Przywracanie w�asno�ci kopca
            }
        }
    }

    //Wypisanie wyniku

    cout << "Format:\nWierzcholek: odleglosc od wierzcholka zrodlowego" << endl;
    for (int i = 0; i < vertices; i++)
        cout << i << ": " << distance[i] << endl; // Wypisanie odleg�o�ci dla ka�dego wierzcho�ka

    // Zwolnienie zaalokowanej pami�ci
    delete[] distance;
    delete[] sptSet;
    delete[] priorityQueue;
}


void Dijkstra::dijkstraMatrix(MatrixGraph& graph, int startVertex, int endVertex) {
    int vertices = graph.vertices; // Liczba wierzcho�k�w w grafie
    int* priorityQueue = new int[vertices]; // Kolejka priorytetowa jako tablica wierzcho�k�w
    int* distance = new int[vertices]; // Tablica odleg�o�ci od wierzcho�ka startowego
    int* predecessors = new int[vertices]; // Tablica poprzednik�w do �ledzenia �cie�ki
    int size = vertices; // Rozmiar kolejki priorytetowej

    // Inicjalizacja tablic
    for (int i = 0; i < vertices; ++i)
    {
        distance[i] = INT_MAX; // Ustawienie wszystkich odleg�o�ci na niesko�czono��
        priorityQueue[i] = i; // Dodanie wierzcho�ka do kolejki
        predecessors[i] = -1; // Inicjalizacja poprzednik�w
    }

    distance[startVertex] = 0; // Ustawienie odleg�o�ci pocz�tkowej na 0
    heapify(priorityQueue, distance, size, 0); // Przywracanie w�asno�ci kopca

    // G��wna p�tla algorytmu Dijkstry
    while (size > 0)
    {
        int minDistanceVertex = extractMin(priorityQueue, distance, size); // Pobranie wierzcho�ka z minimaln� odleg�o�ci�

        // Przegl�danie wszystkich kraw�dzi incydentnych z wierzcho�kiem minDistanceVertex
        for (int i = 0; i < graph.edges; ++i)
        {
            if (graph.incidenceMatrix[minDistanceVertex][i] == 1)
            {
                for (int v = 0; v < vertices; ++v)
                {
                    if (v != minDistanceVertex && graph.incidenceMatrix[v][i] == -1)
                    {
                        int weight = graph.weightsMatrix[i]; // Waga kraw�dzi

                        // Aktualizacja odleg�o�ci, je�li znaleziono kr�tsz� �cie�k�
                        if (distance[minDistanceVertex] != INT_MAX && distance[minDistanceVertex] + weight < distance[v]) {
                            distance[v] = distance[minDistanceVertex] + weight; // Aktualizacja odleg�o�ci
                            predecessors[v] = minDistanceVertex; // Ustawienie poprzednika
                            decreaseKey(priorityQueue, distance, size, v, distance[v]); // Aktualizacja kolejki priorytetowej
                        }
                    }
                }
            }
        }
    }

    // Wypisanie wynik�w

    cout << "Koszt najkrotszej sciezki z wierzcholka " << startVertex << " do wierzcholka " << endVertex << " wynosi: " << distance[endVertex] << endl;
    cout << "Znaleziona sciezka: ";
    int currentVertex = endVertex;
    while (currentVertex != -1)
    {
        cout << currentVertex; // Wypisanie bie��cego wierzcho�ka na �cie�ce
        currentVertex = predecessors[currentVertex]; // Przej�cie do poprzednika
        if (currentVertex != -1)
            cout << " -> ";
    }
    cout << endl;


    // Zwolnienie zaalokowanej pami�ci
    delete[] priorityQueue;
    delete[] distance;
    delete[] predecessors;
}


// Metoda zamieniaj�ca dwie pary (odleg�o��, wierzcho�ek)
void Dijkstra::swap(MyPair<int, int>& a, MyPair<int, int>& b)
{
    MyPair<int, int> temp = a;
    a = b;
    b = temp;
}

void Dijkstra::swap(int& a, int& b)
{
    int temp = a;
    a = b;
    b = temp;
}

// Metoda przywracaj�ca w�asno�� kopca dla par (odleg�o��, wierzcho�ek)

void Dijkstra::heapify(MyPair<int, int>* priorityQueue, int* distance, int n, int i)
{
    int smallest = i; // Ustawienie najmniejszego jako bie��cy indeks
    int left = 2 * i + 1; // Indeks lewego dziecka
    int right = 2 * i + 2; // Indeks prawego dziecka

    // Sprawdzenie, czy lewe dziecko jest mniejsze od najmniejszego elementu
    if (left < n && distance[priorityQueue[left].first] < distance[priorityQueue[smallest].first])
    {
        smallest = left; // Ustawienie najmniejszego jako lewego dziecka
    }

    // Sprawdzenie, czy prawe dziecko jest mniejsze od najmniejszego elementu
    if (right < n && distance[priorityQueue[right].first] < distance[priorityQueue[smallest].first])
    {
        smallest = right; // Ustawienie najmniejszego jako prawego dziecka
    }

    // Je�li najmniejszy element nie jest bie��cym elementem, zamie� je i zrekuruj
    if (smallest != i)
    {
        swap(priorityQueue[i], priorityQueue[smallest]); // Zamiana elementu bie��cego z najmniejszym
        heapify(priorityQueue, distance, n, smallest); // Rekurencyjne przywracanie w�asno�ci kopca
    }
}


// Metoda usuwaj�ca i zwracaj�ca element minimalny z kopca dla par (odleg�o��, wierzcho�ek)
MyPair<int, int> Dijkstra::extractMin(MyPair<int, int>* priorityQueue, int* distance, int& size)
{
    if (size <= 0)
    {
        return makeMyPair(INT_MAX, -1); // Zwr�� par� z maksymaln� warto�ci� i -1, je�li kopiec jest pusty
    }

    if (size == 1)
    {
        size--; // Zmniejsz rozmiar kopca
        return priorityQueue[0]; // Zwr�� jedyny element w kopcu
    }

    MyPair<int, int> root = priorityQueue[0]; // Pobierz element korzenia
    priorityQueue[0] = priorityQueue[size - 1]; // Przenie� ostatni element do korzenia
    size--; // Zmniejsz rozmiar kopca
    heapify(priorityQueue, distance, size, 0); // Przywr�� w�asno�� kopca

    return root; // Zwr�� element korzenia
}

// Metoda zmniejszaj�ca warto�� klucza w kopcu dla par (odleg�o��, wierzcho�ek)
void Dijkstra::decreaseKey(MyPair<int, int>* priorityQueue, int* distance, int size, int vertex, int newDistance)
{
    int i;
    for (i = 0; i < size; ++i)
    {
        if (priorityQueue[i].second == vertex)
        {
            distance[vertex] = newDistance; // Zaktualizowanie warto�ci odleg�o�ci dla wierzcho�ka
            priorityQueue[i].first = newDistance; // Zaktualizowanie warto�ci klucza w kopcu
            break;
        }
    }

    // Przywracanie w�asno�ci kopca po zmniejszeniu warto�ci klucza
    while (i != 0 && priorityQueue[i].first < priorityQueue[(i - 1) / 2].first)
    {
        swap(priorityQueue[i], priorityQueue[(i - 1) / 2]); // Zamiana elementu bie��cego z rodzicem
        i = (i - 1) / 2; // Przesuni�cie indeksu na rodzica
    }
}

// Metoda przywracaj�ca w�asno�� kopca
void Dijkstra::heapify(int* priorityQueue, int* distance, int n, int i)
{
    int smallest = i; // Ustawienie najmniejszego jako bie��cy indeks
    int left = 2 * i + 1; // Indeks lewego dziecka
    int right = 2 * i + 2; // Indeks prawego dziecka

    // Sprawdzenie, czy lewe dziecko jest mniejsze od najmniejszego elementu
    if (left < n && distance[priorityQueue[left]] < distance[priorityQueue[smallest]])
    {
        smallest = left; // Ustawienie najmniejszego jako lewego dziecka
    }

    // Sprawdzenie, czy prawe dziecko jest mniejsze od najmniejszego elementu
    if (right < n && distance[priorityQueue[right]] < distance[priorityQueue[smallest]])
    {
        smallest = right; // Ustawienie najmniejszego jako prawego dziecka
    }

    // Je�li najmniejszy element nie jest bie��cym elementem, zamie� je i zrekuruj
    if (smallest != i)
    {
        swap(priorityQueue[i], priorityQueue[smallest]); // Zamiana elementu bie��cego z najmniejszym
        heapify(priorityQueue, distance, n, smallest); // Rekurencyjne przywracanie w�asno�ci kopca
    }
}

// Metoda usuwaj�ca i zwracaj�ca element minimalny z kopca
int Dijkstra::extractMin(int* priorityQueue, int* distance, int& size)
{
    if (size <= 0)
    {
        return -1; // Zwr�� -1, je�li kopiec jest pusty
    }

    if (size == 1)
    {
        size--; // Zmniejsz rozmiar kopca
        return priorityQueue[0]; // Zwr�� jedyny element w kopcu
    }

    int root = priorityQueue[0]; // Pobierz element korzenia
    priorityQueue[0] = priorityQueue[size - 1]; // Przenie� ostatni element do korzenia
    size--; // Zmniejsz rozmiar kopca
    heapify(priorityQueue, distance, size, 0); // Przywr�� w�asno�� kopca

    return root; // Zwr�� element korzenia
}

// Metoda zmniejszaj�ca warto�� klucza w kopcu
void Dijkstra::decreaseKey(int* priorityQueue, int* distance, int size, int vertex, int newDistance)
{
    int i;
    for (i = 0; i < size; ++i)
    {
        if (priorityQueue[i] == vertex)
        {
            distance[vertex] = newDistance; // Zaktualizowanie warto�ci odleg�o�ci dla wierzcho�ka
            break;
        }
    }

    // Przywracanie w�asno�ci kopca po zmniejszeniu warto�ci klucza
    while (i != 0 && distance[priorityQueue[i]] < distance[priorityQueue[(i - 1) / 2]])
    {
        swap(priorityQueue[i], priorityQueue[(i - 1) / 2]); // Zamiana elementu bie��cego z rodzicem
        i = (i - 1) / 2; // Przesuni�cie indeksu na rodzica
    }
}
