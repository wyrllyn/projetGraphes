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
	while (!ifs.eof()) {
		std::string line;
		getline(ifs, line);
		if (line.find("e") == 0) { //line starts with 'e'
			//std::stringstream ss(line);//TODO:parse line
		} else if (line.find_last_of("number of vertices") != std::string::npos) {
			std::string::size_type pos = line.find_last_of(":");
			line = line.substr(pos, std::string::npos);
			int numberOfNodes(0);
			//int numberOfNodes = std::stoi(line); //TODO:number of nodes
			for (int i = 0; i < numberOfNodes; i++) {
				this->nodes.insert(NODE_INSERT(i));
			}
		}
	  }
	  ifs.close();
}

Graph::~Graph() {

}

