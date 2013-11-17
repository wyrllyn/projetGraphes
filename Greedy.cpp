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

		for (unsigned int j = 0; j < currentNode.getNeighbors().size(); j++){
			// if currentNode contains nodes in common with biggest => added into commonNodes
			int nodeId = currentNode.getNeighbors().at(j);
			if (commonNodes.canBeAdded(original.getNodes().at(nodeId))){
				commonNodes.addNode(original.getNodes().at(nodeId));
			}
		}

		//verification only if commonNodes' size is bigger than cliqueSize
		if (commonNodes.getNodes().size() > clique.getNodes().size()){
			if (commonNodes.isClique()){//possibilité de le virer
				clique = Graph(commonNodes);
			}
		}
	}



}
