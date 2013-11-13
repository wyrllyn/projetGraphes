#include "Greedy.h"

Greedy::Greedy(Graph g){
	//TODO init
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
	for (unsigned i = 0; i < bSize ; i++){
		int current = original.getNodes()[biggest].getNeighbors().at(i);
		int tempSize = 2;
		//TODO init clique with values biggest and current
		std::vector<Node> tempVector = original.getNodes()[biggest].getNeighbors();
		for (int j = 0; j < original.getNodes()[biggest].getNeighbors().size(); j++){
			// if currentNode contains nodes in commun with biggest
			if (std::find(tempVector.begin(), tempVector.end(), original.getNodes()[biggest].getNeighbors().at(j))){
				tempSize++;
			}
		}
		if (tempSize > cliqueSize){
			//TODO : construction of a clique
		}
	}



}
