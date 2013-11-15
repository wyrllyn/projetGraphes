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
		std::cout << "current line:" << line << std::endl;
		if (line.find("e") == 0) { //line starts with 'e'
			parseLine(line);
		} else if (line.find("c") == 0
				&& nodes.size() == 0
				&& line.find("number of vertices") != std::string::npos) {
			std::string::size_type pos = line.find_last_of(":") + 1;
			line = line.substr(pos);
			int numberOfNodes = std::stoi(line); //TODO:number of nodes
			for (int i = 1; i < numberOfNodes; i++) {
				this->nodes.insert(NODE_INSERT(i));
			}
			std::cout << "Created " << numberOfNodes << " nodes" << std::endl;
		}
		//std::cout << "end loop" << std::endl;
	}
	ifs.close();
}

Graph::Graph(){

}

void Graph::addNode(Node n){
	nodes.insert(NODE_INSERT(n.getId()));
}

Graph::~Graph() {

}

void Graph::parseLine(std::string line) {
	std::string temp = line.substr(line.find_first_of(" "), line.find_last_of(" "));
	int origin = std::stoi(temp);

	temp = line.substr(line.find_last_of(" "));
	int target = stoi(temp);

	nodes.at(origin).addNeighbor(nodes.at(target));
}

bool Graph::isClique(){
	bool ok = true;
	for (int i = 0; i < nodes.size(); i++){
		std::vector<Node> temp = nodes.at(i).getNeighbors();
		for (int j = 0; j < nodes.size(); j++){
			if (nodes.at(i) != nodes.at(j)){
				// if a graph's node isn't found into temp then it isn't a clique
				if (std::find(temp.begin(), temp.end(), nodes.at(i) ) == temp.end()){
					ok = false;
					break;
				}
			}
		}
	}
	return ok;
}

std::map<int, Node> Graph::getNodes()
{
	return nodes;	
}

