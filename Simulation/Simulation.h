#ifndef SIMULATION_H
#define SIMULATION_H

#include "Graphs/ListGraph.h"

class Simulation
{
public:
    // Metoda do uruchomienia trybu symulacji dla danego algorytmu
    static void simulationMode(int algNum);

    // Metoda zwracaj¹ca nazwê algorytmu na podstawie numeru
    static const char* modeName(int algnum);
};

#endif // SIMULATION_H