#include <iostream>
#include<utility>
#include<vector>
#include<map>
#include<set>
using namespace std;

#ifndef KMEANS_H
#define KMEANS_H

using Point = pair<double,double>;

class Kmeans
{
private:
	size_t m_k;
	map<int, set<Point>> m_closestCentroid; // index of centroid -> points close to him
	vector<Point> m_points;
	size_t m_fieldSizeX;
	size_t m_fieldSizeY;
	size_t m_numberOfPoints;
	
	bool* m_hasChanged;
	Point* m_clusterCentroids;

	void init(size_t k);
	void makeRandomCentroids();
	bool checkChanges();
	void makeFalse();
	size_t min(Point& p);
	Point average(set<Point>&);
	Point makePair();
	bool isInSet(const set<Point>& points, Point p);
	void loadPoints(const char*);
	void printResult() const;

public:
	Kmeans(const char*);
	~Kmeans();

	void clusterize(size_t k);
};

#endif
