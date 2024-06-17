#ifndef GRAPH_MATRIX_H
#define GRAPH_MATRIX_H

#include "GraphGenerator.h"
#include <string>

using namespace std;

// Definicja klasy MatrixGraph do reprezentacji grafu za pomoc� macierzy incydencji
class MatrixGraph
{
public:
    int vertices; // Liczba wierzcho�k�w w grafie
    int edges; // Liczba kraw�dzi w grafie
    int** incidenceMatrix; // Macierz incydencji
    int* weightsMatrix; // Tablica przechowuj�ca wagi kraw�dzi
    bool shouldDeleteData; // Flaga okre�laj�ca, czy dane powinny by� usuni�te

    // Konstruktor klasy MatrixGraph
    MatrixGraph();

    // Destruktor klasy MatrixGraph
    ~MatrixGraph();

    // Metoda wczytuj�ca graf z pliku
    void load_graph(string& filename, int type);

    // Metoda zapisuj�ca graf do pliku (naj)
    void save_graph_naj() const;

    // Metoda zapisuj�ca graf do pliku (mst)
    void save_graph_mst() const;

    // Metoda wy�wietlaj�ca graf
    void display_graph() const;

    // Metoda wype�niaj�ca graf na podstawie obiektu Graph
    void populateFromGraph(Graph& graph, int type);

    // Metoda sprawdzaj�ca, czy graf jest poprawny
    bool isGraphValid() const;
};

#endif // GRAPH_MATRIX_H
