#ifndef GRAPH_LIST_H
#define GRAPH_LIST_H

#include "GraphGenerator.h"
#include <string>
#include "MyPair.h"

using namespace std;

// Definicja klasy ListGraph do reprezentacji grafu za pomoc� listy s�siedztwa
class ListGraph
{
public:
    int vertices; // Liczba wierzcho�k�w w grafie
    int edges; // Liczba kraw�dzi w grafie
    int* edgeCounts; // Tablica przechowuj�ca liczb� kraw�dzi dla ka�dego wierzcho�ka
    MyPair<int, int>** adjacencyList; // Tablica tablic (lista s�siedztwa)
    bool shouldDeleteData; // Flaga okre�laj�ca, czy dane powinny by� usuni�te

    ListGraph* next{}; // Wska�nik na nast�pny graf w strukturze danych

    // Konstruktor klasy ListGraph
    ListGraph();

    // Destruktor klasy ListGraph
    ~ListGraph();

    // Metoda wczytuj�ca graf z pliku
    void load_graph(string& filename, int mode);

    // Metoda zapisuj�ca graf do pliku
    void save_graph();

    // Metoda wy�wietlaj�ca graf
    void display_graph();

    // Metoda wype�niaj�ca graf na podstawie obiektu Graph
    void populateFromGraph(Graph& graph);

    // Metoda sprawdzaj�ca, czy graf jest poprawny
    bool isGraphValid() const;
};

#endif // GRAPH_LIST_H