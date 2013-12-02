/*
 * Graph.cpp
 *
 *  Created on: 25 oct. 2013
 *      Author: etudiant
 */

#include "Graph.h"

#include <fstream>
#include <iostream>
#include <algorithm>

Graph::Graph(const std::string fileUrl) {
	std::ifstream ifs(fileUrl);
	std::cout << "Opening file: " << fileUrl << std::endl;
	while (ifs.is_open() && !ifs.eof()) {
		std::string line;
		getline(ifs, line);
		//std::cout << "current line:" << line << std::endl;
		if (line.find("e") == 0) { //line starts with 'e'
			parseLine(line);
		} else if (line.find("c") == 0
				&& nodes.size() == 0
				&& line.find("number of vertices") != std::string::npos) {
			std::string::size_type pos = line.find_last_of(":") + 1;
			line = line.substr(pos);

			unsigned int numberOfNodes = std::stoul(line);
			for (unsigned int i = 1; i <= numberOfNodes; i++) {
				this->nodes.insert(NODE_INSERT_NEW(i));
			}
			std::cout << "Created " << numberOfNodes << " nodes" << std::endl;

			for (unsigned int i; i <= numberOfNodes; i++) {
				nodeSet.insert(nodes[i]);
			}
		}
	}
	std::cout << "Graph creation was successful" << std::endl;
	ifs.close();
}

Graph::Graph(){

}

Graph::Graph(const Graph& graph) : nodes(graph.nodes) {

}

Graph::~Graph() {

}

void Graph::addNode(Node* n){
	nodes.insert(NODE_INSERT(n));
}


void Graph::parseLine(std::string line) {
	std::string temp = line.substr(line.find_first_of(" "), line.find_last_of(" "));
	unsigned int origin = std::stoul(temp);

	temp = line.substr(line.find_last_of(" "));
	unsigned int target = std::stoul(temp);

	nodes.at(origin)->addNeighbor(nodes.at(target)->getId());
	nodes.at(target)->addNeighbor(nodes.at(origin)->getId());
}

bool Graph::isClique(){
	bool ok = true;
	for (unsigned int i = 0; i < nodes.size(); i++){
		std::vector<unsigned int> temp = nodes.at(i)->getNeighbors();
		for (unsigned int j = 0; j < nodes.size(); j++){
			if (nodes.at(i) != nodes.at(j)){
				// if a graph's node isn't found into temp then it isn't a clique
				if (std::find(temp.begin(), temp.end(), nodes.at(i)->getId() ) == temp.end()){
					ok = false;
					break;
				}
			}
		}
	}
	return ok;
}

bool Graph::canBeAdded(Node* n){
	//std::cout << "can Node " << n.getId() << " be added?" << std::endl;
	for (std::pair<unsigned int, Node*> node_pair : nodes){
		Node* node = node_pair.second;
		//std::cout << "testing for Node " << node.getId() << std::endl;
		if(!found(node, n)){
			//std::cout << "can't be added" << std::endl;
			return false;
		}
	}
	return true;
}

std::map<unsigned int, Node*>& Graph::getNodes()
{
	return nodes;
}

bool Graph::found(Node* node, Node* toFind) {
	for (unsigned int currentId : node->getNeighbors()) {
		if (currentId == toFind->getId()) {
			return true;
		}
	}
	return false;
}

std::ostream& operator<<(std::ostream& out, Graph& graph) {
	out << "Graph:" << std::endl;
	std::map<unsigned int, Node*>& nodes = graph.getNodes();
	out << "\tNumber of nodes: " << nodes.size() << std::endl;
	for (std::pair<unsigned int, Node*> node_pair : nodes) {
		Node* node = node_pair.second;
		out << "\t" << node << std::endl;
	}
	return out;
}
