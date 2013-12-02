#include "Node.h"
#include "Graph.h"
#include "Greedy.h"
#include <fstream>

#define DEFAULT_FILE_NAME "res/c125.9.clq"

//#define DEBUG //TODO:make that a proper build configuration

int main(int argc, const char* argv[]) {
	std::string fileName = DEFAULT_FILE_NAME;
	if (argc > 1) {
		fileName = argv[1];
	}
#ifdef DEBUG
	fileName = "res/C2000.9.clq";
#endif
	Graph g(fileName);
	std::cout << "Creating Greedy object ..." << std::endl;
	Greedy greedo(g);
	std::cout << "Running findMax method ..." << std::endl;
	Graph result = greedo.findMax();

	std::ofstream ofs(fileName.append(".result"));
	ofs << result;
	std::cout << "Results printed in " << fileName;
	ofs.close();
}
