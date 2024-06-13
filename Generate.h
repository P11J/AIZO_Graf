#ifndef GENERATE_H
#define GENERATE_H

#include <string>

class Graph 
{
public:
    int vertices;
    int edges;
    int* startVertices; // Tablica przechowuj�ca pocz�tki kraw�dzi
    int* endVertices;   // Tablica przechowuj�ca ko�ce kraw�dzi
    int* weights;       // Tablica przechowuj�ca wagi kraw�dzi

    Graph();
    ~Graph();

    void generateGraph(int vertices, float density);
    bool isGraphValid();


};

#endif GENERATE_H


