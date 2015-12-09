#include <string.h>
#include <stdlib.h>
#include <stdio.h>

//shortest path from one node to another using floyd's algorithm

//array for city names when printing shortest path
char *cities[11] = {"NYC", "Allentown", "Scranton", "Binghamton", "Albany",
	"Montreal", "Syracuse", "Kingston", "Rochester", "Buffalo", "Toronto"};

//integer references to cities
int NYC = 0;
int Allentown = 1;
int Scranton = 2;
int Binghamton = 3;
int Albany = 4;
int Montreal = 5;
int Syracuse = 6;
int Kingston = 7;
int Rochester = 8;
int Buffalo = 9;
int Toronto = 10;

//p table initialization
int P[11][11];

//calculates shortest path in graph
void path(int q, int r) {
	if (P[q][r] != 0) {
		path(q, P[q][r]);
		printf("--> %s", cities[P[q][r]]);
		path(P[q][r], r);
		return;
	}

	else {
		return;
	}
}

int main() {

	//initialize the D table
	unsigned int D[11][11];
	//set all the d table values to infinity
	//set the p table values to 0
	for (int i = 0; i < 11; i++) {
		for (int j = 0; j < 11; j++) {
			D[i][j] = -1;
			P[i][j] = 0;
		}
		D[i][i] = 0;
	}

	//make a d table of all adjacent connections/paths
	D[NYC][Allentown] = 70;
	D[NYC][Scranton] = 100;
	D[NYC][Binghamton] = 180;
	D[NYC][Albany] = 140;

	D[Allentown][NYC] = 70;
	D[Allentown][Scranton] = 65;

	D[Scranton][NYC] = 100;
	D[Scranton][Allentown] = 65;
	D[Scranton][Binghamton] = 60;

	D[Binghamton][NYC] = 180;
	D[Binghamton][Scranton] = 60;
	D[Binghamton][Syracuse] = 70;

	D[Syracuse][Albany] = 100;
	D[Syracuse][Binghamton] = 70;
	D[Syracuse][Kingston] = 65;
	D[Syracuse][Rochester] = 70;

	D[Albany][Montreal] = 130;
	D[Albany][NYC] = 140;
	D[Albany][Syracuse] = 100;

	D[Kingston][Montreal] = 160;
	D[Kingston][Toronto] = 180;
	D[Kingston][Syracuse] = 65;

	D[Montreal][Albany] = 130;
	D[Montreal][Kingston] = 160;

	D[Rochester][Syracuse] = 70;
	D[Rochester][Buffalo] = 60;

	D[Buffalo][Rochester] = 60;
	D[Buffalo][Toronto] = 100;

	D[Toronto][Kingston] = 180;
	D[Toronto][Buffalo] = 100;

	//Floyd's algorithm
	for (int k = 0; k < 11; k++) {
		for (int i = 0; i < 11; i++) {
			for (int j = 0; j < 11; j++) {
				//if the path from i to j is greater than
				//i to intermediate k and intermediate k to j
				//then set (i to k) + (k to j) to the shortest
				//path and set the intermediate node k in p table
				if ((D[i][j] > (D[i][k] + D[k][j])) &&
		          	    (D[i][k] != -1) && D[k][j] != -1) {
						D[i][j] = D[i][k] + D[k][j];
						P[i][j] = k;
				}
				printf("%i", P[i][j]);
			}
		}
	}
	//call path to calculate shortest path from NYC to Toronto
	printf("Shortest path from NYC to Toronto is : %s", cities[0]);
	path(0, 10);	
	return path;
	printf("%s and gives a total distance of: %d miles\n\n ", cities[10], 	D[NYC][Scranton] + D[Scranton][Binghamton] + D[Binghamton][Syracuse]  + D[Syracuse][Rochester] + D[Rochester][Buffalo] + D[Buffalo][Toronto]);
	return 0;

}
