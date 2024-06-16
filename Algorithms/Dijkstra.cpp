#include "Dijkstra.h" // Do��czenie pliku nag��wkowego dla algorytmu Dijkstry

#include <iostream> // Do��czenie biblioteki wej�cia-wyj�cia
#include <iomanip> // Do��czenie biblioteki dla manipulacji strumieniami wej�cia-wyj�cia

// Implementacja metody Dijkstra_list dla grafu reprezentowanego list�
void Alg_Dijkstra::Dijkstra_list(ListGraph& graph, int start, int end, bool write)
{
    int vertices = graph.vertices; // Pobranie liczby wierzcho�k�w w grafie

    // Dynamiczna alokacja pami�ci dla kopca priorytetowego, tablicy odleg�o�ci i tablicy poprzednik�w
    My_pair<int, int>* pq = new My_pair<int, int>[vertices]; // Kopiec priorytetowy przechowuj�cy pary (odleg�o��, wierzcho�ek)
    int* dist = new int[vertices]; // Tablica odleg�o�ci przechowuj�ca najkr�tsze odleg�o�ci od wierzcho�ka startowego
    int* predecessors = new int[vertices]; // Tablica poprzednik�w przechowuj�ca poprzednik�w na najkr�tszych �cie�kach
    int size = vertices; // Rozmiar kopca priorytetowego

    // Inicjalizacja tablicy odleg�o�ci, kopca priorytetowego i poprzednik�w
    for (int i = 0; i < vertices; ++i)
    {
        dist[i] = INT_MAX; // Inicjalizacja odleg�o�ci jako niesko�czono��
        pq[i] = my_make_pair(INT_MAX, i); // Inicjalizacja kopca priorytetowego z par� (niesko�czono��, wierzcho�ek)
        predecessors[i] = -1; // Inicjalizacja poprzednik�w jako -1, co oznacza brak poprzednika
    }

    dist[start] = 0; // Odleg�o�� wierzcho�ka startowego do samego siebie wynosi 0
    pq[start] = my_make_pair(0, start); // Ustawienie odleg�o�ci wierzcho�ka startowego w kopcu priorytetowym
    heapify(pq, dist, size, 0); // Przywr�cenie w�asno�ci kopca priorytetowego

    // P�tla g��wna algorytmu Dijkstry
    while (size > 0)
    {
        My_pair<int, int> minPair = extractMin(pq, dist, size); // Wyci�gni�cie wierzcho�ka o minimalnej odleg�o�ci z kopca
        int u = minPair.second; // Pobranie numeru wierzcho�ka z pary

        // Przegl�d s�siad�w wierzcho�ka u
        for (int i = 0; i < graph.edgeCounts[u]; ++i)
        {
            My_pair<int, int> neighbor = graph.adjacencyList[u][i]; // Pobranie s�siada wierzcho�ka u
            int v = neighbor.first; // Numer s�siada
            int weight = neighbor.second; // Waga kraw�dzi do s�siada

            // Aktualizacja odleg�o�ci s�siada v, je�li znaleziono kr�tsz� �cie�k�
            if (dist[u] != INT_MAX && dist[u] + weight < dist[v])
            {
                dist[v] = dist[u] + weight; // Zaktualizowanie odleg�o�ci s�siada v
                predecessors[v] = u; // Ustawienie poprzednika s�siada v
                decreaseKey(pq, dist, size, v, dist[v]); // Zmniejszenie warto�ci klucza w kopcu priorytetowym
            }
        }
    }

    // Wy�wietlenie wynik�w, je�li flaga write jest ustawiona na true
    if (write == true)
    {
        cout << "Koszt najkrotszej sciezki z wierzcholka " << start << " do wierzcholka " << end << " wynosi: " << dist[end] << endl;
        cout << "Znaleziona sciezka: ";
        int currentVertex = end;
        while (currentVertex != -1)
        {
            cout << currentVertex; // Wy�wietlenie bie��cego wierzcho�ka
            currentVertex = predecessors[currentVertex]; // Przej�cie do poprzednika
            if (currentVertex != -1)
                cout << " -> "; // Separator strza�kowy
        }
        cout << endl;
    }

    // Zwolnienie zaalokowanej pami�ci dla kopca priorytetowego, tablicy odleg�o�ci i tablicy poprzednik�w
    delete[] pq;
    delete[] dist;
    delete[] predecessors;
}

// Metoda zamieniaj�ca dwie pary (odleg�o��, wierzcho�ek)
void Alg_Dijkstra::swap(My_pair<int, int>& a, My_pair<int, int>& b)
{
    My_pair<int, int> temp = a; // Przypisanie warto�ci a do zmiennej tymczasowej
    a = b; // Przypisanie warto�ci b do a
    b = temp; // Przypisanie warto�ci zmiennej tymczasowej do b
}

// Metoda przywracaj�ca w�asno�� kopca dla par (odleg�o��, wierzcho�ek)
void Alg_Dijkstra::heapify(My_pair<int, int>* pq, int* dist, int n, int i)
{
    int smallest = i; // Ustawienie najmniejszego jako bie��cy indeks
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

    // Je�li najmniejszy element nie jest bie��cym elementem, zamie� je i zrekuruj
    if (smallest != i)
    {
        swap(pq[i], pq[smallest]); // Zamiana elementu bie��cego z najmniejszym
        heapify(pq, dist, n, smallest); // Rekurencyjne przywracanie w�asno�ci kopca
    }
}

// Metoda usuwaj�ca i zwracaj�ca element minimalny z kopca dla par (odleg�o��, wierzcho�ek)
My_pair<int, int> Alg_Dijkstra::extractMin(My_pair<int, int>* pq, int* dist, int& size)
{
    if (size <= 0)
    {
        return my_make_pair(INT_MAX, -1); // Zwr�� par� z maksymaln� warto�ci� i -1, je�li kopiec jest pusty
    }

    if (size == 1)
    {
        size--; // Zmniejsz rozmiar kopca
        return pq[0]; // Zwr�� jedyny element w kopcu
    }

    My_pair<int, int> root = pq[0]; // Pobierz element korzenia
    pq[0] = pq[size - 1]; // Przenie� ostatni element do korzenia
    size--; // Zmniejsz rozmiar kopca
    heapify(pq, dist, size, 0); // Przywr�� w�asno�� kopca

    return root; // Zwr�� element korzenia
}

// Metoda zmniejszaj�ca warto�� klucza w kopcu dla par (odleg�o��, wierzcho�ek)
void Alg_Dijkstra::decreaseKey(My_pair<int, int>* pq, int* dist, int size, int vertex, int newDist)
{
    int i;
    for (i = 0; i < size; ++i)
    {
        if (pq[i].second == vertex)
        {
            dist[vertex] = newDist; // Zaktualizowanie warto�ci odleg�o�ci dla wierzcho�ka
            pq[i].first = newDist; // Zaktualizowanie warto�ci klucza w kopcu
            break;
        }
    }

    // Przywracanie w�asno�ci kopca po zmniejszeniu warto�ci klucza
    while (i != 0 && pq[i].first < pq[(i - 1) / 2].first)
    {
        swap(pq[i], pq[(i - 1) / 2]); // Zamiana elementu bie��cego z rodzicem
        i = (i - 1) / 2; // Przesuni�cie indeksu na rodzica
    }
}

// Metoda przywracaj�ca w�asno�� kopca
void Alg_Dijkstra::heapify(int* pq, int* dist, int n, int i)
{
    int smallest = i; // Ustawienie najmniejszego jako bie��cy indeks
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

    // Je�li najmniejszy element nie jest bie��cym elementem, zamie� je i zrekuruj
    if (smallest != i)
    {
        swap(pq[i], pq[smallest]); // Zamiana elementu bie��cego z najmniejszym
        heapify(pq, dist, n, smallest); // Rekurencyjne przywracanie w�asno�ci kopca
    }
}

// Metoda usuwaj�ca i zwracaj�ca element minimalny z kopca
int Alg_Dijkstra::extractMin(int* pq, int* dist, int& size)
{
    if (size <= 0)
    {
        return -1; // Zwr�� -1, je�li kopiec jest pusty
    }

    if (size == 1)
    {
        size--; // Zmniejsz rozmiar kopca
        return pq[0]; // Zwr�� jedyny element w kopcu
    }

    int root = pq[0]; // Pobierz element korzenia
    pq[0] = pq[size - 1]; // Przenie� ostatni element do korzenia
    size--; // Zmniejsz rozmiar kopca
    heapify(pq, dist, size, 0); // Przywr�� w�asno�� kopca

    return root; // Zwr�� element korzenia
}

// Metoda zmniejszaj�ca warto�� klucza w kopcu
void Alg_Dijkstra::decreaseKey(int* pq, int* dist, int size, int vertex, int newDist)
{
    int i;
    for (i = 0; i < size; ++i)
    {
        if (pq[i] == vertex)
        {
            dist[vertex] = newDist; // Zaktualizowanie warto�ci odleg�o�ci dla wierzcho�ka
            break;
        }
    }

    // Przywracanie w�asno�ci kopca po zmniejszeniu warto�ci klucza
    while (i != 0 && dist[pq[i]] < dist[pq[(i - 1) / 2]])
    {
        swap(pq[i], pq[(i - 1) / 2]); // Zamiana elementu bie��cego z rodzicem
        i = (i - 1) / 2; // Przesuni�cie indeksu na rodzica
    }
}
