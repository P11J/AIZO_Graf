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
    ListGraph list; // Obiekt grafu reprezentowanego list�
    MatrixGraph matrix; // Obiekt grafu reprezentowanego macierz�

    int choice = 0; // Zmienna przechowuj�ca wyb�r u�ytkownika
    bool y = true; // Flaga kontroluj�ca dzia�anie p�tli menu
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
                    graph.generateGraph(vertices, 0.25); // Generowanie grafu o g�sto�ci 25%
                    list.loadGraphToGraph(graph); // Wype�nienie grafu listowego
                    if (mode == 1)
                    {
                        matrix.loadGraphToGraph(graph, 1); // Wype�nienie grafu macierzowego
                    }
                    else if (mode == 2)
                    {
                        matrix.loadGraphToGraph(graph, -1); // Wype�nienie grafu macierzowego
                    }
                }
                else if (density == 2)
                {
                    Graph graph;
                    graph.generateGraph(vertices, 0.5); // Generowanie grafu o g�sto�ci 50%
                    list.loadGraphToGraph(graph); // Wype�nienie grafu listowego
                    if (mode == 1)
                    {
                        matrix.loadGraphToGraph(graph, 1); // Wype�nienie grafu macierzowego
                    }
                    else if (mode == 2)
                    {
                        matrix.loadGraphToGraph(graph, -1); // Wype�nienie grafu macierzowego
                    }
                }
                else if (density == 3)
                {
                    Graph graph;
                    graph.generateGraph(vertices, 0.99); // Generowanie grafu o g�sto�ci 99%
                    list.loadGraphToGraph(graph); // Wype�nienie grafu listowego
                    if (mode == 1)
                    {
                        matrix.loadGraphToGraph(graph, 1); // Wype�nienie grafu macierzowego
                    }
                    else if (mode == 2)
                    {
                        matrix.loadGraphToGraph(graph, -1); // Wype�nienie grafu macierzowego
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
                matrix.displayGraph(); // Wy�wietlenie grafu macierzowego
                matrix.shouldDeleteData = false; // Ustawienie flagi, aby nie usuwa� danych
                list.displayGraph(); // Wy�wietlenie grafu listowego
                list.shouldDeleteData = false; // Ustawienie flagi, aby nie usuwa� danych
                break;
            }

            case 5:
            {
                if (mode == 1)
                {
                    matrix.shouldDeleteData = false; // Ustawienie flagi, aby nie usuwa� danych
                    list.shouldDeleteData = false; // Ustawienie flagi, aby nie usuwa� danych
                    if (matrix.vertices <= 0 || matrix.incidenceMatrix == nullptr || matrix.weightsMatrix == nullptr)
                    {
                        cout << "Macierz incydencji nie jest poprawnie zaladowana." << endl;
                    }
                    else
                    {
                        auto begin = chrono::high_resolution_clock::now(); // Rozpocz�cie pomiaru czasu
                        Prim::primMatrix(matrix); // Wywo�anie algorytmu Prima dla macierzy
                        auto end = chrono::high_resolution_clock::now(); // Zako�czenie pomiaru czasu
                        auto elapsed = chrono::duration_cast<chrono::milliseconds>(end - begin); // Obliczenie czasu wykonania
                        cout << "Czas wykonania dla macierzy: " << elapsed.count() << " ms" << endl << endl;
                    }

                    if (list.vertices <= 0 || list.edgeCounts == nullptr || list.adjacencyList == nullptr)
                    {
                        cout << "Lista sasiedztwa nie jest poprawnie zaladowana." << endl;
                    }
                    else
                    {
                        auto begin = chrono::high_resolution_clock::now(); // Rozpocz�cie pomiaru czasu
                        Prim::primList(list); // Wywo�anie algorytmu Prima dla listy
                        auto end = chrono::high_resolution_clock::now(); // Zako�czenie pomiaru czasu
                        auto elapsed = chrono::duration_cast<chrono::milliseconds>(end - begin); // Obliczenie czasu wykonania
                        cout << "Czas wykonania dla listy: " << elapsed.count() << " ms" << endl << endl;
                    }
                }
                else if (mode == 2)
                {
                    Dijkstra dijkstra; // Utworzenie obiektu algorytmu Dijkstry
                    matrix.shouldDeleteData = false; // Ustawienie flagi, aby nie usuwa� danych
                    list.shouldDeleteData = false; // Ustawienie flagi, aby nie usuwa� danych

                    int startVertex, endVertex;
                    cout << "Podaj wierzcholek poczatkowy: ";
                    cin >> startVertex; // Odczytanie wierzcho�ka pocz�tkowego
                    cout << "Podaj wierzcholek koncowy: ";
                    cin >> endVertex; // Odczytanie wierzcho�ka ko�cowego
                    cout << endl;

                    if (matrix.vertices <= 0 || matrix.incidenceMatrix == nullptr || matrix.weightsMatrix == nullptr)
                    {
                        cout << "Macierz incydencji nie jest poprawnie zaladowana." << endl;
                    }
                    else
                    {
                        cout << "Macierz incydencji" << endl;
                        auto begin = chrono::high_resolution_clock::now(); // Rozpocz�cie pomiaru czasu
                        dijkstra.dijkstraMatrix(matrix, startVertex, endVertex); // Wywo�anie algorytmu Dijkstry dla macierzy
                        auto end = chrono::high_resolution_clock::now(); // Zako�czenie pomiaru czasu
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
                        auto begin = chrono::high_resolution_clock::now(); // Rozpocz�cie pomiaru czasu
                        dijkstra.dijkstraList(list, startVertex, endVertex); // Wywo�anie algorytmu Dijkstry dla listy
                        auto end = chrono::high_resolution_clock::now(); // Zako�czenie pomiaru czasu
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
                    matrix.shouldDeleteData = false; // Ustawienie flagi, aby nie usuwa� danych
                    list.shouldDeleteData = false; // Ustawienie flagi, aby nie usuwa� danych

                    if (matrix.vertices <= 0 || matrix.incidenceMatrix == nullptr || matrix.weightsMatrix == nullptr)
                    {
                        cout << "Macierz incydencji nie jest poprawnie zaladowana." << endl;
                    }
                    else
                    {
                        auto begin = chrono::high_resolution_clock::now(); // Rozpocz�cie pomiaru czasu
                        kruskal.kruskalMatrix(matrix); // Wywo�anie algorytmu Kruskala dla macierzy
                        auto end = chrono::high_resolution_clock::now(); // Zako�czenie pomiaru czasu
                        auto elapsed = chrono::duration_cast<chrono::milliseconds>(end - begin); // Obliczenie czasu wykonania
                        cout << "Czas wykonania dla macierzy: " << elapsed.count() << " ms" << endl << endl;
                    }

                    if (list.vertices <= 0 || list.edgeCounts == nullptr || list.adjacencyList == nullptr)
                    {
                        cout << "Lista sasiedztwa nie jest poprawnie zaladowana." << endl;
                    }
                    else
                    {
                        auto begin = chrono::high_resolution_clock::now(); // Rozpocz�cie pomiaru czasu
                        kruskal.kruskalList(list); // Wywo�anie algorytmu Kruskala dla listy
                        auto end = chrono::high_resolution_clock::now(); // Zako�czenie pomiaru czasu
                        auto elapsed = chrono::duration_cast<chrono::milliseconds>(end - begin); // Obliczenie czasu wykonania
                        cout << "Czas wykonania dla listy: " << elapsed.count() << " ms" << endl << endl;
                    }
                }
                else if (mode == 2)
                {
                    matrix.shouldDeleteData = false; // Ustawienie flagi, aby nie usuwa� danych
                    list.shouldDeleteData = false; // Ustawienie flagi, aby nie usuwa� danych

                    int startVertex, endVertex;
                    cout << "Podaj wierzcholek poczatkowy: ";
                    cin >> startVertex; // Odczytanie wierzcho�ka pocz�tkowego
                    cout << "Podaj wierzcholek koncowy: ";
                    cin >> endVertex; // Odczytanie wierzcho�ka ko�cowego
                    cout << endl;

                    if (matrix.vertices <= 0 || matrix.incidenceMatrix == nullptr || matrix.weightsMatrix == nullptr)
                    {
                        cout << "Macierz incydencji nie jest poprawnie zaladowana." << endl;
                    }
                    else
                    {
                        auto begin = chrono::high_resolution_clock::now(); // Rozpocz�cie pomiaru czasu
                        FordBellman::fordBellmanMatrix(matrix, startVertex, endVertex); // Wywo�anie algorytmu Forda-Bellmana dla macierzy
                        auto end = chrono::high_resolution_clock::now(); // Zako�czenie pomiaru czasu
                        auto elapsed = chrono::duration_cast<chrono::milliseconds>(end - begin); // Obliczenie czasu wykonania
                        cout << "Czas wykonania dla macierzy: " << elapsed.count() << " ms" << endl << endl;
                    }

                    if (list.vertices <= 0 || list.edgeCounts == nullptr || list.adjacencyList == nullptr)
                    {
                        cout << "Lista sasiedztwa nie jest poprawnie zaladowana." << endl;
                    }
                    else
                    {
                        auto begin = chrono::high_resolution_clock::now(); // Rozpocz�cie pomiaru czasu
                        FordBellman::fordBellmanList(list, startVertex, endVertex); // Wywo�anie algorytmu Forda-Bellmana dla listy
                        auto end = chrono::high_resolution_clock::now(); // Zako�czenie pomiaru czasu
                        auto elapsed = chrono::duration_cast<chrono::milliseconds>(end - begin); // Obliczenie czasu wykonania
                        cout << "Czas wykonania dla listy: " << elapsed.count() << " ms" << endl << endl;
                    }
                }
                break;
            }

            case 7:
            {
                Simulation::simulationMode(1); // Wywo�anie trybu symulacji 1
                Simulation::simulationMode(2); // Wywo�anie trybu symulacji 2
                Simulation::simulationMode(3); // Wywo�anie trybu symulacji 3
                Simulation::simulationMode(4); // Wywo�anie trybu symulacji 4
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
                exit(0); // Zako�czenie dzia�ania programu
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
