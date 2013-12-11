#include "Node.h"
#include "Graph.h"
#include "Greedy.h"
#include <fstream>

#define DEFAULT_FILE_NAME "res/gen200_p0.9_44.clq" // attention à la casse

int main(int argc, const char* argv[]) {
	std::string fileName = DEFAULT_FILE_NAME;
	if (argc > 1) {
		fileName = argv[1];
	}

	//TODO use matrix whenever possible
	//TODO check memory usage & delete old items
	//TODO list of files

	Graph g(fileName);
	std::cout << "Creating Greedy object ..." << std::endl;
	Greedy greedo(g);
	std::cout << "Running findMax method ..." << std::endl;
	Graph result = greedo.findMaxOther();

	std::string::size_type slashPos = fileName.find_last_of("/");
	std::string temp = fileName.substr(0, slashPos + 1);
	fileName = fileName.substr(slashPos + 1);
	fileName = temp.append(std::string("results/").append(fileName));
	std::ofstream ofs(fileName.append(".result"));
	ofs << result;
	std::cout << "Results printed in " << fileName;
	ofs.close();
}
