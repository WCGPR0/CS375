/** Victor Wu
    CS375 - Assignment 4*/

#include <iostream>
#include <string>
#include <fstream>
#include <cstring>
#include <list>

#define initialSize 50
#define ISDIGIT(s) !s.empty() && s.find_first_not_of("0123456789") == std::string::npos

/// Helper Function in outputting the shortest path
void path(int q, int r, int **P, std::string *list);

int n = 0, size = 0, max_size = initialSize;


// Graphs
class Node {
	int v, w;
public:
	AdjListNode(int v, int w) { this->v = v; this->w = w; }
	int getV() { return v; }
	int getWeight() { return w; }

};

class Graph {
	int v; //< Number of Vertices
	list<Node> *nodeList;
	void topologicalSort(int v, bool visited[], stack<int> &Stack);


}



int main (int argc, char* argv[]) {
	if (argc == 2 && strcmp(argv[1],"--help") == 0) { std::cout << "Usage: ./victor_wu_C++ [arguments] [input] [output]" << std::endl << "Arguments:\n\t--A[N]\tMinimum Number of semesters necessary to complete the cirriculum\n\t--B:\tExists cycle within a graph" << std::endl; return 0; }	
	if (argc == 5 && strcmp(argv[1], "--A") == 0) {
	std::ifstream myFile(argv[3], std::ios_base::in); //< Input File, First Argument
	std::ofstream myFileOutput(argv[4]); //< Output File, Second Argument
	max_size = atoi(argv[2]); //< Size of Input File, Third Argument

	std::string str;
	std::string list_param1[max_size], //< Array of First Arguments
	list_param2[max_size]; //< Array of Second Arguments
	int list_param3[max_size]; //< Array of Third Arguments
	while (size < max_size) {
		//Paramter 1 - Departure
		myFile >> str;
		if (strcmp(str, "requires")) {


		}
		else if (strcmp(str, "and")) {

		}
		else {

		}
		if (ISDIGIT(str)) {std::cerr << "Invalid input file. Detected integer (" << str << ") in destination names." << std::endl;return -1;}
		list_param1[size] = str;

		//Paramter 2 - Arrival
		myFile >> str;	
		if (ISDIGIT(str)) {std::cerr << "Invalid input file. Detected integer (" << str << ") in destination names." << std::endl; return -1;}
		list_param2[size] = str;

		//Paramter 3 - Distance
		myFile >> str;
		if (!ISDIGIT(str)) {std::cerr << "Invalid input file. Detected non-integer (" << str << ") in distances." << std::endl; return -1;}
		list_param3[size] = stoi(str); 

		size++;
	}	

	int **P = new int*[max_size]; //< P Table
	int **D = new int*[max_size]; //< D Table
	for (int i = 0; i < max_size; ++i) {
		P[i] = new int[max_size]();
		D[i] = new int[max_size];
		std::fill_n(D[i], max_size, -1);	
	}	
	
	//Construct int-based Table based on uniqueness
	std::string list[max_size]; //< Sring Array list of Cities
	int tempSize = -1, //< Size of List of Cities
	count = -1; //< Amount of entries in D-table	
	for (int i = 0; i < size; ++i) {
		int index = -1;
		for (int j = 0; j < tempSize; ++j) if (list_param1[i].compare(list[j]) == 0) index = j;
		if (index == -1) {
			index = ++tempSize;
			list[tempSize] = list_param1[i];
		}
		int _index = -1;
		for (int j = 0; j < tempSize; ++j) if (list_param2[i].compare(list[j]) == 0) _index = j;
		if (_index == -1) {
			_index = ++tempSize;
			list[tempSize] = list_param2[i];
		}
		D[index][_index] = list_param3[++count];	
	}


	// TESTING
	std::cout << tempSize << std::endl;
	for (int i = 0; i < tempSize; i++)
		 std::cout << list[i] << std::endl;

	//Floyds' alogrithm
		for (int i = 0; i < max_size; ++i) {
			for (int j = 0; j < max_size; ++j) {
				for (int k = 0; k < max_size; ++k) {
					if ((D[j][k] > (D[j][i] + D[i][k])) && (D[j][i] != -1) && D[i][k] != -1) {
						D[j][k] = D[j][i] + D[i][k];
						P[j][k] = i;
					}
		//			printf("%i", P[j][k]);
				}
			}
		}


	/// Outputs the D-table to the output file
	for (int i = 0; i < max_size; ++i)
		for (int j = 0; j < max_size; ++j)
			myFileOutput << D[i][j] << ", ";
		myFileOutput << std::endl;


	/// Outputs the P-table to the output file
	for (int i = 0; i < max_size; ++i)
		for (int j = 0; j < max_size; ++j)
			myFileOutput << P[i][j] << ", ";
		myFileOutput << std::endl;


	std::cout << "Shortest Path: " << list[0];
	path(0, tempSize, P, list);

	std::cout << list[tempSize] << std::endl;
	std::cout << "Total Distance: ";
	int sum = 0;
	for (int i = 0; i < max_size; ++i)
		for (int j = 0; j < max_size; ++j)
			if (P[i][j] != 0) sum+= D[i][j];
	std::cout << sum << std::endl;

	for (int i = 0; i < max_size; ++i) {
		delete P[i];
		delete D[i];
	}
	delete P;
	delete D;
	
	myFileOutput.close();
	myFile.close();
	return 0;
	}
	else if (argc == 4 && strcmp(argv[1], "--B") == 0) {


	}
	else { std::cerr << "Error, invalid amount of arguments. Refer to README for details on usage, or use command --help" << std::endl; return -1;}
}


/// Helper Function in outputting the shortest path
void path(int q, int r, int **P, std::string* list) {
	if (P[q][r] != 0) {
		path(q, P[q][r], P, list);
		std::cout << " -> " << list[P[q][r]];
		path(P[q][r], r, P, list);
	}
	return;
}
