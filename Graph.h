/*
 * Graph.h
 *
 *  Created on: 25 oct. 2013
 *      Author: etudiant
 */

#ifndef GRAPH_H_
#define GRAPH_H_

#include <set>
#include <string>
#include "Node.h"

class Graph {
private:
  std::set<Node> nodes;
public:
	Graph(std::string fileUrl);
	virtual ~Graph();
};

#endif /* GRAPH_H_ */
