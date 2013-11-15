#include "Greedy.h"

Greedy::Greedy(Graph g){
	clique = new Graph();
	//TODO init original
}

void Greedy::findMax(){
	int biggest = 0;
	int bSize = 0;

	//1st loop to select the node which has the most neighbors

	for (int i = 0; i < original.getNodes().size(); i++){
		if (original.getNodes()[i].getNeighbors().size() > bSize){
			biggest = original.getNodes()[i]; //don't know if it works...
			bSize = original.getNodes()[i].getNeighbors().size();
		}
	}

	int cliqueSize = 0;
	//2nd loop to construct a sort of clique (yeah, sort of... )
	for (int i = 0; i < bSize ; i++){
		// id of the current neighbor of biggest
		int current = original.getNodes()[biggest].getNeighbors().at(i);
		int tempSize = 2;
		// vector of neighbors
		std::vector<Node> tempVector = original.getNodes()[biggest].getNeighbors();

		for (int j = 0; j < original.getNodes()[current].getNeighbors().size(); j++){
			// if currentNode contains nodes in common with biggest
			if (std::find(tempVector.begin(), tempVector.end(), original.getNodes()[current].getNeighbors().at(j))){
				tempSize++;
			}
		}
		if (tempSize > cliqueSize){
			clique = new Graph();
			clique.addNode(original.getNodes()[biggest]);
			clique.addNode(original.getNodes()[current]);
			for (int j = 0; j < original.getNodes()[current].getNeighbors().size(); j++){
					// if currentNode contains nodes in common with biggest
					if (std::find(tempVector.begin(), tempVector.end(), original.getNodes()[current].getNeighbors().at(j))){
						clique.addNode(original.getNodes()[current].getNeighbors().at(j));
					}
				}
		}
	}



}
