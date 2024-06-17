#ifndef GRAPH_LIST_H
#define GRAPH_LIST_H

#include "GraphGenerator.h"
#include <string>
#include "MyPair.h"

using namespace std;

// Definicja klasy ListGraph do reprezentacji grafu za pomoc¹ listy s¹siedztwa
class ListGraph
{
public:
    int vertices; // Liczba wierzcho³ków w grafie
    int edges; // Liczba krawêdzi w grafie
    int* edgeCounts; // Tablica przechowuj¹ca liczbê krawêdzi dla ka¿dego wierzcho³ka
    MyPair<int, int>** adjacencyList; // Tablica tablic (lista s¹siedztwa)
    bool shouldDeleteData; // Flaga okreœlaj¹ca, czy dane powinny byæ usuniête

    ListGraph* next{}; // WskaŸnik na nastêpny graf w strukturze danych

    // Konstruktor klasy ListGraph
    ListGraph();

    // Destruktor klasy ListGraph
    ~ListGraph();

    // Metoda wczytuj¹ca graf z pliku
    void load_graph(string& filename, int mode);

    // Metoda zapisuj¹ca graf do pliku
    void save_graph();

    // Metoda wyœwietlaj¹ca graf
    void display_graph();

    // Metoda wype³niaj¹ca graf na podstawie obiektu Graph
    void populateFromGraph(Graph& graph);

    // Metoda sprawdzaj¹ca, czy graf jest poprawny
    bool isGraphValid() const;
};

#endif // GRAPH_LIST_H