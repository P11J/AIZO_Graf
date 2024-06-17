#include "Dijkstra.h"

#include <iostream>
#include <algorithm>

// Implementacja dla grafu reprezentowanego list¹

void Dijkstra::dijkstraList(ListGraph& graph, int startVertex, int endVertex)
{
    int vertices = graph.vertices; // Liczba wierzcho³ków w grafie
    int* distance = new int[vertices]; // Tablica odleg³oœci od wierzcho³ka startowego
    bool* sptSet = new bool[vertices]; // Tablica œledz¹ca wierzcho³ki w zbiorze SPT (Shortest Path Tree)
    auto* priorityQueue = new MyPair<int, int>[vertices]; // Kolejka priorytetowa przechowuj¹ca pary (wierzcho³ek, odleg³oœæ)

    // Inicjalizacja tablic
    for (int i = 0; i < vertices; i++)
    {
        distance[i] = INT_MAX; // Ustawienie wszystkich odleg³oœci na nieskoñczonoœæ
        sptSet[i] = false; // Ustawienie, ¿e ¿aden wierzcho³ek nie jest jeszcze w SPT
        priorityQueue[i] = MyPair<int, int>(i, distance[i]); // Dodanie pary (wierzcho³ek, odleg³oœæ) do kolejki
    }

    distance[startVertex] = 0; // Ustawienie odleg³oœci pocz¹tkowej na 0
    priorityQueue[startVertex].second = 0; // Aktualizacja odleg³oœci w kolejce priorytetowej

    int size = vertices; // Rozmiar kolejki priorytetowej

    // G³ówna pêtla algorytmu Dijkstry
    for (int count = 0; count < vertices - 1; count++)
    {
        heapify(priorityQueue, distance, size, 0); // Przywracanie w³asnoœci kopca
        int u = priorityQueue[0].first; // Pobranie wierzcho³ka z minimaln¹ odleg³oœci¹
        sptSet[u] = true; // Dodanie wierzcho³ka do zbioru SPT
        priorityQueue[0] = priorityQueue[size - 1]; // Usuniêcie wierzcho³ka z kolejki priorytetowej
        size--; // Zmniejszenie rozmiaru kolejki

        // Przegl¹danie s¹siadów wierzcho³ka u
        for (int j = 0; j < graph.edgeCounts[u]; j++)
        {
            int v = graph.adjacencyList[u][j].first; // S¹siaduj¹cy wierzcho³ek
            int weight = graph.adjacencyList[u][j].second; // Waga krawêdzi
            // Aktualizacja odleg³oœci, jeœli znaleziono krótsz¹ œcie¿kê
            if (!sptSet[v] && distance[u] != INT_MAX && distance[u] + weight < distance[v])
            {
                distance[v] = distance[u] + weight; // Aktualizacja odleg³oœci
                // Aktualizacja odleg³oœci w kolejce priorytetowej
                for (int k = 0; k < size; k++)
                {
                    if (priorityQueue[k].first == v)
                    {
                        priorityQueue[k].second = distance[v];
                        break;
                    }
                }
                heapify(priorityQueue, distance, size, 0); // Przywracanie w³asnoœci kopca
            }
        }
    }

    //Wypisanie wyniku

    cout << "Format:\nWierzcholek: odleglosc od wierzcholka zrodlowego" << endl;
    for (int i = 0; i < vertices; i++)
        cout << i << ": " << distance[i] << endl; // Wypisanie odleg³oœci dla ka¿dego wierzcho³ka

    // Zwolnienie zaalokowanej pamiêci
    delete[] distance;
    delete[] sptSet;
    delete[] priorityQueue;
}


void Dijkstra::dijkstraMatrix(MatrixGraph& graph, int startVertex, int endVertex) {
    int vertices = graph.vertices; // Liczba wierzcho³ków w grafie
    int* priorityQueue = new int[vertices]; // Kolejka priorytetowa jako tablica wierzcho³ków
    int* distance = new int[vertices]; // Tablica odleg³oœci od wierzcho³ka startowego
    int* predecessors = new int[vertices]; // Tablica poprzedników do œledzenia œcie¿ki
    int size = vertices; // Rozmiar kolejki priorytetowej

    // Inicjalizacja tablic
    for (int i = 0; i < vertices; ++i)
    {
        distance[i] = INT_MAX; // Ustawienie wszystkich odleg³oœci na nieskoñczonoœæ
        priorityQueue[i] = i; // Dodanie wierzcho³ka do kolejki
        predecessors[i] = -1; // Inicjalizacja poprzedników
    }

    distance[startVertex] = 0; // Ustawienie odleg³oœci pocz¹tkowej na 0
    heapify(priorityQueue, distance, size, 0); // Przywracanie w³asnoœci kopca

    // G³ówna pêtla algorytmu Dijkstry
    while (size > 0)
    {
        int minDistanceVertex = extractMin(priorityQueue, distance, size); // Pobranie wierzcho³ka z minimaln¹ odleg³oœci¹

        // Przegl¹danie wszystkich krawêdzi incydentnych z wierzcho³kiem minDistanceVertex
        for (int i = 0; i < graph.edges; ++i)
        {
            if (graph.incidenceMatrix[minDistanceVertex][i] == 1)
            {
                for (int v = 0; v < vertices; ++v)
                {
                    if (v != minDistanceVertex && graph.incidenceMatrix[v][i] == -1)
                    {
                        int weight = graph.weightsMatrix[i]; // Waga krawêdzi

                        // Aktualizacja odleg³oœci, jeœli znaleziono krótsz¹ œcie¿kê
                        if (distance[minDistanceVertex] != INT_MAX && distance[minDistanceVertex] + weight < distance[v]) {
                            distance[v] = distance[minDistanceVertex] + weight; // Aktualizacja odleg³oœci
                            predecessors[v] = minDistanceVertex; // Ustawienie poprzednika
                            decreaseKey(priorityQueue, distance, size, v, distance[v]); // Aktualizacja kolejki priorytetowej
                        }
                    }
                }
            }
        }
    }

    // Wypisanie wyników

    cout << "Koszt najkrotszej sciezki z wierzcholka " << startVertex << " do wierzcholka " << endVertex << " wynosi: " << distance[endVertex] << endl;
    cout << "Znaleziona sciezka: ";
    int currentVertex = endVertex;
    while (currentVertex != -1)
    {
        cout << currentVertex; // Wypisanie bie¿¹cego wierzcho³ka na œcie¿ce
        currentVertex = predecessors[currentVertex]; // Przejœcie do poprzednika
        if (currentVertex != -1)
            cout << " -> ";
    }
    cout << endl;


    // Zwolnienie zaalokowanej pamiêci
    delete[] priorityQueue;
    delete[] distance;
    delete[] predecessors;
}


// Metoda zamieniaj¹ca dwie pary (odleg³oœæ, wierzcho³ek)
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

// Metoda przywracaj¹ca w³asnoœæ kopca dla par (odleg³oœæ, wierzcho³ek)

void Dijkstra::heapify(MyPair<int, int>* priorityQueue, int* distance, int n, int i)
{
    int smallest = i; // Ustawienie najmniejszego jako bie¿¹cy indeks
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

    // Jeœli najmniejszy element nie jest bie¿¹cym elementem, zamieñ je i zrekuruj
    if (smallest != i)
    {
        swap(priorityQueue[i], priorityQueue[smallest]); // Zamiana elementu bie¿¹cego z najmniejszym
        heapify(priorityQueue, distance, n, smallest); // Rekurencyjne przywracanie w³asnoœci kopca
    }
}


// Metoda usuwaj¹ca i zwracaj¹ca element minimalny z kopca dla par (odleg³oœæ, wierzcho³ek)
MyPair<int, int> Dijkstra::extractMin(MyPair<int, int>* priorityQueue, int* distance, int& size)
{
    if (size <= 0)
    {
        return makeMyPair(INT_MAX, -1); // Zwróæ parê z maksymaln¹ wartoœci¹ i -1, jeœli kopiec jest pusty
    }

    if (size == 1)
    {
        size--; // Zmniejsz rozmiar kopca
        return priorityQueue[0]; // Zwróæ jedyny element w kopcu
    }

    MyPair<int, int> root = priorityQueue[0]; // Pobierz element korzenia
    priorityQueue[0] = priorityQueue[size - 1]; // Przenieœ ostatni element do korzenia
    size--; // Zmniejsz rozmiar kopca
    heapify(priorityQueue, distance, size, 0); // Przywróæ w³asnoœæ kopca

    return root; // Zwróæ element korzenia
}

// Metoda zmniejszaj¹ca wartoœæ klucza w kopcu dla par (odleg³oœæ, wierzcho³ek)
void Dijkstra::decreaseKey(MyPair<int, int>* priorityQueue, int* distance, int size, int vertex, int newDistance)
{
    int i;
    for (i = 0; i < size; ++i)
    {
        if (priorityQueue[i].second == vertex)
        {
            distance[vertex] = newDistance; // Zaktualizowanie wartoœci odleg³oœci dla wierzcho³ka
            priorityQueue[i].first = newDistance; // Zaktualizowanie wartoœci klucza w kopcu
            break;
        }
    }

    // Przywracanie w³asnoœci kopca po zmniejszeniu wartoœci klucza
    while (i != 0 && priorityQueue[i].first < priorityQueue[(i - 1) / 2].first)
    {
        swap(priorityQueue[i], priorityQueue[(i - 1) / 2]); // Zamiana elementu bie¿¹cego z rodzicem
        i = (i - 1) / 2; // Przesuniêcie indeksu na rodzica
    }
}

// Metoda przywracaj¹ca w³asnoœæ kopca
void Dijkstra::heapify(int* priorityQueue, int* distance, int n, int i)
{
    int smallest = i; // Ustawienie najmniejszego jako bie¿¹cy indeks
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

    // Jeœli najmniejszy element nie jest bie¿¹cym elementem, zamieñ je i zrekuruj
    if (smallest != i)
    {
        swap(priorityQueue[i], priorityQueue[smallest]); // Zamiana elementu bie¿¹cego z najmniejszym
        heapify(priorityQueue, distance, n, smallest); // Rekurencyjne przywracanie w³asnoœci kopca
    }
}

// Metoda usuwaj¹ca i zwracaj¹ca element minimalny z kopca
int Dijkstra::extractMin(int* priorityQueue, int* distance, int& size)
{
    if (size <= 0)
    {
        return -1; // Zwróæ -1, jeœli kopiec jest pusty
    }

    if (size == 1)
    {
        size--; // Zmniejsz rozmiar kopca
        return priorityQueue[0]; // Zwróæ jedyny element w kopcu
    }

    int root = priorityQueue[0]; // Pobierz element korzenia
    priorityQueue[0] = priorityQueue[size - 1]; // Przenieœ ostatni element do korzenia
    size--; // Zmniejsz rozmiar kopca
    heapify(priorityQueue, distance, size, 0); // Przywróæ w³asnoœæ kopca

    return root; // Zwróæ element korzenia
}

// Metoda zmniejszaj¹ca wartoœæ klucza w kopcu
void Dijkstra::decreaseKey(int* priorityQueue, int* distance, int size, int vertex, int newDistance)
{
    int i;
    for (i = 0; i < size; ++i)
    {
        if (priorityQueue[i] == vertex)
        {
            distance[vertex] = newDistance; // Zaktualizowanie wartoœci odleg³oœci dla wierzcho³ka
            break;
        }
    }

    // Przywracanie w³asnoœci kopca po zmniejszeniu wartoœci klucza
    while (i != 0 && distance[priorityQueue[i]] < distance[priorityQueue[(i - 1) / 2]])
    {
        swap(priorityQueue[i], priorityQueue[(i - 1) / 2]); // Zamiana elementu bie¿¹cego z rodzicem
        i = (i - 1) / 2; // Przesuniêcie indeksu na rodzica
    }
}
