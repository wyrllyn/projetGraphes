#ifndef GREEDY_H
#define GREEDY_H

#include "Graph.h"
#include <algorithm>
#include <iostream>


#define FIND(tempVector, original, current, index) std::find(tempVector.begin(), tempVector.end(), original.getNodes().at(current).getNeighbors().at(index)) != tempVector.end()

class Greedy {

private:
	Graph original;
	Graph clique;
public:
	Greedy(Graph g);
	void findMax();
};



#endif
