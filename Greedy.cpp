#include "Greedy.h"

Greedy::Greedy(Graph g) :
	original(g),
	clique()
{

}

void Greedy::findMax(){
	unsigned int biggest = 0;
	unsigned int bSize = 0;

	//1st loop to select the node which has the most neighbors

	for (unsigned int i = 0; i < original.getNodes().size(); i++){
		if (original.getNodes().at(i).getNeighbors().size() > bSize){
			biggest = original.getNodes().at(i).getId(); //don't know if it works...
			bSize = original.getNodes().at(i).getNeighbors().size();
		}
	}

	//2nd loop to construct a sort of clique (yeah, sort of... )
	for (unsigned int i = 0; i < bSize ; i++){

		// id of the current neighbor of biggest
		unsigned int current = original.getNodes().at(biggest).getNeighbors().at(i).getId();

		// commonNodes initialization
		Graph commonNodes = new Graph();
		commonNodes.addNode(original.getNodes().at(biggest));
		commonNodes.addNode(original.getNodes().at(current));
		// vector of neighbors
		std::vector<Node> tempVector = original.getNodes().at(biggest).getNeighbors();

		for (unsigned int j = 0; j < original.getNodes().at(current).getNeighbors().size(); j++){
			// if currentNode contains nodes in common with biggest => added into commonNodes
			if (FIND(tempVector, original, current, j)){
				commonNodes.addNode(original.getNodes().at(current).getNeighbors().at(j));
			}
		}

		//verification only if commonNodes' size is bigger than cliqueSize
		if (commonNodes.getNodes().size() > clique.getNodes().size()){
			if (commonNodes.isClique()){
				clique = new Graph(commonNodes);
			}
			else{
				//TODO : verif si on peut créer une clique à partir de commonNodes
			}
		}
	}



}
