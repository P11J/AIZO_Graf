#include "Simulation.h"
#include "Algorithms/Prim.h"
#include "Algorithms/Kruskal.h"
#include "Algorithms/Dijkstra.h"
#include "Algorithms/FordBellman.h"

#include <iostream>
#include <chrono>

#define ITERATIONS 50 // Definicja liczby powtórzeń dla symulacji
#define MS 1000 // Jednostka przeliczająca czas na milisekundy

void Simulation::simulationMode(int algNum)
{


    int vertexCounts[] = { 10, 20, 50, 100, 200, 500, 1000}; // Liczby wierzchołków
    float densities[] = { 0.25, 0.50, 0.99 }; // Gęstości grafu

    if (algNum == 1) // Algorytm Prima
    {

        cout << modeName(algNum) << endl; // Wyświetlenie nazwy algorytmu
        for (int i = 0; i < 3; i++) // Iteracja po gęstościach
        {
            cout << "----- gestosc " << densities[i] << endl; // Wyświetlenie gęstości
            for (int j = 0; j < 7; j++) // Iteracja po liczbach wierzchołków
            {
                cout << "--- rozmiar " << vertexCounts[j] << endl; // Wyświetlenie liczby wierzchołków

                int vertices = vertexCounts[j]; // Liczba wierzchołków
                float density = densities[i]; // Gęstość grafu
                std::chrono::duration<double> time1{}; // Zmienna do przechowywania czasu wykonania dla listy

                for (int n = 0; n < ITERATIONS; n++) // Powtórzenia dla uzyskania średniego czasu
                {
                    ListGraph list; // Utworzenie grafu listowego
                    Graph graph; // Utworzenie obiektu grafu
                    graph.generateGraph(vertices, density); // Generowanie grafu
                    list.loadGraphToGraph(graph); // Wypełnienie grafu listowego

                    auto begin = chrono::high_resolution_clock::now(); // Rozpoczęcie pomiaru czasu
                    Prim::primList(list); // Wywołanie algorytmu Prima dla listy
                    auto end = chrono::high_resolution_clock::now(); // Zakończenie pomiaru czasu
                    auto elapsed = chrono::duration_cast<chrono::microseconds>(end - begin); // Obliczenie czasu wykonania
                    time1 += elapsed; // Sumowanie czasu wykonania
                }
                cout << "Czas dla listy wyniosl: " << time1.count() * MS / ITERATIONS << " ms" << endl; // Wyświetlenie średniego czasu wykonania dla listy

                std::chrono::duration<double> time2{}; // Zmienna do przechowywania czasu wykonania dla macierzy
                for (int n = 0; n < ITERATIONS; n++) // Powtórzenia dla uzyskania średniego czasu
                {
                    MatrixGraph matrix; // Utworzenie grafu macierzowego
                    Graph graph; // Utworzenie obiektu grafu
                    graph.generateGraph(vertices, density); // Generowanie grafu
                    matrix.loadGraphToGraph(graph, 1); // Wypełnienie grafu macierzowego

                    auto begin = chrono::high_resolution_clock::now(); // Rozpoczęcie pomiaru czasu
                    Prim::primMatrix(matrix); // Wywołanie algorytmu Prima dla macierzy
                    auto end = chrono::high_resolution_clock::now(); // Zakończenie pomiaru czasu
                    auto elapsed = chrono::duration_cast<chrono::microseconds>(end - begin); // Obliczenie czasu wykonania
                    time2 += elapsed; // Sumowanie czasu wykonania
                }
                cout << "Czas dla macierzy wyniosl: " << time2.count() * MS / ITERATIONS << " ms" << endl; // Wyświetlenie średniego czasu wykonania dla macierzy
            }
        }
    }

    if (algNum == 2) // Algorytm Kruskala
    {
        Kruskal kruskal; // Utworzenie obiektu algorytmu Kruskala
        cout << modeName(algNum) << endl; // Wyświetlenie nazwy algorytmu
        for (int i = 0; i < 3; i++) // Iteracja po gęstościach
        {
            cout << "----- gestosc " << densities[i] << endl; // Wyświetlenie gęstości
            for (int j = 0; j < 7; j++) // Iteracja po liczbach wierzchołków
            {
                cout << "--- rozmiar " << vertexCounts[j] << endl; // Wyświetlenie liczby wierzchołków

                int vertices = vertexCounts[j]; // Liczba wierzchołków
                float density = densities[i]; // Gęstość grafu

                std::chrono::duration<double> time1{}; // Zmienna do przechowywania czasu wykonania dla listy
                for (int n = 0; n < ITERATIONS; n++) // Powtórzenia dla uzyskania średniego czasu
                {
                    ListGraph list; // Utworzenie grafu listowego
                    Graph graph; // Utworzenie obiektu grafu
                    graph.generateGraph(vertices, density); // Generowanie grafu
                    list.loadGraphToGraph(graph); // Wypełnienie grafu listowego

                    auto begin = chrono::high_resolution_clock::now(); // Rozpoczęcie pomiaru czasu
                    kruskal.kruskalList(list); // Wywołanie algorytmu Kruskala dla listy
                    auto end = chrono::high_resolution_clock::now(); // Zakończenie pomiaru czasu
                    auto elapsed = chrono::duration_cast<chrono::microseconds>(end - begin); // Obliczenie czasu wykonania
                    time1 += elapsed; // Sumowanie czasu wykonania
                }
                cout << "Czas dla listy wyniosl: " << time1.count() * MS / ITERATIONS << " ms" << endl; // Wyświetlenie średniego czasu wykonania dla listy

                std::chrono::duration<double> time2{}; // Zmienna do przechowywania czasu wykonania dla macierzy
                for (int n = 0; n < ITERATIONS; n++) // Powtórzenia dla uzyskania średniego czasu
                {
                    MatrixGraph matrix; // Utworzenie grafu macierzowego
                    Graph graph; // Utworzenie obiektu grafu
                    graph.generateGraph(vertices, density); // Generowanie grafu
                    matrix.loadGraphToGraph(graph, 1); // Wypełnienie grafu macierzowego

                    auto begin = chrono::high_resolution_clock::now(); // Rozpoczęcie pomiaru czasu
                    kruskal.kruskalMatrix(matrix); // Wywołanie algorytmu Kruskala dla macierzy
                    auto end = chrono::high_resolution_clock::now(); // Zakończenie pomiaru czasu
                    auto elapsed = chrono::duration_cast<chrono::microseconds>(end - begin); // Obliczenie czasu wykonania
                    time2 += elapsed; // Sumowanie czasu wykonania
                }
                cout << "Czas dla macierzy wyniosl: " << time2.count() * MS / ITERATIONS << " ms" << endl; // Wyświetlenie średniego czasu wykonania dla macierzy
            }
        }
    }

    if (algNum == 3) // Algorytm Dijkstry
    {
        Dijkstra dijkstra; // Utworzenie obiektu algorytmu Dijkstry
        cout << modeName(algNum) << endl; // Wyświetlenie nazwy algorytmu
        for (int i = 0; i < 3; i++) // Iteracja po gęstościach
        {
            cout << "----- gestosc " << densities[i] << endl; // Wyświetlenie gęstości
            for (int j = 0; j < 7; j++) // Iteracja po liczbach wierzchołków
            {
                cout << "--- rozmiar " << vertexCounts[j] << endl; // Wyświetlenie liczby wierzchołków

                int vertices = vertexCounts[j]; // Liczba wierzchołków
                float density = densities[i]; // Gęstość grafu

                std::chrono::duration<double> time1{}; // Zmienna do przechowywania czasu wykonania dla listy
                for (int n = 0; n < ITERATIONS; n++) // Powtórzenia dla uzyskania średniego czasu
                {
                    ListGraph list; // Utworzenie grafu listowego
                    Graph graph; // Utworzenie obiektu grafu
                    graph.generateGraph(vertices, density); // Generowanie grafu
                    list.loadGraphToGraph(graph); // Wypełnienie grafu listowego

                    auto begin = chrono::high_resolution_clock::now(); // Rozpoczęcie pomiaru czasu
                    dijkstra.dijkstraList(list, 0, vertices); // Wywołanie algorytmu Dijkstry dla listy
                    auto end = chrono::high_resolution_clock::now(); // Zakończenie pomiaru czasu
                    auto elapsed = chrono::duration_cast<chrono::microseconds>(end - begin); // Obliczenie czasu wykonania
                    time1 += elapsed; // Sumowanie czasu wykonania
                }
                cout << "Czas dla listy wyniosl: " << time1.count() * MS / ITERATIONS << " ms" << endl; // Wyświetlenie średniego czasu wykonania dla listy

                std::chrono::duration<double> time2{}; // Zmienna do przechowywania czasu wykonania dla macierzy
                for (int n = 0; n < ITERATIONS; n++) // Powtórzenia dla uzyskania średniego czasu
                {
                    MatrixGraph matrix; // Utworzenie grafu macierzowego
                    Graph graph; // Utworzenie obiektu grafu
                    graph.generateGraph(vertices, density); // Generowanie grafu
                    matrix.loadGraphToGraph(graph, -1); // Wypełnienie grafu macierzowego

                    auto begin = chrono::high_resolution_clock::now(); // Rozpoczęcie pomiaru czasu
                    dijkstra.dijkstraMatrix(matrix, 0, vertices); // Wywołanie algorytmu Dijkstry dla macierzy
                    auto end = chrono::high_resolution_clock::now(); // Zakończenie pomiaru czasu
                    auto elapsed = chrono::duration_cast<chrono::microseconds>(end - begin); // Obliczenie czasu wykonania
                    time2 += elapsed; // Sumowanie czasu wykonania
                }
                cout << "Czas dla macierzy wyniosl: " << time2.count() * MS / ITERATIONS << " ms" << endl; // Wyświetlenie średniego czasu wykonania dla macierzy
            }
        }
    }

    if (algNum == 4) // Algorytm Forda-Bellmana
    {
        cout << modeName(algNum) << endl; // Wyświetlenie nazwy algorytmu
        for (int i = 0; i < 3; i++) // Iteracja po gęstościach
        {
            cout << "----- gestosc " << densities[i] << endl; // Wyświetlenie gęstości
            for (int j = 0; j < 7; j++) // Iteracja po liczbach wierzchołków
            {
                cout << "--- rozmiar " << vertexCounts[j] << endl; // Wyświetlenie liczby wierzchołków

                int vertices = vertexCounts[j]; // Liczba wierzchołków
                float density = densities[i]; // Gęstość grafu

                std::chrono::duration<double> time1{}; // Zmienna do przechowywania czasu wykonania dla listy
                for (int n = 0; n < ITERATIONS; n++) // Powtórzenia dla uzyskania średniego czasu
                {
                    ListGraph list; // Utworzenie grafu listowego
                    Graph graph; // Utworzenie obiektu grafu
                    graph.generateGraph(vertices, density); // Generowanie grafu
                    list.loadGraphToGraph(graph); // Wypełnienie grafu listowego

                    auto begin = chrono::high_resolution_clock::now(); // Rozpoczęcie pomiaru czasu
                    FordBellman::fordBellmanList(list, 0, vertices); // Wywołanie algorytmu Forda-Bellmana dla listy
                    auto end = chrono::high_resolution_clock::now(); // Zakończenie pomiaru czasu
                    auto elapsed = chrono::duration_cast<chrono::microseconds>(end - begin); // Obliczenie czasu wykonania
                    time1 += elapsed; // Sumowanie czasu wykonania
                }
                cout << "Czas dla listy wyniosl: " << time1.count() * MS / ITERATIONS << " ms" << endl; // Wyświetlenie średniego czasu wykonania dla listy

                std::chrono::duration<double> time2{}; // Zmienna do przechowywania czasu wykonania dla macierzy
                for (int n = 0; n < ITERATIONS; n++) // Powtórzenia dla uzyskania średniego czasu
                {
                    MatrixGraph matrix; // Utworzenie grafu macierzowego
                    Graph graph; // Utworzenie obiektu grafu
                    graph.generateGraph(vertices, density); // Generowanie grafu
                    matrix.loadGraphToGraph(graph, -1); // Wypełnienie grafu macierzowego

                    auto begin = chrono::high_resolution_clock::now(); // Rozpoczęcie pomiaru czasu
                    FordBellman::fordBellmanMatrix(matrix, 0, vertices); // Wywołanie algorytmu Forda-Bellmana dla macierzy
                    auto end = chrono::high_resolution_clock::now(); // Zakończenie pomiaru czasu
                    auto elapsed = chrono::duration_cast<chrono::microseconds>(end - begin); // Obliczenie czasu wykonania
                    time2 += elapsed; // Sumowanie czasu wykonania
                }
                cout << "Czas dla macierzy wyniosl: " << time2.count() * MS / ITERATIONS << " ms" << endl; // Wyświetlenie średniego czasu wykonania dla macierzy
            }
        }
    }

    cout << endl << endl << endl; // Oddzielenie wyników pustymi liniami
}

// Definicja metody modeName klasy Simulation
const char* Simulation::modeName(int algnum)
{
    switch (algnum)
    {
        case 1:
        {
            return "Algorytm Prima"; // Nazwa dla algorytmu Prima
            break;
        }
        case 2:
        {
            return "Algorytm Kruskala"; // Nazwa dla algorytmu Kruskala
            break;
        }
        case 3:
        {
            return "Algorytm Dijkstry"; // Nazwa dla algorytmu Dijkstry
            break;
        }
        case 4:
        {
            return "Algorytm Forda-Bellmana"; // Nazwa dla algorytmu Forda-Bellmana
            break;
        }
            {
                default:
                    return "error"; // Błąd, jeśli algorytm nie jest rozpoznawany
            }
    }
}