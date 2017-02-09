#include "ClusterCentroids.h"
#include <algorithm>
using namespace std;

ClusterCentroids::ClusterCentroids() : m_fieldSizeX(0), m_fieldSizeY(0), m_k(0), m_numberOfPoints(0)
{
	srand(time(NULL));
}

Point ClusterCentroids::get(size_t i) const
{
	return m_centroids[i];
}

void ClusterCentroids::makeRandomCentroids()
{
	for (size_t i = 0; i < m_k; ++i)
	{
		m_centroids.push_back(makePair());
	}
}

void ClusterCentroids::init(size_t k, size_t numberOfPoints, size_t fieldSizeX, size_t fieldSizeY)
{
	m_k = k;
	m_numberOfPoints = numberOfPoints;
	m_fieldSizeX = fieldSizeX;
	m_fieldSizeY = fieldSizeY;
	makeRandomCentroids();
}

size_t ClusterCentroids::min(const Point & p)
{
	double minDistance = sqrt(pow((m_centroids[0].first - p.first), 2) + pow((m_centroids[0].second - p.second), 2));
	size_t index = 0;

	double distance;
	for (size_t i = 1; i < m_centroids.size(); ++i)
	{
		distance = sqrt(pow((m_centroids[i].first - p.first), 2) + pow((m_centroids[i].second - p.second), 2));
		if (distance < minDistance)
		{
			index = i;
			minDistance = distance;
		}
	}
	return index;
}

Point ClusterCentroids::makePair()
{
	Point p;
	bool isIn = false;
	do
	{
		p = makeRandomPair();
		isIn = find(m_centroids.begin(), m_centroids.end(), p) != m_centroids.end();
	} while (isIn);
	return p;
}

Point ClusterCentroids::makeRandomPair()
{
	return make_pair(rand() % m_fieldSizeX, rand() % m_fieldSizeY);
}

Point ClusterCentroids::average(set<Point>& pointsToCluster)
{
	size_t numPointsInCurrentCluster = pointsToCluster.size();
	if (numPointsInCurrentCluster == 0)
	{
		return makePair();
	}
	double x = .0, y = .0;
	for (set<Point>::iterator it = pointsToCluster.begin(); it != pointsToCluster.end(); ++it)
	{
		x += it->first;
		y += it->second;
	}
	return Point(x / numPointsInCurrentCluster, y / numPointsInCurrentCluster);
}

void ClusterCentroids::insert(Point p)
{
	m_centroids.push_back(p);
}

void ClusterCentroids::clear()
{
	m_centroids.clear();
}
