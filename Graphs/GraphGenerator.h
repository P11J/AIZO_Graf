#ifndef GENERATE_H
#define GENERATE_H

#include <string>

// Definicja klasy Graph do reprezentacji grafu
class Graph
{
public:
    int vertices; // Liczba wierzcho³ków w grafie
    int edges; // Liczba krawêdzi w grafie
    int* startVertices; // Tablica przechowuj¹ca pocz¹tki krawêdzi
    int* endVertices; // Tablica przechowuj¹ca koñce krawêdzi
    int* weights; // Tablica przechowuj¹ca wagi krawêdzi

    // Konstruktor klasy Graph
    Graph();

    // Destruktor klasy Graph
    ~Graph();

    // Metoda generuj¹ca graf o zadanej liczbie wierzcho³ków i gêstoœci
    void generateGraph(int vertices2, float density);

    // Metoda sprawdzaj¹ca, czy graf jest poprawny
    bool isGraphValid() const;
};

#endif // GENERATE_H

