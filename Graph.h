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
protected:
  void parseLine(std::string line);
public:
	Graph(std::string fileUrl);
	Graph();
	//sara : pour avoir accès aux nodes
	std::map<int, Node> getNodes();
	void addNode(Node n);
	bool isClique();
	virtual ~Graph();
};

#endif /* GRAPH_H_ */
