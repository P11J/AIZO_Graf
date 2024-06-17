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

// Definicja metody f_menu_settings klasy MenuContents
void MenuContents::f_menu_settings(int mode)
{
    ListGraph list; // Obiekt grafu reprezentowanego list�
    MatrixGraph matrix; // Obiekt grafu reprezentowanego macierz�

    int wybor_funkcji = 0; // Zmienna przechowuj�ca wyb�r u�ytkownika
    bool y = true; // Flaga kontroluj�ca dzia�anie p�tli menu
    while (y)
    {
        //system("cls"); // Wyczyszczenie ekranu (zakomentowane)
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
        cin >> wybor_funkcji; // Odczytanie wyboru u�ytkownika

        // Obs�uga wyboru u�ytkownika
        switch (wybor_funkcji)
        {
            case 1:
            {
                string filename;
                cout << "Podaj nazwe pliku: ";
                cin >> filename; // Odczytanie nazwy pliku
                if (mode == 1)
                {
                    matrix.load_graph(filename, 1); // Wczytanie grafu macierzowego
                    list.load_graph(filename, 1); // Wczytanie grafu listowego
                }
                else if (mode == 2)
                {
                    matrix.load_graph(filename, -1); // Wczytanie grafu macierzowego
                    list.load_graph(filename, 2); // Wczytanie grafu listowego
                }
                break;
            }

            case 2:
            {
                if (mode == 1)
                {
                    matrix.save_graph_mst(); // Zapis grafu macierzowego
                    list.save_graph(); // Zapis grafu listowego
                }
                else if (mode == 2)
                {
                    matrix.save_graph_naj(); // Zapis grafu macierzowego
                    list.save_graph(); // Zapis grafu listowego
                }
                break;
            }

            case 3:
            {
                int vertices;
                float density;
                cout << "Podaj liczbe wierzcholkow: ";
                cin >> vertices; // Odczytanie liczby wierzcho�k�w
                cout << "Podaj gestosc grafu: 1. 25%" << endl;
                cout << "                     2. 50%" << endl;
                cout << "                     3. 99%" << endl;
                cout << endl;
                cin >> density; // Odczytanie g�sto�ci grafu
                if (density == 1)
                {
                    Graph graph;
                    graph.generateGraph(vertices, 0.25); // Generowanie grafu o g�sto�ci 25%
                    list.populateFromGraph(graph); // Wype�nienie grafu listowego
                    if (mode == 1)
                    {
                        matrix.populateFromGraph(graph, 1); // Wype�nienie grafu macierzowego
                    }
                    else if (mode == 2)
                    {
                        matrix.populateFromGraph(graph, -1); // Wype�nienie grafu macierzowego
                    }
                }
                else if (density == 2)
                {
                    Graph graph;
                    graph.generateGraph(vertices, 0.5); // Generowanie grafu o g�sto�ci 50%
                    list.populateFromGraph(graph); // Wype�nienie grafu listowego
                    if (mode == 1)
                    {
                        matrix.populateFromGraph(graph, 1); // Wype�nienie grafu macierzowego
                    }
                    else if (mode == 2)
                    {
                        matrix.populateFromGraph(graph, -1); // Wype�nienie grafu macierzowego
                    }
                }
                else if (density == 3)
                {
                    Graph graph;
                    graph.generateGraph(vertices, 0.99); // Generowanie grafu o g�sto�ci 99%
                    list.populateFromGraph(graph); // Wype�nienie grafu listowego
                    if (mode == 1)
                    {
                        matrix.populateFromGraph(graph, 1); // Wype�nienie grafu macierzowego
                    }
                    else if (mode == 2)
                    {
                        matrix.populateFromGraph(graph, -1); // Wype�nienie grafu macierzowego
                    }
                }
                else
                {
                    cout << "Bledna gestosc" << endl; // Komunikat o b��dnej g�sto�ci
                }
                break;
            }

            case 4:
            {
                matrix.display_graph(); // Wy�wietlenie grafu macierzowego
                matrix.shouldDeleteData = false; // Ustawienie flagi, aby nie usuwa� danych
                list.display_graph(); // Wy�wietlenie grafu listowego
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
                        Alg_Prim::Prim_matrix(matrix, true); // Wywo�anie algorytmu Prima dla macierzy
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
                        Alg_Prim::Prim_list(list, true); // Wywo�anie algorytmu Prima dla listy
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

                    int startV, endV;
                    cout << "Podaj wierzcholek poczatkowy: ";
                    cin >> startV; // Odczytanie wierzcho�ka pocz�tkowego
                    cout << "Podaj wierzcholek koncowy: ";
                    cin >> endV; // Odczytanie wierzcho�ka ko�cowego
                    cout << endl;

                    if (matrix.vertices <= 0 || matrix.incidenceMatrix == nullptr || matrix.weightsMatrix == nullptr)
                    {
                        cout << "Macierz incydencji nie jest poprawnie zaladowana." << endl;
                    }
                    else
                    {
                        cout << "Macierz incydencji" << endl;
                        auto begin = chrono::high_resolution_clock::now(); // Rozpocz�cie pomiaru czasu
                        dijkstra.dijkstraMatrix(matrix, startV, endV); // Wywo�anie algorytmu Dijkstry dla macierzy
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
                        dijkstra.dijkstraList(list, startV, endV); // Wywo�anie algorytmu Dijkstry dla listy
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
                    Alg_Kruskal kruskal; // Utworzenie obiektu algorytmu Kruskala
                    matrix.shouldDeleteData = false; // Ustawienie flagi, aby nie usuwa� danych
                    list.shouldDeleteData = false; // Ustawienie flagi, aby nie usuwa� danych

                    if (matrix.vertices <= 0 || matrix.incidenceMatrix == nullptr || matrix.weightsMatrix == nullptr)
                    {
                        cout << "Macierz incydencji nie jest poprawnie zaladowana." << endl;
                    }
                    else
                    {
                        auto begin = chrono::high_resolution_clock::now(); // Rozpocz�cie pomiaru czasu
                        kruskal.Kruskal_matrix(matrix, true); // Wywo�anie algorytmu Kruskala dla macierzy
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
                        kruskal.Kruskal_list(list, true); // Wywo�anie algorytmu Kruskala dla listy
                        auto end = chrono::high_resolution_clock::now(); // Zako�czenie pomiaru czasu
                        auto elapsed = chrono::duration_cast<chrono::milliseconds>(end - begin); // Obliczenie czasu wykonania
                        cout << "Czas wykonania dla listy: " << elapsed.count() << " ms" << endl << endl;
                    }
                }
                else if (mode == 2)
                {
                    matrix.shouldDeleteData = false; // Ustawienie flagi, aby nie usuwa� danych
                    list.shouldDeleteData = false; // Ustawienie flagi, aby nie usuwa� danych

                    int startV, endV;
                    cout << "Podaj wierzcholek poczatkowy: ";
                    cin >> startV; // Odczytanie wierzcho�ka pocz�tkowego
                    cout << "Podaj wierzcholek koncowy: ";
                    cin >> endV; // Odczytanie wierzcho�ka ko�cowego
                    cout << endl;

                    if (matrix.vertices <= 0 || matrix.incidenceMatrix == nullptr || matrix.weightsMatrix == nullptr)
                    {
                        cout << "Macierz incydencji nie jest poprawnie zaladowana." << endl;
                    }
                    else
                    {
                        auto begin = chrono::high_resolution_clock::now(); // Rozpocz�cie pomiaru czasu
                        FordBellman::fordBellmanMatrix(matrix, startV, endV); // Wywo�anie algorytmu Forda-Bellmana dla macierzy
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
                        FordBellman::fordBellmanList(list, startV, endV); // Wywo�anie algorytmu Forda-Bellmana dla listy
                        auto end = chrono::high_resolution_clock::now(); // Zako�czenie pomiaru czasu
                        auto elapsed = chrono::duration_cast<chrono::milliseconds>(end - begin); // Obliczenie czasu wykonania
                        cout << "Czas wykonania dla listy: " << elapsed.count() << " ms" << endl << endl;
                    }
                }
                break;
            }

            case 7:
            {
                Simulation simulation; // Utworzenie obiektu symulacji
                simulation.simulation_mode(1); // Wywo�anie trybu symulacji 1
                simulation.simulation_mode(2); // Wywo�anie trybu symulacji 2
                simulation.simulation_mode(3); // Wywo�anie trybu symulacji 3
                simulation.simulation_mode(4); // Wywo�anie trybu symulacji 4
                break;
            }

            case 8:
            {
                y = false; // Wyj�cie z p�tli menu
                break;
            }

            case 9:
            {
                y = false; // Wyj�cie z p�tli menu
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
