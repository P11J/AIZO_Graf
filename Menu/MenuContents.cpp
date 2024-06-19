#include "MenuContents.h"
#include "Graphs/MatrixGraph.h"
#include "Graphs/ListGraph.h"
#include "Algorithms/Prim.h"
#include "Algorithms/Kruskal.h"
#include "Algorithms/Dijkstra.h"
#include "Algorithms/FordBellman.h"
#include "Simulation/Simulation.h"

#include <iostream>
#include <string>
#include <cstdlib>
#include <chrono>

using namespace std;


void MenuContents::menuSettings(int mode)
{
    ListGraph list; // Obiekt grafu reprezentowanego list¹
    MatrixGraph matrix; // Obiekt grafu reprezentowanego macierz¹

    int choice = 0; // Zmienna przechowuj¹ca wybór u¿ytkownika
    bool y = true; // Flaga kontroluj¹ca dzia³anie pêtli menu
    while (y)
    {
        cout << endl;
        cout << "Wybierz funkcje programu: " << endl;
        cout << "1. Odczyt grafu z pliku" << endl;
        cout << "2. Zapis grafu do pliku " << endl;
        cout << "3. Generowanie grafu" << endl;
        cout << "4. Wyswietlenie grafu listowo i macierzowo" << endl;
        if (mode == 1)
        {
            cout << "5. Wybor algorytmu Prima" << endl;
            cout << "6. Wybor algorytmu Kruskala" << endl;
        }
        else if (mode == 2)
        {
            cout << "5. Wybor algorytmu Dijkstry" << endl;
            cout << "6. Wybor algorytmu Forda-Bellmana" << endl;
        }
        cout << "7. Tryb symulacji" << endl;
        cout << "8. Zmien problem" << endl;
        cout << "9. Wylaczenie programu" << endl;
        cout << endl;
        cin >> choice;


        switch (choice)
        {
            case 1:
            {
                string filename;
                cout << "Podaj nazwe pliku: ";
                cin >> filename;
                if (mode == 1)
                {
                    matrix.loadGraph(filename, 1); // Wczytanie grafu macierzowego
                    list.loadGraph(filename, 1); // Wczytanie grafu listowego
                }
                else if (mode == 2)
                {
                    matrix.loadGraph(filename, -1); // Wczytanie grafu macierzowego
                    list.loadGraph(filename, 2); // Wczytanie grafu listowego
                }
                break;
            }

            case 2:
            {
                if (mode == 1)
                {
                    matrix.saveGraphMST(); // Zapis grafu macierzowego
                    list.saveGraph(); // Zapis grafu listowego
                }
                else if (mode == 2)
                {
                    matrix.saveGraphSTP(); // Zapis grafu macierzowego
                    list.saveGraph(); // Zapis grafu listowego
                }
                break;
            }

            case 3:
            {
                int vertices;
                float density;
                cout << "Podaj liczbe wierzcholkow: ";
                cin >> vertices;
                cout << "Podaj gestosc grafu:" << endl;
                cout << "1. 25%" << endl;
                cout << "2. 50%" << endl;
                cout << "3. 99%" << endl;
                cin >> density;
                if (density == 1)
                {
                    Graph graph;
                    graph.generateGraph(vertices, 0.25); // Generowanie grafu o gêstoœci 25%
                    list.loadGraphToGraph(graph); // Wype³nienie grafu listowego
                    if (mode == 1)
                    {
                        matrix.loadGraphToGraph(graph, 1); // Wype³nienie grafu macierzowego
                    }
                    else if (mode == 2)
                    {
                        matrix.loadGraphToGraph(graph, -1); // Wype³nienie grafu macierzowego
                    }
                }
                else if (density == 2)
                {
                    Graph graph;
                    graph.generateGraph(vertices, 0.5); // Generowanie grafu o gêstoœci 50%
                    list.loadGraphToGraph(graph); // Wype³nienie grafu listowego
                    if (mode == 1)
                    {
                        matrix.loadGraphToGraph(graph, 1); // Wype³nienie grafu macierzowego
                    }
                    else if (mode == 2)
                    {
                        matrix.loadGraphToGraph(graph, -1); // Wype³nienie grafu macierzowego
                    }
                }
                else if (density == 3)
                {
                    Graph graph;
                    graph.generateGraph(vertices, 0.99); // Generowanie grafu o gêstoœci 99%
                    list.loadGraphToGraph(graph); // Wype³nienie grafu listowego
                    if (mode == 1)
                    {
                        matrix.loadGraphToGraph(graph, 1); // Wype³nienie grafu macierzowego
                    }
                    else if (mode == 2)
                    {
                        matrix.loadGraphToGraph(graph, -1); // Wype³nienie grafu macierzowego
                    }
                }
                else
                {
                    cout << "Bledna gestosc" << endl;
                }
                break;
            }

            case 4:
            {
                matrix.displayGraph(); // Wyœwietlenie grafu macierzowego
                matrix.shouldDeleteData = false; // Ustawienie flagi, aby nie usuwaæ danych
                list.displayGraph(); // Wyœwietlenie grafu listowego
                list.shouldDeleteData = false; // Ustawienie flagi, aby nie usuwaæ danych
                break;
            }

            case 5:
            {
                if (mode == 1)
                {
                    matrix.shouldDeleteData = false; // Ustawienie flagi, aby nie usuwaæ danych
                    list.shouldDeleteData = false; // Ustawienie flagi, aby nie usuwaæ danych
                    if (matrix.vertices <= 0 || matrix.incidenceMatrix == nullptr || matrix.weightsMatrix == nullptr)
                    {
                        cout << "Macierz incydencji nie jest poprawnie zaladowana." << endl;
                    }
                    else
                    {
                        auto begin = chrono::high_resolution_clock::now(); // Rozpoczêcie pomiaru czasu
                        Prim::primMatrix(matrix); // Wywo³anie algorytmu Prima dla macierzy
                        auto end = chrono::high_resolution_clock::now(); // Zakoñczenie pomiaru czasu
                        auto elapsed = chrono::duration_cast<chrono::milliseconds>(end - begin); // Obliczenie czasu wykonania
                        cout << "Czas wykonania dla macierzy: " << elapsed.count() << " ms" << endl << endl;
                    }

                    if (list.vertices <= 0 || list.edgeCounts == nullptr || list.adjacencyList == nullptr)
                    {
                        cout << "Lista sasiedztwa nie jest poprawnie zaladowana." << endl;
                    }
                    else
                    {
                        auto begin = chrono::high_resolution_clock::now(); // Rozpoczêcie pomiaru czasu
                        Prim::primList(list); // Wywo³anie algorytmu Prima dla listy
                        auto end = chrono::high_resolution_clock::now(); // Zakoñczenie pomiaru czasu
                        auto elapsed = chrono::duration_cast<chrono::milliseconds>(end - begin); // Obliczenie czasu wykonania
                        cout << "Czas wykonania dla listy: " << elapsed.count() << " ms" << endl << endl;
                    }
                }
                else if (mode == 2)
                {
                    Dijkstra dijkstra; // Utworzenie obiektu algorytmu Dijkstry
                    matrix.shouldDeleteData = false; // Ustawienie flagi, aby nie usuwaæ danych
                    list.shouldDeleteData = false; // Ustawienie flagi, aby nie usuwaæ danych

                    int startVertex, endVertex;
                    cout << "Podaj wierzcholek poczatkowy: ";
                    cin >> startVertex; // Odczytanie wierzcho³ka pocz¹tkowego
                    cout << "Podaj wierzcholek koncowy: ";
                    cin >> endVertex; // Odczytanie wierzcho³ka koñcowego
                    cout << endl;

                    if (matrix.vertices <= 0 || matrix.incidenceMatrix == nullptr || matrix.weightsMatrix == nullptr)
                    {
                        cout << "Macierz incydencji nie jest poprawnie zaladowana." << endl;
                    }
                    else
                    {
                        cout << "Macierz incydencji" << endl;
                        auto begin = chrono::high_resolution_clock::now(); // Rozpoczêcie pomiaru czasu
                        dijkstra.dijkstraMatrix(matrix, startVertex, endVertex); // Wywo³anie algorytmu Dijkstry dla macierzy
                        auto end = chrono::high_resolution_clock::now(); // Zakoñczenie pomiaru czasu
                        auto elapsed = chrono::duration_cast<chrono::milliseconds>(end - begin); // Obliczenie czasu wykonania
                        cout << "Czas wykonania dla macierzy: " << elapsed.count() << " ms" << endl << endl;
                    }

                    if (list.vertices <= 0 || list.edgeCounts == nullptr || list.adjacencyList == nullptr)
                    {
                        cout << "Lista sasiedztwa nie jest poprawnie zaladowana." << endl;
                    }
                    else
                    {
                        cout << "Lista sasiedztwa" << endl;
                        auto begin = chrono::high_resolution_clock::now(); // Rozpoczêcie pomiaru czasu
                        dijkstra.dijkstraList(list, startVertex, endVertex); // Wywo³anie algorytmu Dijkstry dla listy
                        auto end = chrono::high_resolution_clock::now(); // Zakoñczenie pomiaru czasu
                        auto elapsed = chrono::duration_cast<chrono::milliseconds>(end - begin); // Obliczenie czasu wykonania
                        cout << "Czas wykonania dla listy: " << elapsed.count() << " ms" << endl << endl;
                    }
                }
                break;
            }

            case 6:
            {
                if (mode == 1)
                {
                    Kruskal kruskal; // Utworzenie obiektu algorytmu Kruskala
                    matrix.shouldDeleteData = false; // Ustawienie flagi, aby nie usuwaæ danych
                    list.shouldDeleteData = false; // Ustawienie flagi, aby nie usuwaæ danych

                    if (matrix.vertices <= 0 || matrix.incidenceMatrix == nullptr || matrix.weightsMatrix == nullptr)
                    {
                        cout << "Macierz incydencji nie jest poprawnie zaladowana." << endl;
                    }
                    else
                    {
                        auto begin = chrono::high_resolution_clock::now(); // Rozpoczêcie pomiaru czasu
                        kruskal.kruskalMatrix(matrix); // Wywo³anie algorytmu Kruskala dla macierzy
                        auto end = chrono::high_resolution_clock::now(); // Zakoñczenie pomiaru czasu
                        auto elapsed = chrono::duration_cast<chrono::milliseconds>(end - begin); // Obliczenie czasu wykonania
                        cout << "Czas wykonania dla macierzy: " << elapsed.count() << " ms" << endl << endl;
                    }

                    if (list.vertices <= 0 || list.edgeCounts == nullptr || list.adjacencyList == nullptr)
                    {
                        cout << "Lista sasiedztwa nie jest poprawnie zaladowana." << endl;
                    }
                    else
                    {
                        auto begin = chrono::high_resolution_clock::now(); // Rozpoczêcie pomiaru czasu
                        kruskal.kruskalList(list); // Wywo³anie algorytmu Kruskala dla listy
                        auto end = chrono::high_resolution_clock::now(); // Zakoñczenie pomiaru czasu
                        auto elapsed = chrono::duration_cast<chrono::milliseconds>(end - begin); // Obliczenie czasu wykonania
                        cout << "Czas wykonania dla listy: " << elapsed.count() << " ms" << endl << endl;
                    }
                }
                else if (mode == 2)
                {
                    matrix.shouldDeleteData = false; // Ustawienie flagi, aby nie usuwaæ danych
                    list.shouldDeleteData = false; // Ustawienie flagi, aby nie usuwaæ danych

                    int startVertex, endVertex;
                    cout << "Podaj wierzcholek poczatkowy: ";
                    cin >> startVertex; // Odczytanie wierzcho³ka pocz¹tkowego
                    cout << "Podaj wierzcholek koncowy: ";
                    cin >> endVertex; // Odczytanie wierzcho³ka koñcowego
                    cout << endl;

                    if (matrix.vertices <= 0 || matrix.incidenceMatrix == nullptr || matrix.weightsMatrix == nullptr)
                    {
                        cout << "Macierz incydencji nie jest poprawnie zaladowana." << endl;
                    }
                    else
                    {
                        auto begin = chrono::high_resolution_clock::now(); // Rozpoczêcie pomiaru czasu
                        FordBellman::fordBellmanMatrix(matrix, startVertex, endVertex); // Wywo³anie algorytmu Forda-Bellmana dla macierzy
                        auto end = chrono::high_resolution_clock::now(); // Zakoñczenie pomiaru czasu
                        auto elapsed = chrono::duration_cast<chrono::milliseconds>(end - begin); // Obliczenie czasu wykonania
                        cout << "Czas wykonania dla macierzy: " << elapsed.count() << " ms" << endl << endl;
                    }

                    if (list.vertices <= 0 || list.edgeCounts == nullptr || list.adjacencyList == nullptr)
                    {
                        cout << "Lista sasiedztwa nie jest poprawnie zaladowana." << endl;
                    }
                    else
                    {
                        auto begin = chrono::high_resolution_clock::now(); // Rozpoczêcie pomiaru czasu
                        FordBellman::fordBellmanList(list, startVertex, endVertex); // Wywo³anie algorytmu Forda-Bellmana dla listy
                        auto end = chrono::high_resolution_clock::now(); // Zakoñczenie pomiaru czasu
                        auto elapsed = chrono::duration_cast<chrono::milliseconds>(end - begin); // Obliczenie czasu wykonania
                        cout << "Czas wykonania dla listy: " << elapsed.count() << " ms" << endl << endl;
                    }
                }
                break;
            }

            case 7:
            {
                Simulation::simulationMode(1); // Wywo³anie trybu symulacji 1
                Simulation::simulationMode(2); // Wywo³anie trybu symulacji 2
                Simulation::simulationMode(3); // Wywo³anie trybu symulacji 3
                Simulation::simulationMode(4); // Wywo³anie trybu symulacji 4
                break;
            }

            case 8:
            {
                y = false;
                break;
            }

            case 9:
            {
                y = false;
                cout << "Zakonczono dzialanie programu" << endl;
                exit(0); // Zakoñczenie dzia³ania programu
                break;
            }

            default:
            {
                cout << "Wybrano niepoprawna opcje" << endl; // Komunikat o niepoprawnym wyborze
                break;
            }
        }
    }
}
