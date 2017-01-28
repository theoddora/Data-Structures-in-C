#include "Kmeans.h"
#include <stdlib.h>
#include <time.h>
#include <fstream>

Kmeans::Kmeans(const char* points) : m_k(0), m_hasChanged(nullptr), m_clusterCentroids(nullptr)
{
	loadPoints(points);
}

Kmeans::~Kmeans()
{
	delete m_hasChanged;
	delete[] m_clusterCentroids;
}

void Kmeans::clusterize(size_t k)
{
	init(k);
	cout << "we are going to clusterize " << m_numberOfPoints << " points" << endl;

	do
	{
		makeFalse();
		for (size_t i = 0; i < m_numberOfPoints; ++i)
		{
			Point p = m_points[i];
			size_t indexAtAddingPoint = min(p);
			if (isInSet(m_closestCentroid.at(indexAtAddingPoint), p))
			{
				m_hasChanged[i] = true;
			}
			else
			{
				m_closestCentroid.at(indexAtAddingPoint).insert(p);
			}
		}

		if (checkChanges())
		{
			break;
		}

		for (size_t i = 0; i < m_k; ++i)
		{
			Point p = average(m_closestCentroid.at(i));
			cout << "new cluster centroid at position #" << i << "? -> " "[" << p.first << ", " << p.second << "]" << endl;
			m_clusterCentroids[i] = make_pair(p.first, p.second);
		}
	} while (1);

	printResult();
}

void Kmeans::init(size_t k)
{
	srand(time(NULL));
	m_k = k;
	m_clusterCentroids = new Point[m_k];
	makeRandomCentroids();
}

void Kmeans::makeRandomCentroids()
{
	m_numberOfPoints = m_points.size();

	m_hasChanged = new bool[m_numberOfPoints];

	double x = m_points[0].first, y = m_points[0].second;
	for (size_t i = 1; i < m_numberOfPoints; i++)
	{
		if (m_points[i].first > x)
		{
			x = m_points[i].first;
		}
		if (m_points[i].second > y)
		{
			y = m_points[i].second;
		}
	}
	m_fieldSizeX = (int)ceil(x);
	m_fieldSizeY = (int)ceil(y);

	for (size_t i = 0; i < m_k; ++i)
	{
		m_clusterCentroids[i] = makePair();
		m_closestCentroid[i];
	}
}

bool Kmeans::checkChanges()
{
	for (auto const& entry : m_closestCentroid)
	{
		size_t pointsInCurrentCluster = entry.second.size();
		if (pointsInCurrentCluster == 0)
		{
			return false;
		}
	}
	int counterPointsInClusters = 0;
	for (size_t i = 0; i < m_numberOfPoints; ++i)
	{
		if (m_hasChanged[i])
		{
			++counterPointsInClusters;
		}
	}
	return counterPointsInClusters == m_numberOfPoints;
}

void Kmeans::makeFalse()
{
	for (size_t i = 0; i < m_numberOfPoints; ++i)
	{
		m_hasChanged[i] = false;
	}
}

size_t Kmeans::min(Point& p)
{
	double minDistance = sqrt(pow((m_clusterCentroids[0].first - p.first), 2) + pow((m_clusterCentroids[0].second - p.second), 2));
	size_t index = 0;

	double distance;
	for (size_t i = 1; i < m_k; ++i)
	{
		distance = sqrt(pow((m_clusterCentroids[i].first - p.first), 2) + pow((m_clusterCentroids[i].second - p.second), 2));
		if (distance < minDistance)
		{
			index = i;
		}
	}
	return index;
}

Point Kmeans::average(set<Point>& pointsToCluster)
{
	size_t numberOfPoiunts = pointsToCluster.size();
	if (numberOfPoiunts == 0)
	{
		return makePair();
	}
	double x = 0, y = 0;
	for (set<Point>::iterator it = pointsToCluster.begin(); it != pointsToCluster.end(); ++it)
	{
		x += it->first;
		y += it->second;
	}
	return Point(x / numberOfPoiunts, y / numberOfPoiunts);
}

Point Kmeans::makePair()
{
	return make_pair(rand() % m_fieldSizeX, rand() % m_fieldSizeY);
}

bool Kmeans::isInSet(const set<Point>& points, Point p)
{
	for (set<Point>::iterator it = points.begin(); it != points.end(); ++it)
	{
		if (p.first == it->first && p.second == it->second)
		{
			return true;
		}
	}
	return false;
}

void Kmeans::loadPoints(const char* points)
{
	char* line = new char[1024];
	ifstream file;

	file.open(points);

	char* token, *otherPart;
	do
	{
		file.getline(line, 1024);
		if (file.eof())
		{
			break;
		}
		token = strtok_s(line, " ", &otherPart);
		Point point;
		point.first = atof(token);
		token = strtok_s(nullptr, " ", &otherPart);
		point.second = atof(token);
		m_points.push_back(point);
	} while (file);
	file.close();
}

void Kmeans::printResult() const
{
	size_t i = 0;
	for (auto const& entry : m_closestCentroid)
	{
		cout << "cluster #"
			<< entry.first
			<< " with center "
			<< "point["
			<< m_clusterCentroids[i].first
			<< ", "
			<< m_clusterCentroids[i].second
			<< "]; "
			<< " has the following "
			<< entry.second.size()
			<< "points:\n";

		for (set<Point>::iterator it = entry.second.begin(); it != entry.second.end(); ++it)
		{
			cout << "point["
				<< it->first
				<< ", "
				<< it->second
				<< "]; ";
		}
		cout << endl;
	}

}
