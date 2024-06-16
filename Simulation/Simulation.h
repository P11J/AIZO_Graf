#ifndef SIMULATION_H
#define SIMULATION_H

#include "Graphs/ListGraph.h"

class Simulation
{
public:
	void simulation_mode(int algnum);
	const char* mode_name(int algnum);
};

#endif SIMULATION_H