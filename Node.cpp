/*
 * Node.cpp
 *
 *  Created on: 25 oct. 2013
 *      Author: etudiant
 */

#include "Node.h"

Node::Node(unsigned int id) : id(id) {

}

Node::~Node() {

}

void Node::addNeighbor(unsigned int nodeId) {
	this->neighbors.push_back(nodeId);
}

std::vector<unsigned int>& Node::getNeighbors(){
	return neighbors;
}

unsigned int Node::getId() const {
	return id;
}

bool operator<(const Node& n, const Node& m) {
	return n.getId() < m.getId();
}

bool Node::operator<(const Node& n) {
	return this->id < n.id;
}

bool Node::operator ==(const Node& n) {
	return n.id == id;
}

bool Node::operator!=(const Node& n) {
	return id != n.id;
}

std::ostream& operator<<(std::ostream& out, Node& node) {
	out << "Node: id=" << node.getId() << "; neighbors=";
	for (unsigned int n : node.getNeighbors()) {
		out << " " << n;
	}
	return out;
}
