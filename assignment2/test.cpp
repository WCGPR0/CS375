#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>

#define initialSize 50

//Public GCC compiler-friendly macros

#define n argv[2]

using namespace std;

struct Point {
   int x;
   int y;
   int z;
};


int smallest(Point* p, int n);

int size = 0, max_size = initialSize;
int *A = new int[max_size];


int main(int argc, char* argv[]) {
		int test;
		Point* p = new Point();
		 smallest(p, test);

	return 0;
}

int smallest(Point *p, int n) {
return 0;
}
