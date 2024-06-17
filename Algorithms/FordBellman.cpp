#include "FordBellman.h"

#include <iostream>


// Implementacja dla grafu reprezentowanego list¹
void FordBellman::fordBellmanList(ListGraph& graph, int startVertex, int endVertex)
{
    int vertices = graph.vertices; // Pobranie liczby wierzcho³ków w grafie
    int edges = graph.edges; // Pobranie liczby krawêdzi w grafie
    int* edgeCounts = graph.edgeCounts; // Pobranie liczby krawêdzi wychodz¹cych z ka¿dego wierzcho³ka
    MyPair<int, int>** adjacencyList = graph.adjacencyList; // Pobranie listy s¹siedztwa

    // Dynamiczna alokacja pamiêci dla tablicy odleg³oœci i tablicy poprzedników
    int* distance = new int[vertices]; // Tablica odleg³oœci przechowuj¹ca najkrótsze odleg³oœci od wierzcho³ka startowego
    int* predecessors = new int[vertices]; // Tablica poprzedników przechowuj¹ca poprzedników na najkrótszych œcie¿kach

    // Inicjalizacja pocz¹tkowa tablicy odleg³oœci i poprzedników
    for (int i = 0; i < vertices; i++)
    {
        distance[i] = INT_MAX; // Inicjalizacja odleg³oœci jako nieskoñczonoœæ
        predecessors[i] = -1; // Inicjalizacja poprzedników jako -1, co oznacza brak poprzednika
    }
    distance[startVertex] = 0; // Odleg³oœæ wierzcho³ka startowego do samego siebie wynosi 0

    // Relaksacja krawêdzi
    bool isChanged; // Bool do sprawdzania, czy odleg³oœci zosta³y zmienione
    for (int i = 1; i < vertices; i++)
    {
        isChanged = false; // Resetowanie boola na pocz¹tku ka¿dej iteracji
        for (int u = 0; u < vertices; u++)
        {
            for (int j = 0; j < edgeCounts[u]; j++)
            {
                int v = adjacencyList[u][j].first; // Pobranie numeru s¹siada
                int weight = adjacencyList[u][j].second; // Pobranie wagi krawêdzi

                // Aktualizacja odleg³oœci s¹siada v, jeœli znaleziono krótsz¹ œcie¿kê
                if (distance[u] != INT_MAX && distance[u] + weight < distance[v])
                {
                    isChanged = true; // Ustawienie flagi, ¿e odleg³oœæ zosta³a zmieniona
                    distance[v] = distance[u] + weight; // Zaktualizowanie odleg³oœci s¹siada v
                    predecessors[v] = u; // Ustawienie poprzednika s¹siada v
                }
            }
        }
        if (!isChanged)
            break; // Jeœli odleg³oœci nie zosta³y zmienione, zakoñcz iteracjê
    }

    // Wyœwietlenie wyników

    cout << "Koszt najkrotszej sciezki z wierzcholka " << startVertex << " do wierzcholka " << endVertex << " wynosi: " << distance[endVertex] << std::endl;
    cout << "Znaleziona sciezka: ";
    int currentVertex = endVertex;
    while (currentVertex != -1)
    {
        cout << currentVertex; // Wyœwietlenie bie¿¹cego wierzcho³ka
        currentVertex = predecessors[currentVertex]; // Przejœcie do poprzednika
        if (currentVertex != -1)
            cout << " -> ";
    }
    cout << endl;

    // Zwolnienie zaalokowanej pamiêci dla tablicy odleg³oœci i tablicy poprzedników
    delete[] distance;
    delete[] predecessors;
}

// Implementacja dla grafu reprezentowanego macierz¹
void FordBellman::fordBellmanMatrix(MatrixGraph& graph, int startVertex, int endVertex)
{
    int vertices = graph.vertices; // Pobranie liczby wierzcho³ków w grafie
    int edges = graph.edges; // Pobranie liczby krawêdzi w grafie
    int** incidenceMatrix = graph.incidenceMatrix; // Pobranie macierzy incydencji
    int* weightsMatrix = graph.weightsMatrix; // Pobranie macierzy wag

    // Dynamiczna alokacja pamiêci dla tablicy odleg³oœci i tablicy poprzedników
    int* distance = new int[vertices]; // Tablica odleg³oœci przechowuj¹ca najkrótsze odleg³oœci od wierzcho³ka startowego
    int* predecessors = new int[vertices]; // Tablica poprzedników przechowuj¹ca poprzedników na najkrótszych œcie¿kach

    // Inicjalizacja pocz¹tkowa tablicy odleg³oœci i poprzedników
    for (int i = 0; i < vertices; i++)
    {
        distance[i] = INT_MAX; // Inicjalizacja odleg³oœci jako nieskoñczonoœæ
        predecessors[i] = -1; // Inicjalizacja poprzedników jako -1, co oznacza brak poprzednika
    }
    distance[startVertex] = 0; // Odleg³oœæ wierzcho³ka startowego do samego siebie wynosi 0

    // Relaksacja krawêdzi
    bool isChanged; // Bool do sprawdzania, czy odleg³oœci zosta³y zmienione
    for (int i = 1; i < vertices; i++)
    {
        isChanged = false; // Resetowanie boola na pocz¹tku ka¿dej iteracji
        for (int j = 0; j < edges; j++)
        {
            // Przejœcie po wszystkich krawêdziach
            int u = -1, v = -1, weight = -1;
            // Znalezienie wierzcho³ków u i v oraz ich wagi
            for (int k = 0; k < vertices; k++)
            {
                if (incidenceMatrix[k][j] == 1)
                    u = k; // Ustawienie wierzcho³ka pocz¹tkowego
                else if (incidenceMatrix[k][j] == -1)
                    v = k; // Ustawienie wierzcho³ka koñcowego
            }
            weight = weightsMatrix[j]; // Pobranie wagi krawêdzi

            // Aktualizacja odleg³oœci wierzcho³ka v, jeœli znaleziono krótsz¹ œcie¿kê
            if (distance[u] != INT_MAX && distance[u] + weight < distance[v])
            {
                isChanged = true; // Ustawienie boola, ¿e odleg³oœæ zosta³a zmieniona
                distance[v] = distance[u] + weight; // Zaktualizowanie odleg³oœci wierzcho³ka v
                predecessors[v] = u; // Ustawienie poprzednika wierzcho³ka v
            }
        }
        if (!isChanged)
            break; // Jeœli odleg³oœci nie zosta³y zmienione, zakoñcz iteracjê
    }

    // Wyœwietlenie wyników, jeœli flaga write jest ustawiona na true

    std::cout << "Koszt najkrotszej sciezki z wierzcholka " << startVertex << " do wierzcholka " << endVertex << " wynosi: " << distance[endVertex] << std::endl;
    std::cout << "Znaleziona sciezka: ";
    int currentVertex = endVertex;
    while (currentVertex != -1)
    {
        std::cout << currentVertex; // Wyœwietlenie bie¿¹cego wierzcho³ka
        currentVertex = predecessors[currentVertex]; // Przejœcie do poprzednika
        if (currentVertex != -1)
            std::cout << " -> "; // Separator strza³kowy
    }
    std::cout << std::endl;


    // Zwolnienie zaalokowanej pamiêci dla tablicy odleg³oœci i tablicy poprzedników
    delete[] distance;
    delete[] predecessors;
}
