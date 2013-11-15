#ifndef GREEDY_H
#define GREEDY_H

#include "Graph.h"

class Greedy {

private:
	Graph original;
	Graph clique;
public:
	Greedy(Graph g);
	void findMax();
};



#endif
