#include "Node.h"
#include "Graph.h"
#include "Greedy.h"

#define DEFAULT_FILE_NAME "res/c FILE:  C125.9.clq"

int main() {
	Graph g("res/c250.9.clq");
	std::cout << "Creating Greedy object ..." << std::endl;
	Greedy greedo(g);
	std::cout << "Running findMax method ..." << std::endl;
	greedo.findMax();
}
