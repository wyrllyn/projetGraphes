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
  std::vector<unsigned int> neighbors;
  unsigned int id;
public:
	Node(unsigned int id);
	virtual ~Node();

	void addNeighbor(unsigned int nodeId);
	unsigned int getId();
	std::vector<unsigned int> getNeighbors();

	bool operator<(const Node& n);
	bool operator==(const Node& n);
	bool operator!=(const Node& n);
};

#endif /* NODE_H_ */
