/*
 * Graph.cpp
 *
 *  Created on: 25 oct. 2013
 *      Author: etudiant
 */

#include "Graph.h"

#include <fstream>
#include <iostream>

Graph::Graph(const std::string fileUrl) {
	std::ifstream ifs(fileUrl);
	std::cout << "open!" << fileUrl << std::endl;
	while (ifs.is_open() && !ifs.eof()) {
		std::string line;
		getline(ifs, line);
		std::cout << "current line:" << line << std::endl;
		if (line.find("e") == 0) { //line starts with 'e'
			parseLine(line);
		} else if (line.find("c") == 0 &&
				line.find("number of vertices") != std::string::npos) {
			std::string::size_type pos = line.find_last_of(":");
			line = line.substr(pos);
			int numberOfNodes(125);
			//int numberOfNodes = std::stoi(line); //TODO:number of nodes
			for (int i = 0; i < numberOfNodes; i++) {
				this->nodes.insert(NODE_INSERT(i));
			}
		}
		//std::cout << "end loop" << std::endl;
	}
	ifs.close();
}

Graph::~Graph() {

}

void Graph::parseLine(std::string line) {
	std::string temp = line.substr(line.find_first_of(" "), line.find_last_of(" "));
	int origin = std::stoi(temp);
	//int target = stoi(temp);
}

