/** Victor Wu
  CS375 - Assignment 4*/

#include <iostream>
#include <string>
#include <fstream>
#include <cstring>
#include <algorithm>
#include <vector>

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
//! \param Destination vertex edge points to
//! \param Value of the edge
inline void addEdge(std::vector<edge> &myTree, int v1, int v2, int value) {
	edge tempEdge;
	tempEdge.v1 = v1;
	tempEdge.v2 = v2;
	tempEdge.value = value;
	myTree.push_back(tempEdge);
}

//! \param The edge to be found
//! \return the set the set is found in
int find_vertex(std::vector<std::vector<int> > &sets, int vertex) {
	std::vector<std::vector<int> >::iterator row;
	std::vector<int>::iterator col;
	for (row = sets.begin(); row != sets.end(); ++row) {
		for (col = row->begin(); col != row-> end(); ++col) {
			if (vertex == *col)
				return std::distance(sets.begin(), row);
		}
	}
	return -1;
}


//! \param A graph of edges
//! \return the MST constructed from the edges
std::vector<edge> generateMST(std::vector<edge> &edges) {

	std::vector<edge> MST;
	std::vector<std::vector<int> > sets(edges.size());	

	//Sorts the edges in non-increasing order
	for (unsigned int i = 0; i < edges.size(); i++) {
		for (unsigned int j = 0; j < edges.size(); j++) {
			if (edges[i].value > edges[j].value) {
				edge temp = edges[i];
				edges[i] = edges[j];
				edges[j] = temp;	
			}

		}

	}
	for (unsigned int i = 0; i < edges.size(); ++i)
		sets[i].push_back(i);
	for (unsigned int i = 0; i < edges.size(); ++i) {
		int v1 = find_vertex(sets, edges[i].v1);
		int v2 = find_vertex(sets, edges[i].v2);

		if (v1 != v2) {
			MST.push_back(edges[i]);	
			sets[v1].insert(sets[v1].end(), sets[v2].begin(), sets[v2].end()); //< Merges subset v2 with subset v1	
		}
	}
	return MST;
}


//! \param A graph of edges
//! \param The list of vertices to search
//! \return the position of the vertex found or -1 if not found
int traverseTree(std::vector<edge> &edges, std::vector<int> &vertices) {
	for (std::vector<edge>::iterator itEdge = edges.begin(); itEdge != edges.end(); ++itEdge) {
		for (std::vector<int>::iterator itInt = vertices.begin(); itInt != vertices.end(); ++itInt) {
			if ((itEdge->v1 == *itInt) || (itEdge->v2 == *itInt)) {	
				if (std::find(vertices.begin(), vertices.end(), itEdge->v1) == vertices.end()) vertices.push_back(itEdge->v1);
				if (std::find(vertices.begin(), vertices.end(), itEdge->v2) == vertices.end()) vertices.push_back(itEdge->v2);
				edges.erase(itEdge);	
for (std::vector<int>::iterator itInt = vertices.begin(); itInt != vertices.end(); ++itInt) std::cout << *itInt << "\t";
std::cout<<std::endl;
				return *itInt;	
			}	
		}	
	}
	return -1;

}

int main (int argc, char* argv[]) {
	if (argc >= 2) { if (strcmp(argv[1],"--help") == 0) { std::cout << "Usage: ./victor_wu_C++ [input] [output]" << std::endl << "\tinput" << std::endl; return 0; }	
		else if (argc <= 3) {
			std::ifstream myFile(argv[1], std::ios_base::in); //< Input File, First Argument
			std::ofstream myFileOutput(argv[2]); //< Output File, Second Argument	
			std::string str;		

			std::vector<edge> edges, MST;

			//Reads the file
			int v1, v2, value;
			while (myFile >> v1 >> v2 >> value) {
				addEdge(edges, v1, v2, value);
			}
			MST = generateMST(edges);

			/*		if (true) {
					for (unsigned int i = 0; i < MST.size(); ++i)
					std::cout << MST[i].v1 << "\t" << MST[i].v2 << "\t" << MST[i].value << std::endl;
					}*/
			/*		if (true) {
					for (unsigned int i = 0; i < edges.size(); ++i)
					std::cout << edges[i].v1 << "\t" << edges[i].v2 << "\t" << edges[i].value << std::endl;
					}*/

			//Traverse MST, Pop off MST from edges
			std::vector<int> emptyVertex {MST[0].v1};
			while(!MST.empty()) {		
				int x = traverseTree(MST, emptyVertex);
				if (x >= 0) std::cout << "v" << x << std::endl;
				else std::cout << "New group" << std::endl;	
			}


			myFileOutput.close();
			myFile.close();
		}

		return 0;
	}
	std::cerr << "Error, invalid amount of arguments. Refer to README for details on usage, or use command --help" << std::endl; return -1;
}
