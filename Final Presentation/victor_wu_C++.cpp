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
bool bfs(std::vector<edge> myGraph, int source, int sink, std::vector<int> &path) {
	std::unordered_map<int, bool> visited;	
	std::queue<int> q;
	q.push(source);
	visited[source] = true;
	while (!q.empty()) {
		int u = q.front();
			q.pop();
		for (std::vector<edge>::iterator it = myGraph.begin(); it != myGraph.end(); ++it) {	
//if (DEBUG) { for(auto it = visited.begin(); it != visited.end(); ++ it) std::cout << it->first << "," << it->second << "\t";std::cout << std::endl;}
if (DEBUG) { std::cout << "u: " << u << "\t" << "it->v1: " << it->v1 << "\tvisited[u]: " << visited[u] << std::endl; }	
			if ((u == it->v1) && (visited[it->v2] != true)) {	
if (DEBUG) std::cout << "ADDING " << u << std::endl;
				path.push_back( it->v2 );
				visited[u] = true;
				q.push(it->v2);	
			}

		}	
	}
//delete[] visited;
if (DEBUG) std::cout<< "\t" << visited[sink] << std::endl;
	return (visited[sink-1] == true);	
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
			std::vector<int> path;

			int source = 0;
			int sink = 5;

			while (bfs(resGraph, source, sink, path)) {
				int path_flow = (unsigned int) ~0 >> 1;
				for (std::vector<int>::iterator rt = path.begin(); rt != path.end(); ++rt)
					path_flow = path_flow < *rt ? path_flow : *rt;
				for (std::vector<int>::iterator rt = path.begin(); rt != path.end(); ++rt) {	
					resGraph[*rt].value -= path_flow;
					if (resGraph[*rt].value <= 0) resGraph.erase(*rt);	
				}

				max_flow += path_flow;

			}	

			std::cout << "The max possible flow is: " << max_flow << std::endl;
if (DEBUG) for (auto it = path.begin(); it != path.end(); ++it) std::cout << *it << std::endl; 

			myFileOutput.close();
			myFile.close();
			return 0;
		}
	}
	std::cerr << "Error, invalid amount of arguments. Refer to README for details on usage, or use command --help" << std::endl; return -1;
}
