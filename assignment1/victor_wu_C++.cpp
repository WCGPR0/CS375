#include <iostream>
#include <string>
#include <fstream>
#include <cstring>

using namespace std;

#define initialSize 50

//Public GCC compiler-friendly macros
#define min(a,b) \
	({ __typeof__ (a) _a = (a); \
	 __typeof__ (b) _b = (b); \
	 _a < _b ? _a : _b; })

#define max(a,b) \
	({ __typeof__ (a) _a = (a); \
	 __typeof__ (b) _b = (b); \
	 _a > _b ? _a : _b; })

int binary_search(int *A, int firstIndex, int lastIndex, int sum);

int main (int argc, char* argv[]) {
	if (argc != 3) { cerr << "Error, invalid amount of arguments. Refer to README for details on usage, or use command --help" << endl; return -1;}
	if (strcmp(argv[1], "--help") == 0) { cout << "Usage: ./victor_wu_C++ [input] [output]" << endl; return 0; }

	int n = 0, size = 0;
	int *A = new int[initialSize];
	int *B = new int[initialSize];

	fstream myFile(argv[1], ios_base::in);
	ofstream myFileOutput(argv[2]);

	int sum = 0;

	while (myFile >> A[size++]) {
		//Code based on Psuedo-code Wikipedia: Insertion Sort
		for (int i = 0; i < size; i++) {
			int j = i;
			while (j > 0 && A[j] < A[j-1]) {
				A[j] ^= A[j-1];
				A[j-1] ^= A[j];;
				A[j] ^= A[j-1];	
				j--;
			}

		}
		sum+=A[size-1];
	}
	size--;

	for (int i = 0; i < size; i++) B[i] = sum - A[i];

	// Binary search for complement
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			if (binary_search(&*A, min(A[i],A[j]), size-1, A[i]-A[j]) != -1) myFileOutput << max(A[i],A[j]) << endl;	
		}
	}


	delete [] A;


	myFileOutput.close();
	myFile.close();
	return 0;
}

//Code based on Psuedo-code Wikipedia: Binary Sort
int binary_search(int *A, int firstIndex, int lastIndex, int sum) {
	int returnIndex;
	if (firstIndex > lastIndex) returnIndex = -1;
	else {
		int midIndex = (firstIndex + lastIndex) / 2;
		if (sum == A[midIndex]) returnIndex = midIndex;
		else if (sum < A[midIndex]) returnIndex = binary_search(A, firstIndex, midIndex-1, sum);
		else returnIndex = binary_search(A, midIndex+1, lastIndex, sum);
	}
	return returnIndex;
}

void resize(int *A, int size, size_t oldSize) {
	oldSize *= 2;
	int *newArray = new int[oldSize];
	for (int i = 0; i < size; i++)
		newArray[i] = A[i];
	delete [] A;
	A = newArray;
}

