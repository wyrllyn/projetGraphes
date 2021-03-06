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
#include <assert.h>

Graph::Graph(const std::string fileUrl) {
	std::ifstream ifs(fileUrl);
	std::cout << "Opening file: " << fileUrl << std::endl;
	setFileType(fileUrl);
	std::cout << "File type: " << fileType << std::endl;
	unsigned int numberOfNodes = 0;

	while (ifs.is_open() && !ifs.eof()) {
		std::string line;
		getline(ifs, line);
		//std::cout << "current line:" << line << std::endl;
		if (line.find("e") == 0) { //line starts with 'e'
			parseLine(line);
		} else if ((line.find("c") == 0 || line.find("p") == 0)
				&& nodeMap.size() == 0
				&& (numberOfNodes = extractVertices(line)) > 0) {

			for (unsigned int i = 1; i <= numberOfNodes; i++) {
				this->nodeMap.insert(NODE_INSERT_NEW(i));
			}
			std::cout << "Created " << numberOfNodes << " nodes" << std::endl;
		}
	}

	//prepare nodeSet + nodeMatrix
	nodeMatrix = new unsigned int*[numberOfNodes + 1];
	sizeOfN = new unsigned int [numberOfNodes + 1];
	for (unsigned int i = 1; i <= numberOfNodes; i++) {
		nodeSet.insert(nodeMap[i]);
		std::vector<unsigned int, std::allocator<unsigned int> >&
		neighbors = nodeMap[i]->getNeighbors();
		nodeMatrix[i] = new unsigned int[ neighbors.size() ];
		sizeOfN[i] = neighbors.size();
		for (unsigned int j = 0; j < neighbors.size(); j++) {
			nodeMatrix[i][j] = neighbors[j];
		}
	}

	assert(nodeMap.size() > 0);
	std::cout << "Graph creation was successful" << std::endl;
	ifs.close();
}

unsigned int Graph::extractVertices(std::string& line) {
	switch (fileType) {
	case C:
		if (line.find("number of vertices") != std::string::npos) {
			std::string::size_type pos = line.find_last_of(":") + 1;
			line = line.substr(pos);
			return std::stoul(line);
		} else {
			return 0;
		}
	case BROCK:
	case MANN:
		//Graph Size: [number]
		if (line.find("Graph Size") != std::string::npos) {
			std::string::size_type pos = line.find_first_of(":") + 1;
			std::string::size_type pos_end = line.find_first_of(",");
			line = line.substr(pos, pos_end);
			return std::stoul(line);
		} else {
			return 0;
		}
	case DSJC:
	case HAMMING:
		//p edge [number]
		if (line.find("edge") != std::string::npos) {
			std::string::size_type pos = line.find_last_of("edge") + 1;
			std::string::size_type pos_end = line.find_last_of(" ") - 1;
			line = line.substr(pos, pos_end);
			return std::stoul(line);
		} else {
			return 0;
		}
	case GEN:
		//c [number] vertices
		if (line.find("vertices") != std::string::npos) {
			std::string::size_type pos_end = line.find_first_of("vertices") - 1;
			line = line.substr(2, pos_end);
			return std::stoul(line);
		} else {
			return 0;
		}
	default:
		return 0;
	}
}

void Graph::setFileType(std::string fileUrl) {
	std::string::size_type slashPos = fileUrl.find_last_of("/") + 1;
	fileUrl = fileUrl.substr(slashPos, std::string::npos);
	if (fileUrl.find_first_of("c") == 0 || fileUrl.find_first_of("C") == 0) {
		fileType = C;
	} else if(fileUrl.find_first_of("brock") == 0) {
		fileType = BROCK;
	} else if(fileUrl.find_first_of("DSJC") == 0) {
		fileType = DSJC;
	} else if (fileUrl.find_first_of("gen") == 0) {
		fileType = GEN;
	} else if(fileUrl.find_first_of("hamming") == 0) {
		fileType = HAMMING;
	} else if(fileUrl.find_first_of("MANN") == 0) {
		fileType = MANN;
	} else {
		fileType = C; // default
	}
}

Graph::Graph() : nodeMatrix(NULL), fileType(C) {
	nodeToRemove = 0;
	sizeOfN = NULL;
}

Graph::Graph(const Graph& graph) :
		nodeMap(graph.nodeMap),
		nodeSet(graph.nodeSet),
		nodeMatrix(graph.nodeMatrix),
		sizeOfN(graph.sizeOfN),
		nodeToRemove(graph.nodeToRemove),
		fileType(graph.fileType) {

}

void Graph::remove(unsigned int n){
	nodeMap.erase(n);
}

Graph::~Graph() {

}

/**
 * Creates an empty Graph EXCEPT for its nodeMatrix and sizeOfN array,
 * which are initialized based on the provided nodeMap.
 */
Graph::Graph(std::map<unsigned int, Node*> nodeMap) :
			nodeToRemove(0),
			fileType(C) {
	nodeMatrix = new unsigned int[nodeMap.size() + 1][];
	sizeOfN = new unsigned int[nodeMap.size() + 1];
	// make sure nodeMatrix and sizeOfN contain all the info we need
	for (unsigned int i = 0; i < nodeMap.size(); i++) {
		Node* n = nodeMap[i];
		unsigned int size = n->getNeighbors().size();
		sizeOfN[i] = size;
		nodeMatrix[i] = new unsigned int[size];
		for (int j = 0; j < size; j++) {
			nodeMatrix[i][j] = n->getNeighbors()[j];
		}
	}
}

void Graph::addNode(Node* n){
	nodeMap.insert(NODE_INSERT(n));
	nodeMatrix[n->getId()] = new unsigned int[n->getNeighbors().size()];
	sizeOfN[n->getId()] = n->getNeighbors().size();
}



void Graph::parseLine(std::string line) {
	std::string temp = line.substr(line.find_first_of(" "), line.find_last_of(" "));
	unsigned int origin = std::stoul(temp);

	temp = line.substr(line.find_last_of(" "));
	unsigned int target = std::stoul(temp);

	nodeMap.at(origin)->addNeighbor(nodeMap.at(target)->getId());
	nodeMap.at(target)->addNeighbor(nodeMap.at(origin)->getId());
}

bool Graph::isClique(){
	bool ok = true;
	for (unsigned int i = 0; i < nodeMap.size(); i++){
		std::vector<unsigned int> temp = nodeMap.at(i)->getNeighbors();
		for (unsigned int j = 0; j < nodeMap.size(); j++){
			if (nodeMap.at(i) != nodeMap.at(j)){
				// if a graph's node isn't found into temp then it isn't a clique
				if (std::find(temp.begin(), temp.end(), nodeMap.at(i)->getId() ) == temp.end()){
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
	for (std::pair<unsigned int, Node*> node_pair : nodeMap){
		Node* node = node_pair.second;
		//std::cout << "testing for Node " << node.getId() << std::endl;
		if(!found(node, n)){
			//std::cout << "can't be added" << std::endl;
			return false;
		}
	}
	return true;
}

bool Graph::canBeAddedOther(Node* n){
	unsigned int cmp = 0;
	unsigned int temp = 0;
	for (std::pair<unsigned int, Node*> node_pair : nodeMap){
		Node* node = node_pair.second;
		if(!found(node, n)){
			cmp++;
			temp = node_pair.first;
		}
		if(cmp >= 2){
			return false;
		}
	}
	nodeToRemove = temp;
	return true;
}

bool Graph::canBeAddedMatrix(unsigned int n){
	unsigned int cmp = 0;
	unsigned int temp = 0;
	std::cout << "pouet" << std::endl;
	for (unsigned int node = 1; node <= nodeMap.size(); node++){
		std::cout << "##" << node << std::endl;
		if(!found(node, n)){
			std::cout << "not found" << std::endl;
			cmp++;
			temp = node;
		}
		if(cmp >= 2){
			return false;
		}
	}
	nodeToRemove = temp;
	return true;
}

std::map<unsigned int, Node*>& Graph::getNodeMap()
{
	return nodeMap;
}

std::set<Node*, nodeComparator>& Graph::getNodeSet() {
	return nodeSet;
}

unsigned int** Graph::getNodeMatrix() {
	return nodeMatrix;
}

bool Graph::found(Node* node, Node* toFind) {
	for (unsigned int currentId : node->getNeighbors()) {
		if (currentId == toFind->getId()) {
			return true;
		}
	}
	return false;
}

bool Graph::found(unsigned int node, unsigned int toFind) {
	std::cout << "node=" << node << "; toFind=" << toFind << std::endl;
	//std::cout << sizeOfN[];
	for (unsigned int i = 0; i < sizeOfN[node]; i++) {
		std::cout << "node=" << node << "; i=" << i << "; toFind=" << toFind << "; NM[node][i]=" << nodeMatrix[node][i] << std::endl;
		if (nodeMatrix[node][i] == toFind) {
			return true;
		}
	}
	return false;
}

void Graph::clearNodeToRemove(){
	nodeToRemove = 0;
}

int Graph::getNodeToRemove(){
	return nodeToRemove;
}

std::ostream& operator<<(std::ostream& out, Graph& graph) {
	out << "Graph:" << std::endl;
	std::map<unsigned int, Node*>& nodes = graph.getNodeMap();
	out << "\tNumber of nodes: " << nodes.size() << std::endl;
	for (std::pair<unsigned int, Node*> node_pair : nodes) {
		Node* node = node_pair.second;
		out << "\t" << *node << std::endl;
	}
	return out;
}

std::ostream& operator<<(std::ostream& out, FileType type) {
	switch (type) {
	case C:
		out << "C";
		break;
	case BROCK:
		out << "BROCK";
		break;
	case DSJC:
		out << "DSJC";
		break;
	case GEN:
		out << "GEN";
		break;
	case HAMMING:
		out << "HAMMING";
		break;
	case MANN:
		out << "MANN";
		break;
	}
	return out;
}


unsigned int Graph::getSizeOfN(unsigned int n){
	return sizeOfN[n];
}
