#include "Simulation.h"
#include "Algorithms/Prim.h"
#include "Algorithms/Kruskal.h"
#include "Algorithms/Dijkstra.h"
#include "Algorithms/FordBellman.h"

#include <iostream>
#include <chrono>

#define REPETITION 50 // Definicja liczby powtórzeń dla symulacji
#define UNIT 1000 // Jednostka przeliczająca czas na milisekundy

// Definicja metody simulation_mode klasy Simulation
void Simulation::simulation_mode(int algnum)
{
    //ZMIENIC DENSITIES DO SPRAWKA


    int vertexCounts[] = { 10, 20, 50, 100, 200, 500, 1000}; // Liczby wierzchołków
    float densities[] = { 0.25, 0.50, 0.99 }; // Gęstości grafu

    if (algnum == 1) // Algorytm Prima
    {

        cout << mode_name(algnum) << endl; // Wyświetlenie nazwy algorytmu
        for (int i = 0; i < 3; i++) // Iteracja po gęstościach
        {
            cout << "----- gestosc " << densities[i] << endl; // Wyświetlenie gęstości
            for (int j = 0; j < 7; j++) // Iteracja po liczbach wierzchołków
            {
                cout << "--- rozmiar " << vertexCounts[j] << endl; // Wyświetlenie liczby wierzchołków

                int ver = vertexCounts[j]; // Liczba wierzchołków
                float den = densities[i]; // Gęstość grafu
                std::chrono::duration<double> czas1{}; // Zmienna do przechowywania czasu wykonania dla listy

                for (int n = 0; n < REPETITION; n++) // Powtórzenia dla uzyskania średniego czasu
                {
                    ListGraph list; // Utworzenie grafu listowego
                    Graph graph; // Utworzenie obiektu grafu
                    graph.generateGraph(ver, den); // Generowanie grafu
                    list.populateFromGraph(graph); // Wypełnienie grafu listowego

                    auto begin = chrono::high_resolution_clock::now(); // Rozpoczęcie pomiaru czasu
                    Alg_Prim::Prim_list(list, false); // Wywołanie algorytmu Prima dla listy
                    auto end = chrono::high_resolution_clock::now(); // Zakończenie pomiaru czasu
                    auto elapsed = chrono::duration_cast<chrono::microseconds>(end - begin); // Obliczenie czasu wykonania
                    czas1 += elapsed; // Sumowanie czasu wykonania
                }
                cout << "Czas dla listy wyniosl: " << czas1.count() * UNIT / REPETITION << " ms" << endl; // Wyświetlenie średniego czasu wykonania dla listy

                std::chrono::duration<double> czas2{}; // Zmienna do przechowywania czasu wykonania dla macierzy
                for (int n = 0; n < REPETITION; n++) // Powtórzenia dla uzyskania średniego czasu
                {
                    MatrixGraph matrix; // Utworzenie grafu macierzowego
                    Graph graph; // Utworzenie obiektu grafu
                    graph.generateGraph(ver, den); // Generowanie grafu
                    matrix.populateFromGraph(graph, 1); // Wypełnienie grafu macierzowego

                    auto begin = chrono::high_resolution_clock::now(); // Rozpoczęcie pomiaru czasu
                    Alg_Prim::Prim_matrix(matrix, false); // Wywołanie algorytmu Prima dla macierzy
                    auto end = chrono::high_resolution_clock::now(); // Zakończenie pomiaru czasu
                    auto elapsed = chrono::duration_cast<chrono::microseconds>(end - begin); // Obliczenie czasu wykonania
                    czas2 += elapsed; // Sumowanie czasu wykonania
                }
                cout << "Czas dla macierzy wyniosl: " << czas2.count() * UNIT / REPETITION << " ms" << endl; // Wyświetlenie średniego czasu wykonania dla macierzy
            }
        }
    }

    if (algnum == 2) // Algorytm Kruskala
    {
        Alg_Kruskal kruskal; // Utworzenie obiektu algorytmu Kruskala
        cout << mode_name(algnum) << endl; // Wyświetlenie nazwy algorytmu
        for (int i = 0; i < 3; i++) // Iteracja po gęstościach
        {
            cout << "----- gestosc " << densities[i] << endl; // Wyświetlenie gęstości
            for (int j = 0; j < 7; j++) // Iteracja po liczbach wierzchołków
            {
                cout << "--- rozmiar " << vertexCounts[j] << endl; // Wyświetlenie liczby wierzchołków

                int ver = vertexCounts[j]; // Liczba wierzchołków
                float den = densities[i]; // Gęstość grafu

                std::chrono::duration<double> czas1{}; // Zmienna do przechowywania czasu wykonania dla listy
                for (int n = 0; n < REPETITION; n++) // Powtórzenia dla uzyskania średniego czasu
                {
                    ListGraph list; // Utworzenie grafu listowego
                    Graph graph; // Utworzenie obiektu grafu
                    graph.generateGraph(ver, den); // Generowanie grafu
                    list.populateFromGraph(graph); // Wypełnienie grafu listowego

                    auto begin = chrono::high_resolution_clock::now(); // Rozpoczęcie pomiaru czasu
                    kruskal.Kruskal_list(list, false); // Wywołanie algorytmu Kruskala dla listy
                    auto end = chrono::high_resolution_clock::now(); // Zakończenie pomiaru czasu
                    auto elapsed = chrono::duration_cast<chrono::microseconds>(end - begin); // Obliczenie czasu wykonania
                    czas1 += elapsed; // Sumowanie czasu wykonania
                }
                cout << "Czas dla listy wyniosl: " << czas1.count() * UNIT / REPETITION << " ms" << endl; // Wyświetlenie średniego czasu wykonania dla listy

                std::chrono::duration<double> czas2{}; // Zmienna do przechowywania czasu wykonania dla macierzy
                for (int n = 0; n < REPETITION; n++) // Powtórzenia dla uzyskania średniego czasu
                {
                    MatrixGraph matrix; // Utworzenie grafu macierzowego
                    Graph graph; // Utworzenie obiektu grafu
                    graph.generateGraph(ver, den); // Generowanie grafu
                    matrix.populateFromGraph(graph, 1); // Wypełnienie grafu macierzowego

                    auto begin = chrono::high_resolution_clock::now(); // Rozpoczęcie pomiaru czasu
                    kruskal.Kruskal_matrix(matrix, false); // Wywołanie algorytmu Kruskala dla macierzy
                    auto end = chrono::high_resolution_clock::now(); // Zakończenie pomiaru czasu
                    auto elapsed = chrono::duration_cast<chrono::microseconds>(end - begin); // Obliczenie czasu wykonania
                    czas2 += elapsed; // Sumowanie czasu wykonania
                }
                cout << "Czas dla macierzy wyniosl: " << czas2.count() * UNIT / REPETITION << " ms" << endl; // Wyświetlenie średniego czasu wykonania dla macierzy
            }
        }
    }

    if (algnum == 3) // Algorytm Dijkstry
    {
        Dijkstra dijkstra; // Utworzenie obiektu algorytmu Dijkstry
        cout << mode_name(algnum) << endl; // Wyświetlenie nazwy algorytmu
        for (int i = 0; i < 3; i++) // Iteracja po gęstościach
        {
            cout << "----- gestosc " << densities[i] << endl; // Wyświetlenie gęstości
            for (int j = 0; j < 7; j++) // Iteracja po liczbach wierzchołków
            {
                cout << "--- rozmiar " << vertexCounts[j] << endl; // Wyświetlenie liczby wierzchołków

                int ver = vertexCounts[j]; // Liczba wierzchołków
                float den = densities[i]; // Gęstość grafu

                std::chrono::duration<double> czas1{}; // Zmienna do przechowywania czasu wykonania dla listy
                for (int n = 0; n < REPETITION; n++) // Powtórzenia dla uzyskania średniego czasu
                {
                    ListGraph list; // Utworzenie grafu listowego
                    Graph graph; // Utworzenie obiektu grafu
                    graph.generateGraph(ver, den); // Generowanie grafu
                    list.populateFromGraph(graph); // Wypełnienie grafu listowego

                    auto begin = chrono::high_resolution_clock::now(); // Rozpoczęcie pomiaru czasu
                    dijkstra.dijkstraList(list, 0, ver); // Wywołanie algorytmu Dijkstry dla listy
                    auto end = chrono::high_resolution_clock::now(); // Zakończenie pomiaru czasu
                    auto elapsed = chrono::duration_cast<chrono::microseconds>(end - begin); // Obliczenie czasu wykonania
                    czas1 += elapsed; // Sumowanie czasu wykonania
                }
                cout << "Czas dla listy wyniosl: " << czas1.count() * UNIT / REPETITION << " ms" << endl; // Wyświetlenie średniego czasu wykonania dla listy

                std::chrono::duration<double> czas2{}; // Zmienna do przechowywania czasu wykonania dla macierzy
                for (int n = 0; n < REPETITION; n++) // Powtórzenia dla uzyskania średniego czasu
                {
                    MatrixGraph matrix; // Utworzenie grafu macierzowego
                    Graph graph; // Utworzenie obiektu grafu
                    graph.generateGraph(ver, den); // Generowanie grafu
                    matrix.populateFromGraph(graph, -1); // Wypełnienie grafu macierzowego

                    auto begin = chrono::high_resolution_clock::now(); // Rozpoczęcie pomiaru czasu
                    dijkstra.dijkstraMatrix(matrix, 0, ver); // Wywołanie algorytmu Dijkstry dla macierzy
                    auto end = chrono::high_resolution_clock::now(); // Zakończenie pomiaru czasu
                    auto elapsed = chrono::duration_cast<chrono::microseconds>(end - begin); // Obliczenie czasu wykonania
                    czas2 += elapsed; // Sumowanie czasu wykonania
                }
                cout << "Czas dla macierzy wyniosl: " << czas2.count() * UNIT / REPETITION << " ms" << endl; // Wyświetlenie średniego czasu wykonania dla macierzy
            }
        }
    }

    if (algnum == 4) // Algorytm Forda-Bellmana
    {
        cout << mode_name(algnum) << endl; // Wyświetlenie nazwy algorytmu
        for (int i = 0; i < 3; i++) // Iteracja po gęstościach
        {
            cout << "----- gestosc " << densities[i] << endl; // Wyświetlenie gęstości
            for (int j = 0; j < 7; j++) // Iteracja po liczbach wierzchołków
            {
                cout << "--- rozmiar " << vertexCounts[j] << endl; // Wyświetlenie liczby wierzchołków

                int ver = vertexCounts[j]; // Liczba wierzchołków
                float den = densities[i]; // Gęstość grafu

                std::chrono::duration<double> czas1{}; // Zmienna do przechowywania czasu wykonania dla listy
                for (int n = 0; n < REPETITION; n++) // Powtórzenia dla uzyskania średniego czasu
                {
                    ListGraph list; // Utworzenie grafu listowego
                    Graph graph; // Utworzenie obiektu grafu
                    graph.generateGraph(ver, den); // Generowanie grafu
                    list.populateFromGraph(graph); // Wypełnienie grafu listowego

                    auto begin = chrono::high_resolution_clock::now(); // Rozpoczęcie pomiaru czasu
                    FordBellman::fordBellmanList(list, 0, ver); // Wywołanie algorytmu Forda-Bellmana dla listy
                    auto end = chrono::high_resolution_clock::now(); // Zakończenie pomiaru czasu
                    auto elapsed = chrono::duration_cast<chrono::microseconds>(end - begin); // Obliczenie czasu wykonania
                    czas1 += elapsed; // Sumowanie czasu wykonania
                }
                cout << "Czas dla listy wyniosl: " << czas1.count() * UNIT / REPETITION << " ms" << endl; // Wyświetlenie średniego czasu wykonania dla listy

                std::chrono::duration<double> czas2{}; // Zmienna do przechowywania czasu wykonania dla macierzy
                for (int n = 0; n < REPETITION; n++) // Powtórzenia dla uzyskania średniego czasu
                {
                    MatrixGraph matrix; // Utworzenie grafu macierzowego
                    Graph graph; // Utworzenie obiektu grafu
                    graph.generateGraph(ver, den); // Generowanie grafu
                    matrix.populateFromGraph(graph, -1); // Wypełnienie grafu macierzowego

                    auto begin = chrono::high_resolution_clock::now(); // Rozpoczęcie pomiaru czasu
                    FordBellman::fordBellmanMatrix(matrix, 0, ver); // Wywołanie algorytmu Forda-Bellmana dla macierzy
                    auto end = chrono::high_resolution_clock::now(); // Zakończenie pomiaru czasu
                    auto elapsed = chrono::duration_cast<chrono::microseconds>(end - begin); // Obliczenie czasu wykonania
                    czas2 += elapsed; // Sumowanie czasu wykonania
                }
                cout << "Czas dla macierzy wyniosl: " << czas2.count() * UNIT / REPETITION << " ms" << endl; // Wyświetlenie średniego czasu wykonania dla macierzy
            }
        }
    }

    cout << endl << endl << endl; // Oddzielenie wyników pustymi liniami
}

// Definicja metody mode_name klasy Simulation
const char* Simulation::mode_name(int algnum)
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