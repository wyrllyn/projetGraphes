#include "Greedy.h"

Greedy::Greedy(Graph g) : original(g), clique() {

}

void Greedy::findMax(){
	unsigned int biggest = 0;
	unsigned int bSize = 0;

	//1st loop to select the node which has the most neighbors
	std::cout << "Selecting Node with the largest number of neighbors" << std::endl;
	for (unsigned int i = 1; i <= original.getNodes().size(); i++){
		if (original.getNodes().at(i).getNeighbors().size() > bSize){
			biggest = original.getNodes().at(i).getId(); //don't know if it works...
			bSize = original.getNodes().at(i).getNeighbors().size();
		}
	}
	std::cout << "Biggest Node=" << biggest << " (size=" << bSize << ")" << std::endl;

	//biggest = 5;
	//bSize = original.getNodes().at(biggest).getNeighbors().size();
	//std::cout << "Biggest Node=" << biggest << " (size=" << bSize << ")" << std::endl;
	////
	//2nd loop to construct a sort of clique (yeah, sort of... )
	for (unsigned int i = 0; i < bSize ; i++){

		// id of the current neighbor of biggest
		unsigned int current = original.getNodes().at(biggest).getNeighbors().at(i);

		// commonNodes initialization
		Graph commonNodes = Graph();
		commonNodes.addNode(original.getNodes().at(biggest));
		commonNodes.addNode(original.getNodes().at(current));

		// vector of neighbors
		std::vector<unsigned int> tempVector = original.getNodes().at(biggest).getNeighbors();
		Node& currentNode = original.getNodes().at(current);
		//std::cout << "currentNode=" << currentNode.getId() << " (size=" << currentNode.getNeighbors().size() << ")" << std::endl;

		for (unsigned int nodeId : currentNode.getNeighbors()){
			// if currentNode contains nodes in common with biggest => added into commonNodes
			if (nodeId <= original.getNodes().size() && nodeId > 0 // fucking hack
					&& commonNodes.canBeAdded(original.getNodes().at(nodeId))){
				commonNodes.addNode(original.getNodes().at(nodeId));
			}
		}

		//verification only if commonNodes' size is bigger than cliqueSize
		if (commonNodes.getNodes().size() > clique.getNodes().size()){
			clique = Graph(commonNodes);
			std::cout << "New clique of size " << clique.getNodes().size() << std::endl;
		}
	}
	std::cout << "Clique size=" << clique.getNodes().size() << std::endl;
}
