#ifndef GRAPH_MATRIX_H
#define GRAPH_MATRIX_H

#include "GraphGenerator.h"
#include <string>

using namespace std;

// Definicja klasy MatrixGraph do reprezentacji grafu za pomoc¹ macierzy incydencji
class MatrixGraph
{
public:
    int vertices; // Liczba wierzcho³ków w grafie
    int edges; // Liczba krawêdzi w grafie
    int** incidenceMatrix; // Macierz incydencji
    int* weightsMatrix; // Tablica przechowuj¹ca wagi krawêdzi
    bool shouldDeleteData; // Flaga okreœlaj¹ca, czy dane powinny byæ usuniête

    // Konstruktor klasy MatrixGraph
    MatrixGraph();

    // Destruktor klasy MatrixGraph
    ~MatrixGraph();

    // Metoda wczytuj¹ca graf z pliku
    void load_graph(string& filename, int type);

    // Metoda zapisuj¹ca graf do pliku (naj)
    void save_graph_naj() const;

    // Metoda zapisuj¹ca graf do pliku (mst)
    void save_graph_mst() const;

    // Metoda wyœwietlaj¹ca graf
    void display_graph() const;

    // Metoda wype³niaj¹ca graf na podstawie obiektu Graph
    void populateFromGraph(Graph& graph, int type);

    // Metoda sprawdzaj¹ca, czy graf jest poprawny
    bool isGraphValid() const;
};

#endif // GRAPH_MATRIX_H
