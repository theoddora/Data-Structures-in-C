#include<vector>
#include<map>
#include<set>
#include "ClusterCentroids.h"
using namespace std;

#ifndef KMEANS_H
#define KMEANS_H

class Kmeans
{
private:
	size_t m_k; // number of clusters
	vector<Point> m_points; // points we are going to clusterize

	map<size_t, vector<size_t>> m_closestCentroid; // index of centroid of cluster -> points close to him
	map<size_t, set<Point>> m_pointsBelongingToCluster; // index of centroid of cluster -> points close to him	
	map<size_t, vector<size_t>> clusterPointChanges; // points who stayed in their cluster and didnt go to another one
	
	ClusterCentroids* m_clusterCentroids; // the generated centroids during algorithm

	void init(size_t k);
	void makeRandomCentroids();

	size_t Kmeans::partition(const size_t, const size_t);
	void orderPoints(size_t, size_t);

	void putPointsInClusters();
	bool checkChanges();
	void redefineClusters();
	void makeNewClusters();
	
	void loadPoints(const char*);
	void printResult() const;
	bool checkEmptyClusters();

public:
	Kmeans(const char*);

	void clusterize(size_t);
};

#endif
