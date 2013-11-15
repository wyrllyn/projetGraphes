/*
 * Node.cpp
 *
 *  Created on: 25 oct. 2013
 *      Author: etudiant
 */

#include "Node.h"

Node::Node(int id) : id(id) {
	// TODO Auto-generated constructor stub

}

Node::~Node() {
	// TODO Auto-generated destructor stub
}

void Node::addNeighbor(Node node) {
	this->neighbors.push_back(node);
}

bool Node::operator<(const Node& n) {
	return this->id < n.id;
}

std::vector<Node> Node::getNeighbors(){
	return neighbors;
}

int Node::getId() {
	return id;
}
