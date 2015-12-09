/** Victor Wu
    CS375 - Ford Fulkerson*/

#include <iostream>
#include <string>
#include <fstream>
#include <cstring>
#include <algorithm>
#include <vector>

struct edge {
	int v1, v2, value;
};

void addEdge(std::vector<edge> &myTree, int v1, int v2, int value) {
	edge tempEdge;
	tempEdge.v1 = v1;
	tempEdge.v2 = v2;
	tempEdge.value = value;
	myTree.push_back(tempEdge);
}

std::vector<edge> generateMST(std::vector<edge> &myTree) {



}

int main (int argc, char* argv[]) {
	if (argc == 2) { if (&& strcmp(argv[1],"--help") == 0) { std::cout << "Usage: ./victor_wu_C++ [input]" << std::endl << "Arguments:\n\tInput Filename with edges" << std::endl; return 0; }	
		       else if (argc == 2 && strcmp(argv[1], "--A") == 0) {
	std::ifstream myFile(argv[3], std::ios_base::in); //< Input File, First Argument
	std::ofstream myFileOutput(argv[4]); //< Output File, Second Argument	
	std::string str;		

		
	std::vector<edge> myTree;

		//Reads the file
		int v1, v2, value;
		while (myFile >> v1 >> v2 >> value) {
			addEdge(myTree, v1, v2, value);
		}
		myTree = generateMST(myTree);
	
	
	myFileOutput.close();
	myFile.close();
	return 0;
	}
	else if (argc == 4 && strcmp(argv[1], "--B") == 0) {


	}
}
	else { std::cerr << "Error, invalid amount of arguments. Refer to README for details on usage, or use command --help" << std::endl; return -1;}
}
