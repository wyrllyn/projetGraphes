/*
 * Node.cpp
 *
 *  Created on: 25 oct. 2013
 *      Author: etudiant
 */

#include "Node.h"

Node::Node(int id) : id(id) {

}

Node::~Node() {

}

void Node::addNeighbor(Node& node) {
	this->neighbors.push_back(node);
}

std::vector<Node> Node::getNeighbors(){
	return neighbors;
}

int Node::getId() {
	return id;
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
