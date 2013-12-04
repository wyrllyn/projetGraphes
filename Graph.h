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


// TODO: void remove (node)
// TODO: method : can be added2 => in greedy, if NodeToRemove == 0 => just add, else remove NodeToRemove, set NodeToRemove to 0 add

#define NODE_INSERT_NEW(x) std::pair<unsigned int, Node*>(x, new Node(x))
#define NODE_INSERT(node) std::pair<unsigned int, Node*>(node->getId(), node)

class Graph {
private:
  std::map<unsigned int, Node*> nodeMap;
  std::set<Node*, nodeComparator> nodeSet;
  unsigned int** nodeMatrix;
  int nodeToRemove;
protected:
  void parseLine(std::string line);
  bool found(Node* node, Node* toFind);
public:
	Graph(std::string fileUrl);
	Graph();
	Graph(const Graph& graph);
	std::map<unsigned int, Node*>& getNodeMap();
	std::set<Node*, nodeComparator>& getNodeSet();
	void clearNodeToRemove();
	int getNodeToRemove();
	unsigned int** getNodeMatrix();
	void addNode(Node* n);
	bool isClique();
	void remove(unsigned int n);
	bool canBeAdded(Node* n);
	bool canBeAddedOther(Node* n);
	virtual ~Graph();
};

std::ostream& operator<<(std::ostream& out, Graph& graph);

#endif /* GRAPH_H_ */
