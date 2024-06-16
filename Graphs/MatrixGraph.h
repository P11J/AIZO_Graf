#ifndef GRAPH_MATRIX_H
#define GRAPH_MATRIX_H

#include "GraphGenerator.h"
#include <string>

using namespace std;

class MatrixGraph
{
public:
    int vertices;
    int edges;
    int** incidenceMatrix; // Macierz incydencji
    int* weightsMatrix; // Tablica przechowuj¹ca wagi krawêdzi
    bool shouldDeleteData;

    MatrixGraph();
    ~MatrixGraph();

    void load_graph(string& filename, int type);
    void save_graph_naj();
    void save_graph_mst();
    void display_graph();
    void populateFromGraph(Graph& graph, int type);
    bool isGraphValid();

};

#endif GRAPH_MATRIX_H
