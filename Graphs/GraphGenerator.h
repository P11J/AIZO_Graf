#ifndef GENERATE_H
#define GENERATE_H

#include <string>

// Definicja klasy Graph do reprezentacji grafu
class Graph
{
public:
    int vertices; // Liczba wierzcho�k�w w grafie
    int edges; // Liczba kraw�dzi w grafie
    int* startVertices; // Tablica przechowuj�ca pocz�tki kraw�dzi
    int* endVertices; // Tablica przechowuj�ca ko�ce kraw�dzi
    int* weights; // Tablica przechowuj�ca wagi kraw�dzi

    // Konstruktor klasy Graph
    Graph();

    // Destruktor klasy Graph
    ~Graph();

    // Metoda generuj�ca graf o zadanej liczbie wierzcho�k�w i g�sto�ci
    void generateGraph(int vertices2, float density);

    // Metoda sprawdzaj�ca, czy graf jest poprawny
    bool isGraphValid() const;
};

#endif // GENERATE_H

