/** Victor Wu
    CS375 - Assignment 3 */

#include <iostream>
#include <string>
#include <fstream>
#include <cstring>

#define initialSize 50
#define ISDIGIT(s) !s.empty() && s.find_first_not_of("0123456789") == std::string::npos

int n = 0, size = 0, max_size = initialSize;

int main (int argc, char* argv[]) {
	if (argc == 2 && strcmp(argv[1],"--help") == 0) { std::cout << "Usage: ./victor_wu_C++ [input] [output] [size]" << std::endl; return 0; }	
	if (argc != 4) { std::cerr << "Error, invalid amount of arguments. Refer to README for details on usage, or use command --help" << std::endl; return -1;}	

	std::ifstream myFile(argv[1], std::ios_base::in);
	std::ofstream myFileOutput(argv[2]);
	max_size = atoi(argv[3]);

	std::string str;	
	std::string list_param1[max_size], list_param2[max_size];
	int list_param3[max_size];
	while (size < max_size) {
		//Paramter 1 - Departure
		myFile >> str;	
		if (ISDIGIT(str)) {std::cerr << "Invalid input file. Detected integer (" << str << ") in destination names." << std::endl;return -1;}
		list_param2[size] = str;

		//Paramter 2 - Arrival
		myFile >> str;	
		if (ISDIGIT(str)) {std::cerr << "Invalid input file. Detected integer (" << str << ") in destination names." << std::endl; return -1;}
		list_param2[size] = str;

		//Paramter 3 - Distance
		myFile >> str;
		if (!ISDIGIT(str)) {std::cerr << "Invalid input file. Detected non-integer (" << str << ") in distances." << std::endl; return -1;}
		list_param1[size] = stoi(str); 

		size++;
		
	}	

	int **P = new int*[max_size];
	for (int i = 0; i < max_size; ++i) {
		P[i] = new int[max_size]();
	}
	int **D = new int*[max_size];
	for (int i = 0; i < max_size; ++i) {
		D[i] = new int[max_size]{-1};			
	}	
	
	//Construct int-based Table	
	std::string temp[max_size];
	int tempSize = -1, count = -1;	
	for (int i = 0; i < size; ++i) {
		int index = -1;
		for (int j = 0; j < tempSize; ++j) if (list_param1[i].compare(temp[j]) == 0) index = j;
		if (index == -1) {
			index = tempSize;
			temp[++tempSize] = list_param1[i];
		}
		int _index = -1;
		for (int j = 0; j < tempSize; ++j) if (list_param2[i].compare(temp[j]) == 0) _index = j;
		if (_index == -1) {
			_index = tempSize;
			temp[++tempSize] = list_param2[i];
		}
		D[index][_index] = list_param3[++count];	
	}



	for (int i = 0; i < max_size; ++i)
		for (int j = 0; j < max_size; ++j)
			std::cout << D[i][j] << std::endl;

	myFileOutput.close();
	myFile.close();
	return 0;
}
