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
    void loadGraph(string& filename, int type);

    // Metoda zapisuj�ca graf do pliku (naj)
    void saveGraphSTP() const;

    // Metoda zapisuj�ca graf do pliku (mst)
    void saveGraphMST() const;

    // Metoda wy�wietlaj�ca graf
    void displayGraph() const;

    // Metoda wype�niaj�ca graf na podstawie obiektu Graph
    void loadGraphToGraph(Graph& graph, int type);

    // Metoda sprawdzaj�ca, czy graf jest poprawny
    bool isGraphValid() const;
};

#endif // GRAPH_MATRIX_H
