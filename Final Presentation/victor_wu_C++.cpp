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
#include <unordered_map>

#define DEBUG 1

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
bool bfs(std::vector<edge> myGraph, int source, int sink, std::vector<edge> &path) {
	std::unordered_map<int, bool> visited;	
	visited[source] = true;
	std::queue<int> q;
	q.push(source);
	while (!q.empty()) {
		int u = q.front();
			q.pop();

		for (std::vector<edge>::iterator it = myGraph.begin(); it != myGraph.end(); ++it) {
			int i = std::distance(myGraph.begin(), it);
//if (DEBUG) { for(auto it = visited.begin(); it != visited.end(); ++ it) std::cout << it->first << "," << it->second << "\t";std::cout << std::endl;}
if (DEBUG) { std::cout << "u: " << u << "\t" << "it->v1: " << it->v1 << std::endl; }	
			if ((u == it->v1) && (visited[i] != true)) {	
				path.push_back( *it );
				visited[i] = true;
				q.push(it->v2);
				it = myGraph.begin();
			}

		}
	}
if (DEBUG) std::cout << visited[sink] << std::endl;
	return (visited[sink] == true);	
}


//! Returns the max vertices
/*maxNumberOfVertices(std::vector<edge> myEdges) {
	int max = 0;
	for (std::vector<edge>::iterator it = myEdges.begin(); it != myEdges.end(); ++it) {
		if (it->v1 > max) max = it->v1;
		if (it->v2 > max) max = it->v2;
	}
} */


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

//if (DEBUG) for (std::vector<edge>::iterator it = myTree.begin(); it != myTree.end(); ++it) std::cout << it->v1 << std::endl;	


			//Ford Fulkerson Algorithm
			std::vector<edge> resGraph = myTree;	
			int max_flow = 0;
			std::vector<edge> path(resGraph.size());

			int source = 0;
			int sink = 5;

			while (bfs(resGraph, source, sink, path)) {
				int path_flow = (unsigned int) ~0 >> 1;
				for (std::vector<edge>::iterator rt = resGraph.begin(); rt != resGraph.end(); ++rt)
					path_flow = path_flow <= rt->value ? path_flow : rt->value;
				for (std::vector<edge>::iterator rt = resGraph.begin(); rt != resGraph.end(); ++rt) {
					rt -= path_flow;
					rt += path_flow;
				}

				max_flow += path_flow;

			}	

			std::cout << "The max possible flow is: " << max_flow << std::endl;


			myFileOutput.close();
			myFile.close();
			return 0;
		}
	}
	std::cerr << "Error, invalid amount of arguments. Refer to README for details on usage, or use command --help" << std::endl; return -1;
}
