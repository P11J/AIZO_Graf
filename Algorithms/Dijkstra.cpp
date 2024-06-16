#include "Dijkstra.h" // Do³¹czenie pliku nag³ówkowego dla algorytmu Dijkstry

#include <iostream> // Do³¹czenie biblioteki wejœcia-wyjœcia
#include <iomanip> // Do³¹czenie biblioteki dla manipulacji strumieniami wejœcia-wyjœcia

// Implementacja metody Dijkstra_list dla grafu reprezentowanego list¹
void Alg_Dijkstra::Dijkstra_list(ListGraph& graph, int start, int end, bool write)
{
    int vertices = graph.vertices; // Pobranie liczby wierzcho³ków w grafie

    // Dynamiczna alokacja pamiêci dla kopca priorytetowego, tablicy odleg³oœci i tablicy poprzedników
    My_pair<int, int>* pq = new My_pair<int, int>[vertices]; // Kopiec priorytetowy przechowuj¹cy pary (odleg³oœæ, wierzcho³ek)
    int* dist = new int[vertices]; // Tablica odleg³oœci przechowuj¹ca najkrótsze odleg³oœci od wierzcho³ka startowego
    int* predecessors = new int[vertices]; // Tablica poprzedników przechowuj¹ca poprzedników na najkrótszych œcie¿kach
    int size = vertices; // Rozmiar kopca priorytetowego

    // Inicjalizacja tablicy odleg³oœci, kopca priorytetowego i poprzedników
    for (int i = 0; i < vertices; ++i)
    {
        dist[i] = INT_MAX; // Inicjalizacja odleg³oœci jako nieskoñczonoœæ
        pq[i] = my_make_pair(INT_MAX, i); // Inicjalizacja kopca priorytetowego z par¹ (nieskoñczonoœæ, wierzcho³ek)
        predecessors[i] = -1; // Inicjalizacja poprzedników jako -1, co oznacza brak poprzednika
    }

    dist[start] = 0; // Odleg³oœæ wierzcho³ka startowego do samego siebie wynosi 0
    pq[start] = my_make_pair(0, start); // Ustawienie odleg³oœci wierzcho³ka startowego w kopcu priorytetowym
    heapify(pq, dist, size, 0); // Przywrócenie w³asnoœci kopca priorytetowego

    // Pêtla g³ówna algorytmu Dijkstry
    while (size > 0)
    {
        My_pair<int, int> minPair = extractMin(pq, dist, size); // Wyci¹gniêcie wierzcho³ka o minimalnej odleg³oœci z kopca
        int u = minPair.second; // Pobranie numeru wierzcho³ka z pary

        // Przegl¹d s¹siadów wierzcho³ka u
        for (int i = 0; i < graph.edgeCounts[u]; ++i)
        {
            My_pair<int, int> neighbor = graph.adjacencyList[u][i]; // Pobranie s¹siada wierzcho³ka u
            int v = neighbor.first; // Numer s¹siada
            int weight = neighbor.second; // Waga krawêdzi do s¹siada

            // Aktualizacja odleg³oœci s¹siada v, jeœli znaleziono krótsz¹ œcie¿kê
            if (dist[u] != INT_MAX && dist[u] + weight < dist[v])
            {
                dist[v] = dist[u] + weight; // Zaktualizowanie odleg³oœci s¹siada v
                predecessors[v] = u; // Ustawienie poprzednika s¹siada v
                decreaseKey(pq, dist, size, v, dist[v]); // Zmniejszenie wartoœci klucza w kopcu priorytetowym
            }
        }
    }

    // Wyœwietlenie wyników, jeœli flaga write jest ustawiona na true
    if (write == true)
    {
        cout << "Koszt najkrotszej sciezki z wierzcholka " << start << " do wierzcholka " << end << " wynosi: " << dist[end] << endl;
        cout << "Znaleziona sciezka: ";
        int currentVertex = end;
        while (currentVertex != -1)
        {
            cout << currentVertex; // Wyœwietlenie bie¿¹cego wierzcho³ka
            currentVertex = predecessors[currentVertex]; // Przejœcie do poprzednika
            if (currentVertex != -1)
                cout << " -> "; // Separator strza³kowy
        }
        cout << endl;
    }

    // Zwolnienie zaalokowanej pamiêci dla kopca priorytetowego, tablicy odleg³oœci i tablicy poprzedników
    delete[] pq;
    delete[] dist;
    delete[] predecessors;
}

// Metoda zamieniaj¹ca dwie pary (odleg³oœæ, wierzcho³ek)
void Alg_Dijkstra::swap(My_pair<int, int>& a, My_pair<int, int>& b)
{
    My_pair<int, int> temp = a; // Przypisanie wartoœci a do zmiennej tymczasowej
    a = b; // Przypisanie wartoœci b do a
    b = temp; // Przypisanie wartoœci zmiennej tymczasowej do b
}

// Metoda przywracaj¹ca w³asnoœæ kopca dla par (odleg³oœæ, wierzcho³ek)
void Alg_Dijkstra::heapify(My_pair<int, int>* pq, int* dist, int n, int i)
{
    int smallest = i; // Ustawienie najmniejszego jako bie¿¹cy indeks
    int left = 2 * i + 1; // Indeks lewego dziecka
    int right = 2 * i + 2; // Indeks prawego dziecka

    // Sprawdzenie, czy lewe dziecko jest mniejsze od najmniejszego elementu
    if (left < n && dist[pq[left].first] < dist[pq[smallest].first])
    {
        smallest = left; // Ustawienie najmniejszego jako lewego dziecka
    }

    // Sprawdzenie, czy prawe dziecko jest mniejsze od najmniejszego elementu
    if (right < n && dist[pq[right].first] < dist[pq[smallest].first])
    {
        smallest = right; // Ustawienie najmniejszego jako prawego dziecka
    }

    // Jeœli najmniejszy element nie jest bie¿¹cym elementem, zamieñ je i zrekuruj
    if (smallest != i)
    {
        swap(pq[i], pq[smallest]); // Zamiana elementu bie¿¹cego z najmniejszym
        heapify(pq, dist, n, smallest); // Rekurencyjne przywracanie w³asnoœci kopca
    }
}

// Metoda usuwaj¹ca i zwracaj¹ca element minimalny z kopca dla par (odleg³oœæ, wierzcho³ek)
My_pair<int, int> Alg_Dijkstra::extractMin(My_pair<int, int>* pq, int* dist, int& size)
{
    if (size <= 0)
    {
        return my_make_pair(INT_MAX, -1); // Zwróæ parê z maksymaln¹ wartoœci¹ i -1, jeœli kopiec jest pusty
    }

    if (size == 1)
    {
        size--; // Zmniejsz rozmiar kopca
        return pq[0]; // Zwróæ jedyny element w kopcu
    }

    My_pair<int, int> root = pq[0]; // Pobierz element korzenia
    pq[0] = pq[size - 1]; // Przenieœ ostatni element do korzenia
    size--; // Zmniejsz rozmiar kopca
    heapify(pq, dist, size, 0); // Przywróæ w³asnoœæ kopca

    return root; // Zwróæ element korzenia
}

// Metoda zmniejszaj¹ca wartoœæ klucza w kopcu dla par (odleg³oœæ, wierzcho³ek)
void Alg_Dijkstra::decreaseKey(My_pair<int, int>* pq, int* dist, int size, int vertex, int newDist)
{
    int i;
    for (i = 0; i < size; ++i)
    {
        if (pq[i].second == vertex)
        {
            dist[vertex] = newDist; // Zaktualizowanie wartoœci odleg³oœci dla wierzcho³ka
            pq[i].first = newDist; // Zaktualizowanie wartoœci klucza w kopcu
            break;
        }
    }

    // Przywracanie w³asnoœci kopca po zmniejszeniu wartoœci klucza
    while (i != 0 && pq[i].first < pq[(i - 1) / 2].first)
    {
        swap(pq[i], pq[(i - 1) / 2]); // Zamiana elementu bie¿¹cego z rodzicem
        i = (i - 1) / 2; // Przesuniêcie indeksu na rodzica
    }
}

// Metoda przywracaj¹ca w³asnoœæ kopca
void Alg_Dijkstra::heapify(int* pq, int* dist, int n, int i)
{
    int smallest = i; // Ustawienie najmniejszego jako bie¿¹cy indeks
    int left = 2 * i + 1; // Indeks lewego dziecka
    int right = 2 * i + 2; // Indeks prawego dziecka

    // Sprawdzenie, czy lewe dziecko jest mniejsze od najmniejszego elementu
    if (left < n && dist[pq[left]] < dist[pq[smallest]])
    {
        smallest = left; // Ustawienie najmniejszego jako lewego dziecka
    }

    // Sprawdzenie, czy prawe dziecko jest mniejsze od najmniejszego elementu
    if (right < n && dist[pq[right]] < dist[pq[smallest]])
    {
        smallest = right; // Ustawienie najmniejszego jako prawego dziecka
    }

    // Jeœli najmniejszy element nie jest bie¿¹cym elementem, zamieñ je i zrekuruj
    if (smallest != i)
    {
        swap(pq[i], pq[smallest]); // Zamiana elementu bie¿¹cego z najmniejszym
        heapify(pq, dist, n, smallest); // Rekurencyjne przywracanie w³asnoœci kopca
    }
}

// Metoda usuwaj¹ca i zwracaj¹ca element minimalny z kopca
int Alg_Dijkstra::extractMin(int* pq, int* dist, int& size)
{
    if (size <= 0)
    {
        return -1; // Zwróæ -1, jeœli kopiec jest pusty
    }

    if (size == 1)
    {
        size--; // Zmniejsz rozmiar kopca
        return pq[0]; // Zwróæ jedyny element w kopcu
    }

    int root = pq[0]; // Pobierz element korzenia
    pq[0] = pq[size - 1]; // Przenieœ ostatni element do korzenia
    size--; // Zmniejsz rozmiar kopca
    heapify(pq, dist, size, 0); // Przywróæ w³asnoœæ kopca

    return root; // Zwróæ element korzenia
}

// Metoda zmniejszaj¹ca wartoœæ klucza w kopcu
void Alg_Dijkstra::decreaseKey(int* pq, int* dist, int size, int vertex, int newDist)
{
    int i;
    for (i = 0; i < size; ++i)
    {
        if (pq[i] == vertex)
        {
            dist[vertex] = newDist; // Zaktualizowanie wartoœci odleg³oœci dla wierzcho³ka
            break;
        }
    }

    // Przywracanie w³asnoœci kopca po zmniejszeniu wartoœci klucza
    while (i != 0 && dist[pq[i]] < dist[pq[(i - 1) / 2]])
    {
        swap(pq[i], pq[(i - 1) / 2]); // Zamiana elementu bie¿¹cego z rodzicem
        i = (i - 1) / 2; // Przesuniêcie indeksu na rodzica
    }
}
