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
    void loadGraph(string& filename, int type);

    // Metoda zapisuj¹ca graf do pliku (naj)
    void saveGraphSTP() const;

    // Metoda zapisuj¹ca graf do pliku (mst)
    void saveGraphMST() const;

    // Metoda wyœwietlaj¹ca graf
    void displayGraph() const;

    // Metoda wype³niaj¹ca graf na podstawie obiektu Graph
    void loadGraphToGraph(Graph& graph, int type);

    // Metoda sprawdzaj¹ca, czy graf jest poprawny
    bool isGraphValid() const;
};

#endif // GRAPH_MATRIX_H
