#include "FordBellman.h" // Do��czenie pliku nag��wkowego dla algorytmu Forda-Bellmana

#include <iostream> // Do��czenie biblioteki wej�cia-wyj�cia
#include <iomanip> // Do��czenie biblioteki dla manipulacji strumieniami wej�cia-wyj�cia

// Implementacja metody Ford_Bellman_list dla grafu reprezentowanego list�
void FordBellman::Ford_Bellman_list(ListGraph& graph, int start, int end, bool write)
{
    int vertices = graph.vertices; // Pobranie liczby wierzcho�k�w w grafie
    int edges = graph.edges; // Pobranie liczby kraw�dzi w grafie
    int* edgeCounts = graph.edgeCounts; // Pobranie liczby kraw�dzi wychodz�cych z ka�dego wierzcho�ka
    My_pair<int, int>** adjacencyList = graph.adjacencyList; // Pobranie listy s�siedztwa

    // Dynamiczna alokacja pami�ci dla tablicy odleg�o�ci i tablicy poprzednik�w
    int* distance = new int[vertices]; // Tablica odleg�o�ci przechowuj�ca najkr�tsze odleg�o�ci od wierzcho�ka startowego
    int* predecessors = new int[vertices]; // Tablica poprzednik�w przechowuj�ca poprzednik�w na najkr�tszych �cie�kach

    // Inicjalizacja pocz�tkowa tablicy odleg�o�ci i poprzednik�w
    for (int i = 0; i < vertices; i++)
    {
        distance[i] = INT_MAX; // Inicjalizacja odleg�o�ci jako niesko�czono��
        predecessors[i] = -1; // Inicjalizacja poprzednik�w jako -1, co oznacza brak poprzednika
    }
    distance[start] = 0; // Odleg�o�� wierzcho�ka startowego do samego siebie wynosi 0

    // Relaksacja kraw�dzi
    bool isChanged; // Flaga do sprawdzania, czy odleg�o�ci zosta�y zmienione
    for (int i = 1; i < vertices; i++)
    {
        isChanged = false; // Resetowanie flagi na pocz�tku ka�dej iteracji
        for (int u = 0; u < vertices; u++)
        {
            for (int j = 0; j < edgeCounts[u]; j++)
            {
                int v = adjacencyList[u][j].first; // Pobranie numeru s�siada
                int weight = adjacencyList[u][j].second; // Pobranie wagi kraw�dzi

                // Aktualizacja odleg�o�ci s�siada v, je�li znaleziono kr�tsz� �cie�k�
                if (distance[u] != INT_MAX && distance[u] + weight < distance[v])
                {
                    isChanged = true; // Ustawienie flagi, �e odleg�o�� zosta�a zmieniona
                    distance[v] = distance[u] + weight; // Zaktualizowanie odleg�o�ci s�siada v
                    predecessors[v] = u; // Ustawienie poprzednika s�siada v
                }
            }
        }
        if (!isChanged)
            break; // Je�li odleg�o�ci nie zosta�y zmienione, zako�cz iteracj�
    }

    // Wy�wietlenie wynik�w, je�li flaga write jest ustawiona na true
    if (write == true)
    {
        std::cout << "Koszt najkrotszej sciezki z wierzcholka " << start << " do wierzcholka " << end << " wynosi: " << distance[end] << std::endl;
        std::cout << "Znaleziona sciezka: ";
        int currentVertex = end;
        while (currentVertex != -1)
        {
            std::cout << currentVertex; // Wy�wietlenie bie��cego wierzcho�ka
            currentVertex = predecessors[currentVertex]; // Przej�cie do poprzednika
            if (currentVertex != -1)
                std::cout << " -> "; // Separator strza�kowy
        }
        std::cout << std::endl;
    }

    // Zwolnienie zaalokowanej pami�ci dla tablicy odleg�o�ci i tablicy poprzednik�w
    delete[] distance;
    delete[] predecessors;
}

// Implementacja metody Ford_Bellman_matrix dla grafu reprezentowanego macierz�
void FordBellman::Ford_Bellman_matrix(MatrixGraph& graph, int start, int end, bool write)
{
    int vertices = graph.vertices; // Pobranie liczby wierzcho�k�w w grafie
    int edges = graph.edges; // Pobranie liczby kraw�dzi w grafie
    int** incidenceMatrix = graph.incidenceMatrix; // Pobranie macierzy incydencji
    int* weightsMatrix = graph.weightsMatrix; // Pobranie macierzy wag

    // Dynamiczna alokacja pami�ci dla tablicy odleg�o�ci i tablicy poprzednik�w
    int* distance = new int[vertices]; // Tablica odleg�o�ci przechowuj�ca najkr�tsze odleg�o�ci od wierzcho�ka startowego
    int* predecessors = new int[vertices]; // Tablica poprzednik�w przechowuj�ca poprzednik�w na najkr�tszych �cie�kach

    // Inicjalizacja pocz�tkowa tablicy odleg�o�ci i poprzednik�w
    for (int i = 0; i < vertices; i++)
    {
        distance[i] = INT_MAX; // Inicjalizacja odleg�o�ci jako niesko�czono��
        predecessors[i] = -1; // Inicjalizacja poprzednik�w jako -1, co oznacza brak poprzednika
    }
    distance[start] = 0; // Odleg�o�� wierzcho�ka startowego do samego siebie wynosi 0

    // Relaksacja kraw�dzi
    bool isChanged; // Flaga do sprawdzania, czy odleg�o�ci zosta�y zmienione
    for (int i = 1; i < vertices; i++)
    {
        isChanged = false; // Resetowanie flagi na pocz�tku ka�dej iteracji
        for (int j = 0; j < edges; j++)
        {
            // Przej�cie po wszystkich kraw�dziach
            int u = -1, v = -1, weight = -1;
            // Znalezienie wierzcho�k�w u i v oraz ich wagi
            for (int k = 0; k < vertices; k++)
            {
                if (incidenceMatrix[k][j] == 1)
                    u = k; // Ustawienie wierzcho�ka pocz�tkowego
                else if (incidenceMatrix[k][j] == -1)
                    v = k; // Ustawienie wierzcho�ka ko�cowego
            }
            weight = weightsMatrix[j]; // Pobranie wagi kraw�dzi

            // Aktualizacja odleg�o�ci wierzcho�ka v, je�li znaleziono kr�tsz� �cie�k�
            if (distance[u] != INT_MAX && distance[u] + weight < distance[v])
            {
                isChanged = true; // Ustawienie flagi, �e odleg�o�� zosta�a zmieniona
                distance[v] = distance[u] + weight; // Zaktualizowanie odleg�o�ci wierzcho�ka v
                predecessors[v] = u; // Ustawienie poprzednika wierzcho�ka v
            }
        }
        if (!isChanged)
            break; // Je�li odleg�o�ci nie zosta�y zmienione, zako�cz iteracj�
    }

    // Wy�wietlenie wynik�w, je�li flaga write jest ustawiona na true
    if (write == true)
    {
        std::cout << "Koszt najkrotszej sciezki z wierzcholka " << start << " do wierzcholka " << end << " wynosi: " << distance[end] << std::endl;
        std::cout << "Znaleziona sciezka: ";
        int currentVertex = end;
        while (currentVertex != -1)
        {
            std::cout << currentVertex; // Wy�wietlenie bie��cego wierzcho�ka
            currentVertex = predecessors[currentVertex]; // Przej�cie do poprzednika
            if (currentVertex != -1)
                std::cout << " -> "; // Separator strza�kowy
        }
        std::cout << std::endl;
    }

    // Zwolnienie zaalokowanej pami�ci dla tablicy odleg�o�ci i tablicy poprzednik�w
    delete[] distance;
    delete[] predecessors;
}
