#include <time.h>
#include <stdlib.h>
#include <iostream>
#include <utility>
#include <vector>
#include <set>
using namespace std;

#ifndef CLUSTERCENTROIDS_H
#define CLUSTERCENTROIDS_H


using Point = pair<double, double>;

class ClusterCentroids
{
private:
	size_t m_k;
	vector<Point> m_centroids;
	size_t m_numberOfPoints;
	size_t m_fieldSizeX;
	size_t m_fieldSizeY;

	void makeRandomCentroids();
	Point makePair();
	Point makeRandomPair();

public:
	ClusterCentroids();
	Point get(size_t i) const;

	void init(size_t, size_t, size_t, size_t);
	size_t min(const Point& p);
	Point average(set<Point>& pointsToCluster);
	void insert(Point p);
	void clear();
};
#endif // !CLUSTERCENTROIDS_H