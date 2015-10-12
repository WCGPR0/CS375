#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>

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


#define n argv[2]

using namespace std;

Point* resize(Point *A, int size, size_t& oldSize);
int smallest(Point p[], int n);

int size = 0, max_size = initialSize;
int *A = new int[max_size];


struct Point {
   int x = 0, y = 0,  z = 0;
};

int main(int argc, char* argv[]) {
	if (argc != 3) { cerr << "Error, invalid amount of arguments. Refer to README for details on usage, or use command --help" << endl; return -1;}
	if (strcmp(argv[1], "--help") == 0) { cout << "Usage: ./victor_wu_C++ [input] [output]" << endl; return 0; }

	fstream myFile(argv[1], ios_base::in);
	ofstream myFileOutput(argv[2]);
	
    Point *p = new Point[max_size];

    string line;
	//Reading the input file
    while (getline(myFile, line)) {
	   //Resizing on dynamic Points	
	   if (size >= max_size) p = resize(p, size, max_size);
   
	   //Splitting string into coordinates
	   size_t prev = 0, pos;
	   int count = 0;
	   while ((pos = line.find_first_of(',', prev) != string::npos)) {
			if (pos > prev) {
			   if (count == 0)
				  p[size++].x = stoi(line.substr(prev, pos-prev), nullptr);
			   else if (count == 1)
				  p[size++].y = stoi(line.substr(prev, pos-prev), nullptr);
			   else if (count == 2)
				  p[size++].z = stoi(line.substr(prev, pos-prev), nullptr);
			   else cerr << "Too many dimensions" << endl;
			   prev = pos + 1;
			}
	    }
		//Code based on Psuedo-code Wikipedia: Insertion Sort
		for (int i = 0; i < size; i++) {
		int j = i;
		while (j > 0 && p[j].x < p[j-1].x) {
			p[j].x ^= p[j-1].x; p[j].y ^= p[j-1].y;
			p[j-1].x ^= p[j].x; p[j-1].y ^= p[j].y;
			p[j].x ^= p[j-1].x; p[j].y ^= p[j-1].y;
			--j;
		}
		}
	  }

		cout << smallest(p, size);

	return 0;
}


int smallest(Point p[], int n) {

   int d = min(smallest(p, n/2), smallest(p+n, n/2));

   int strip[size];
   int j = 0;
   for (int i = 0, j = 0; i < size; ++i)
	  if (abs(strip[i]) - p[size/2].x < d)
		 strip[j] = p[i].x; ++j;
   int c = 0;
   for (int i = 0; i < size; ++i)
	  for (j = i+1; j < size && (strip[j] - strip[i]) < d; ++j)
		 c = min(strip[i], strip[j]);
  return min(d, c);
}

Point* resize(Point* A, int size, size_t& oldSize) {
	oldSize *= 2;
	Point *newArray = new Point[oldSize]();
	for (int i = 0; i < size-1; i++) {
		newArray[i].x = A[i].x;
		newArray[i].y = A[i].y;
		newArray[i].z = A[i].z;
   }
	delete [] A;
	A = newArray;
	return A;
}
