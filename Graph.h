/*
 * Graph.h
 *
 *  Created on: 25 oct. 2013
 *      Author: etudiant
 */

#ifndef GRAPH_H_
#define GRAPH_H_

#include <map>
#include <set>
#include <string>
#include <ostream>
#include "Node.h"

#define NODE_INSERT_NEW(x) std::pair<unsigned int, Node*>(x, new Node(x))
#define NODE_INSERT(node) std::pair<unsigned int, Node*>(node->getId(), node)

class Graph {
private:
  std::map<unsigned int, Node*> nodes;
  std::set<Node*> nodeSet;
protected:
  void parseLine(std::string line);
  bool found(Node* node, Node* toFind);
public:
	Graph(std::string fileUrl);
	Graph();
	Graph(const Graph& graph);
	//sara : pour avoir accès aux nodes
	std::map<unsigned int, Node*>& getNodes();
	void addNode(Node* n);
	bool isClique();
	bool canBeAdded(Node* n);
	virtual ~Graph();
};

std::ostream& operator<<(std::ostream& out, Graph& graph);

#endif /* GRAPH_H_ */
