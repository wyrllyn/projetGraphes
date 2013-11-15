/*
 * Node.h
 *
 *  Created on: 25 oct. 2013
 *      Author: etudiant
 */

#ifndef NODE_H_
#define NODE_H_

#include <vector>

class Node {
private:
  std::vector<Node> neighbors;
  int id;
public:
	Node(int id);
	virtual ~Node();

	void addNeighbor(Node node);
	int getId();
	bool operator<(const Node& n);
	std::vector<Node> getNeighbors();
};

#endif /* NODE_H_ */
