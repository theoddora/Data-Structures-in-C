#include "Kmeans.h"
#include <fstream>
#include <iostream>
#include <algorithm>

Kmeans::Kmeans(const char* points) : m_k(0), m_clusterCentroids(nullptr)
{
	m_clusterCentroids = new ClusterCentroids();
	loadPoints(points);
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
		if (!file)
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
	ofstream myfile;
	myfile.open("example.txt");
	size_t i = 0;
	for (auto entry : m_closestCentroid)
	{
		Point p = m_clusterCentroids->get(i++);

		cout << "cluster #"
			<< entry.first
			<< " with center "
			<< "point["
			<< p.first
			<< ", "
			<< p.second
			<< "]; "
			<< " has the following "
			<< entry.second.size()
			<< " points:\n";

		myfile << "cluster #"
			<< entry.first
			<< " with center "
			<< "point["
			<< p.first
			<< ", "
			<< p.second
			<< "]; "
			<< " has the following "
			<< entry.second.size()
			<< " points:\n";

		for (vector<size_t>::iterator it = entry.second.begin(); it != entry.second.end(); ++it)
		{
			cout << "point["
				<< m_points.at(*it).first
				<< ", "
				<< m_points.at(*it).second
				<< "]; ";
			myfile << "point["
				<< m_points.at(*it).first
				<< ", "
				<< m_points.at(*it).second
				<< "]; ";
		}
		cout << endl;
		myfile << endl;
	}
	cout << "---- now writing to file ----" << endl;

	myfile.close();
}

bool Kmeans::checkEmptyClusters()
{
	for (size_t i = 0; i < m_k; i++)
	{
		if (m_closestCentroid.at(i).size() == 0)
		{
			return true;
		}
	}
	return false;
}

void Kmeans::init(size_t k)
{
	m_k = k;
	//orderPoints(0, m_points.size() - 1);
	makeRandomCentroids();
}

size_t Kmeans::partition(const size_t left, const size_t right)
{
	const int mid = left + (right - left) / 2;
	const Point pivot = m_points[mid];

	swap(m_points[mid], m_points[left]);
	int i = left + 1;
	int j = right;

	while (i <= j)
	{
		while (i <= j && m_points[i].first <= pivot.first)
			i++;

		while (i <= j && m_points[j].first > pivot.first)
			j--;

		if (i < j)
			swap(m_points[i], m_points[j]);

	}
	swap(m_points[i - 1], m_points[left]);
	return i - 1;
}

void Kmeans::orderPoints(size_t left, size_t right)
{
	if (left >= right)
	{
		return;
	}

	size_t part = partition(left, right);

	orderPoints(left, part - 1);
	orderPoints(part + 1, right);
}

void Kmeans::makeRandomCentroids()
{
	size_t numberOfPoints = m_points.size();

	double x = m_points[0].first, y = m_points[0].second;
	for (size_t i = 1; i < numberOfPoints; i++)
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
	size_t fieldSizeX = (size_t)ceil(x);
	size_t fieldSizeY = (size_t)ceil(y);

	m_clusterCentroids->init(m_k, numberOfPoints, fieldSizeX, fieldSizeY);

	for (size_t i = 0; i < m_k; ++i)
	{
		m_closestCentroid[i];
		clusterPointChanges[i];
		m_pointsBelongingToCluster[i];
	}
}

void Kmeans::putPointsInClusters()
{
	size_t numOfPoints = m_points.size();
	for (size_t i = 0; i < numOfPoints; ++i)
	{
		Point p = m_points[i];
		size_t indexAtAddingPoint = m_clusterCentroids->min(p);
		m_closestCentroid.at(indexAtAddingPoint).push_back(i);
		m_pointsBelongingToCluster.at(indexAtAddingPoint).insert(p);
		cout << "point[" << p.first << ", " << p.second << "]; added to cluster ["
			<< m_clusterCentroids->get(indexAtAddingPoint).first
			<< ", " << m_clusterCentroids->get(indexAtAddingPoint).second << "]\n";
	}
}

bool Kmeans::checkChanges()
{
	int counter = 0;
	for (auto const& entryReal : m_closestCentroid)
	{
		for (auto const& entryChecking : clusterPointChanges)
		{
			if (entryReal.second.size() == entryChecking.second.size() && equal(entryReal.second.begin(), entryReal.second.begin() + entryReal.second.size(), entryChecking.second.begin()))
			{
				counter++;
				break;
			}
		}
	}
	return counter == m_k;
}

void Kmeans::redefineClusters()
{
	m_closestCentroid.swap(clusterPointChanges);
	for (auto& entry : m_closestCentroid)
	{
		entry.second.clear();
	}
}

void Kmeans::makeNewClusters()
{
	m_clusterCentroids->clear();
	for (size_t i = 0; i < m_k; ++i)
	{
		Point p = m_clusterCentroids->average(m_pointsBelongingToCluster.at(i));
		cout << "new cluster centroid at position #" << i << "? -> " "[" << p.first << ", " << p.second << "]" << endl;
		m_clusterCentroids->insert(p);		
	}
	for (auto& entry : m_pointsBelongingToCluster)
	{
		entry.second.clear();
	}
}

void Kmeans::clusterize(size_t k)
{
	init(k);
	int numOfPoints = m_points.size();
	cout << "we are going to clusterize " << numOfPoints << " points" << endl;

	do
	{
		putPointsInClusters();

		if (!checkEmptyClusters() && checkChanges())
		{
			break;
		}
		redefineClusters();

		makeNewClusters();

	} while (true);

	printResult();
}
