#include "Greedy.h"

Greedy::Greedy(Graph g) : original(g), clique() {

}

//TODO : Other method with matrix ! & tab into graph (size of neighborhood ) sizeOfN

 Graph Greedy::greedyMatrix(){

 	unsigned int biggest = 0;
	unsigned int bSize = 0;
	for (unsigned int i = 1; i < sizeOfN.size(); i++){
		if(sizeOfN[i] > bSize){
			biggest = i;
			bSize = sizeOfN[i]
		}
	}
	std::cout << "Biggest Node=" << biggest << " (size=" << bSize << ")" << std::endl;

	for (unsigned int j = 0; j < bSize ; j++){
		// id of the current neighbor of biggest
		unsigned int current = original.getNodeMatrix()[biggest][j];

		// commonNodes initialization
		Graph commonNodes = Graph();
		commonNodes.addNode(original.getNodeMap().at(biggest));
		commonNodes.addNode(original.getNodeMap().at(current));

		// vector of neighbors
		std::vector<unsigned int> tempVector = original.getNodeMap().at(biggest)->getNeighbors();
		Node* currentNode = original.getNodeMap().at(current);
		//std::cout << "currentNode=" << currentNode.getId() << " (size=" << currentNode.getNeighbors().size() << ")" << std::endl;


		for (unsigned int k = 1; k < sizeOfN[current] ; k++ ){
			unsigned int nodeId =  original.getNodeMatrix[current][k];
			if (nodeId <= original.getNodeMap().size() && nodeId > 0
					&& commonNodes.canBeAddedOther(original.getNodeMap().at(nodeId))){
				//if nodeId is in the neighborhood of every node in the clique
				if (commonNodes.getNodeToRemove() == 0){
					commonNodes.addNode(original.getNodeMap().at(nodeId));
				}
				// if nodeId is in the neighborhood of every node in the clique except nodeToRemove
				else{
					unsigned int cmpNodeId = inCommon(original.getNodeMap().at(nodeId), original.getNodeMap().at(biggest));
					unsigned int cmpToRemove = inCommon(original.getNodeMap().at(commonNodes.getNodeToRemove()),
												original.getNodeMap().at(biggest));
					// if NodeId has more nodes in common with biggest than toRemove
					if(cmpNodeId > cmpToRemove){
						commonNodes.remove(commonNodes.getNodeToRemove());
						commonNodes.clearNodeToRemove();
						commonNodes.addNode(original.getNodeMap().at(nodeId));
					}
				}
			}
		}

		//verification only if commonNodes' size is bigger than cliqueSize
		if (commonNodes.getNodeMap().size() > clique.getNodeMap().size()){
			clique = Graph(commonNodes);
			std::cout << "New clique of size " << clique.getNodeMap().size() << std::endl;
		}
	}
	std::cout << "Clique size=" << clique.getNodeMap().size() << std::endl;
	return clique;
}


Graph Greedy::findMax(){
	unsigned int biggest = 0;
	unsigned int bSize = 0;

	//1st loop to select the node which has the most neighbors
	std::cout << "Selecting Node with the largest number of neighbors" << std::endl;
	for (unsigned int i = 1; i <= original.getNodeMap().size(); i++){
		if (original.getNodeMap().at(i)->getNeighbors().size() > bSize){
			biggest = original.getNodeMap().at(i)->getId(); //don't know if it works...
			bSize = original.getNodeMap().at(i)->getNeighbors().size();
		}
	}
	std::cout << "Biggest Node=" << biggest << " (size=" << bSize << ")" << std::endl;

	//2nd loop to construct a sort of clique (yeah, sort of... )
	for (unsigned int i = 0; i < bSize ; i++){

		// id of the current neighbor of biggest
		unsigned int current = original.getNodeMap().at(biggest)->getNeighbors().at(i);

		// commonNodes initialization
		Graph commonNodes = Graph();
		commonNodes.addNode(original.getNodeMap().at(biggest));
		commonNodes.addNode(original.getNodeMap().at(current));

		// vector of neighbors
		std::vector<unsigned int> tempVector = original.getNodeMap().at(biggest)->getNeighbors();
		Node* currentNode = original.getNodeMap().at(current);
		//std::cout << "currentNode=" << currentNode.getId() << " (size=" << currentNode.getNeighbors().size() << ")" << std::endl;

		for (unsigned int nodeId : currentNode->getNeighbors()){
			// if currentNode contains nodes in common with biggest => added into commonNodes
			if (nodeId <= original.getNodeMap().size() && nodeId > 0 // fucking hack
					&& commonNodes.canBeAdded(original.getNodeMap().at(nodeId))){
				commonNodes.addNode(original.getNodeMap().at(nodeId));
			}
		}

		//verification only if commonNodes' size is bigger than cliqueSize
		if (commonNodes.getNodeMap().size() > clique.getNodeMap().size()){
			clique = Graph(commonNodes);
			std::cout << "New clique of size " << clique.getNodeMap().size() << std::endl;
		}
	}
	std::cout << "Clique size=" << clique.getNodeMap().size() << std::endl;
	return clique;
}

Graph Greedy::findMaxOther(){
	unsigned int biggest = 0;
	unsigned int bSize = 0;

	//1st loop to select the node which has the most neighbors
	std::cout << "Selecting Node with the largest number of neighbors" << std::endl;
	for (unsigned int i = 1; i <= original.getNodeMap().size(); i++){
		if (original.getNodeMap().at(i)->getNeighbors().size() > bSize){
			biggest = original.getNodeMap().at(i)->getId(); //don't know if it works...
			bSize = original.getNodeMap().at(i)->getNeighbors().size();
		}
	}
	std::cout << "Biggest Node=" << biggest << " (size=" << bSize << ")" << std::endl;


	//2nd loop to construct a sort of clique (yeah, sort of... )
	for (unsigned int i = 0; i < bSize ; i++){

		// id of the current neighbor of biggest
		unsigned int current = original.getNodeMap().at(biggest)->getNeighbors().at(i);

		// commonNodes initialization
		Graph commonNodes = Graph();
		commonNodes.addNode(original.getNodeMap().at(biggest));
		commonNodes.addNode(original.getNodeMap().at(current));

		// vector of neighbors
		std::vector<unsigned int> tempVector = original.getNodeMap().at(biggest)->getNeighbors();
		Node* currentNode = original.getNodeMap().at(current);
		//std::cout << "currentNode=" << currentNode.getId() << " (size=" << currentNode.getNeighbors().size() << ")" << std::endl;

		for (unsigned int nodeId : currentNode->getNeighbors()){
			// if currentNode contains nodes in common with biggest => added into commonNodes
			if (nodeId <= original.getNodeMap().size() && nodeId > 0 // fucking hack
					&& commonNodes.canBeAddedOther(original.getNodeMap().at(nodeId))){
				//if nodeId is in the neighborhood of every node in the clique
				if (commonNodes.getNodeToRemove() == 0){
					commonNodes.addNode(original.getNodeMap().at(nodeId));
				}
				// if nodeId is in the neighborhood of every node in the clique except nodeToRemove
				else{
					unsigned int cmpNodeId = inCommon(original.getNodeMap().at(nodeId), original.getNodeMap().at(biggest));
					unsigned int cmpToRemove = inCommon(original.getNodeMap().at(commonNodes.getNodeToRemove()),
												original.getNodeMap().at(biggest));
					// if NodeId has more nodes in common with biggest than toRemove
					if(cmpNodeId > cmpToRemove){
						commonNodes.remove(commonNodes.getNodeToRemove());
						commonNodes.clearNodeToRemove();
						commonNodes.addNode(original.getNodeMap().at(nodeId));
					}
				}
			}
		}

		//verification only if commonNodes' size is bigger than cliqueSize
		if (commonNodes.getNodeMap().size() > clique.getNodeMap().size()){
			clique = Graph(commonNodes);
			std::cout << "New clique of size " << clique.getNodeMap().size() << std::endl;
		}
	}
	std::cout << "Clique size=" << clique.getNodeMap().size() << std::endl;
	return clique;
}

bool Greedy::find(unsigned int toFind, Node* node){
	for (unsigned int currentId : node->getNeighbors()) {
		if (currentId == toFind) {
			return true;
		}
	}
	return false;
}

unsigned int Greedy::inCommon(Node* test, Node* biggest){
	unsigned int cmp = 0;
	for(unsigned int current : test->getNeighbors()){
		if(find(current, biggest)){
			cmp++;
		}
	}
	return cmp;
}


