#ifndef SIMULATION_H
#define SIMULATION_H

#include "Graphs/ListGraph.h"

class Simulation
{
public:
    // Metoda do uruchomienia trybu symulacji dla danego algorytmu
    void simulation_mode(int algnum);

    // Metoda zwracaj¹ca nazwê algorytmu na podstawie numeru
    static const char* mode_name(int algnum);
};

#endif // SIMULATION_H