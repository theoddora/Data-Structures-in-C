#include <iostream>
#include "Kmeans.h"
using namespace std;


int main()
{
	char* points = "points.txt";
	Kmeans algorithm(points);
	algorithm.clusterize(2);
	
	system("pause");
	return 0;
}