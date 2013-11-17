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

#define NODE_INSERT_NEW(x) std::pair<unsigned int, Node>(x, Node(x))
#define NODE_INSERT(node) std::pair<unsigned int, Node>(node.getId(), node)

class Graph {
private:
  std::map<unsigned int, Node> nodes;
protected:
  void parseLine(std::string line);
  bool found(Node& node, Node& toFind);
public:
	Graph(std::string fileUrl);
	Graph();
	Graph(const Graph& graph);
	//sara : pour avoir accès aux nodes
	std::map<unsigned int, Node> getNodes();
	void addNode(Node& n);
	bool isClique();
	bool canBeAdded(Node& n);
	virtual ~Graph();
};

#endif /* GRAPH_H_ */
