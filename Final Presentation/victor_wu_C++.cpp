/** Victor Wu
  CS375 - Ford Fulkerson*/

#include <iostream>
#include <string>
#include <fstream>
#include <cstring>
#include <algorithm>
#include <vector>
#include <queue>
#include <list>

struct edge {
	int v1, v2, value;

	edge& operator =(edge e) {
		v1 = e.v1;
		v2 = e.v2;
		value = e.value;
		return *this;
	}
};


//! \param The tree for the edge to be appended to
//! \param Source vertex edge points from
//!\ param Destination vertex edge points to
//! \param Value of the edge
void addEdge(std::vector<edge> &myTree, int v1, int v2, int value) {
	edge tempEdge;
	tempEdge.v1 = v1;
	tempEdge.v2 = v2;
	tempEdge.value = value;
	myTree.push_back(tempEdge);
}


//! \param The tree
//! \param The starting source
//! \param The ending destination
//! \return the path from starting to end
bool bfs(std::vector<edge> myGraph, int source, int sink) {
	std::list<bool> visited(myGraph.size());
	std::vector<edge> path(myGraph.size());
	std::queue<int> q;
	q.push(source);
	visited[source] = true;
	
	while (!q.empty()) {
		int u = q.front();
		q.pop();
		for (std::vector<edge>::iterator it = myGraph.begin(); it != myGraph.end(); ++it) {
			int i = std::distance(myGraph.begin(), it);
			if (visited[i] == false) {
				q.push(i);
				path[i] = it->value;
				visited[i] = true;
			}

		}

	}	
	return (visited[sink] == true);	
} 

//! \param The tree
//! \param The starting source
//! \param The ending destination
//! \return the maximum possible flow
int letUsFordFulkThisShit(std::vector<edge> myGraph, int source, int sink) {
	std::vector<edge> resGraph = myGraph;
	std::vector<edge> path(myGraph.size());
	int max_flow = 0;
	while (bfs(resGraph, source, sink)) {
		int path_flow = (unsigned int) ~0 >> 1;
		for (std::vector<edge>::iterator rt = resGraph.begin(); rt != resGraph.end(); ++rt)
			path_flow = path_flow <= rt->value ? path_flow : rt->value;
		for (std::vector<edge>::iterator rt = resGraph.begin(); rt != resGraph.end(); ++rt) {
			rt -= path_flow;
			rt += path_flow;
		}

		max_flow += path_flow;

	}
		return max_flow;

}

int main (int argc, char* argv[]) {
	if (argc >= 2) { if (strcmp(argv[1],"--help") == 0) { std::cout << "Usage: ./victor_wu_C++ [input] [output]" << std::endl << "\tinput" << std::endl; return 0; }
		else if (argc <= 3) {
			std::ifstream myFile(argv[1], std::ios_base::in); //< Input File, First Argument
			std::ofstream myFileOutput(argv[2]); //< Output File, Second Argument	
			std::string str;	

			std::vector<edge> myTree;

			//Reads the file
			int v1, v2, value;
			while (myFile >> v1 >> v2 >> value) {
				addEdge(myTree, v1, v2, value);
			}

			std::cout << "The max possible flow is: " << letUsFordFulkThisShit(myTree, 0, 5) << std::endl;


			myFileOutput.close();
			myFile.close();
			return 0;
		}
	}
	std::cerr << "Error, invalid amount of arguments. Refer to README for details on usage, or use command --help" << std::endl; return -1;
}
