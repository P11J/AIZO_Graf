#ifndef ALG_PRIM
#define ALG_PRIM

#include "Graphs/MatrixGraph.h"
#include "Graphs/ListGraph.h"

class Alg_Prim
{
public:
    void Prim_matrix(MatrixGraph& graph, bool write);
    void Prim_list(ListGraph& graph, bool write);
private:
    int minKey(int key[], bool inMST[], int vertices);
};

#endif ALG_PRIM


