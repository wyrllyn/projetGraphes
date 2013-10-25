/*
 * Graph.cpp
 *
 *  Created on: 25 oct. 2013
 *      Author: etudiant
 */

#include "Graph.h"

#include <fstream>

Graph::Graph(std::string fileUrl) {
	std::ifstream ifs(fileUrl);
	  for (std::string line : ifs) {
		  if (line.find("e") == 0) { //line starts with 'e'
			  std::stringstream ss(line);//TODO:parse line
		  } else if (line.find_last_of("number of vertices:") != std::string::npos) {
			  std::string::size_type pos = line.find_last_of("number of vertices:");
			  line = line.substr(pos, std::string::npos);
			  int numberOfNodes;
			  std::stringstream(line) >> numberOfNodes;
			  for (int i = 0; i < numberOfNodes; i++) {
				  this->nodes.insert(Node(i));
			  }
		  }
	  }
	  ifs.close();
}

Graph::~Graph() {
	// TODO Auto-generated destructor stub
}

