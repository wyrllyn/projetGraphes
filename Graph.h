/*
 * Graph.h
 *
 *  Created on: 25 oct. 2013
 *      Author: etudiant
 */

#ifndef GRAPH_H_
#define GRAPH_H_

#include <map>
#include <string>
#include "Node.h"

#define NODE_INSERT(x) std::pair<int,Node>(x, Node(x))

class Graph {
private:
  std::map<int, Node> nodes;
public:
	Graph(std::string fileUrl);
	virtual ~Graph();
};

#endif /* GRAPH_H_ */
