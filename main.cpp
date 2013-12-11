#include "Node.h"
#include "Graph.h"
#include "Greedy.h"
#include <fstream>

#define DEFAULT_FILE_NAME "res/brock200_2.clq" // attention à la casse

int main(int argc, const char* argv[]) {
	std::string fileName = DEFAULT_FILE_NAME;
	if (argc > 1) {
		fileName = argv[1];
	}

	//TODO list of files
	//TODO adapt parsing
	//TODO use matrix whenever possible
	//TODO output results in result/algo folder

	Graph g(fileName);
	std::cout << "Creating Greedy object ..." << std::endl;
	Greedy greedo(g);
	std::cout << "Running findMax method ..." << std::endl;
	Graph result = greedo.findMaxOther();

	//fileName = std::string("results/").append(fileName);
	std::ofstream ofs(fileName.append(".result"));
	ofs << result;
	std::cout << "Results printed in " << fileName;
	ofs.close();
}
