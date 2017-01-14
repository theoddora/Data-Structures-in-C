#include "ShortestRoot.h"
#include <iostream>
using namespace std;

//constructor && destructor
ShortestRoot::ShortestRoot(Room* room) : m_room(nullptr), m_closedList(nullptr)
{
	m_room = room;
	m_tom = m_room->getTomCoordinate();
	m_jerry = m_room->getJerryCoordinates();
	m_roomSize = m_room->getRoomCoordinates();

	makeRoom(m_roomSize);
}

ShortestRoot::~ShortestRoot()
{
	// delete m_room;
	// for (int i = 0; i < m_roomSize; ++i)
	// {
	// 	delete[] m_closedList[i];
	// }
	// delete[] m_closedList;
}

//private functions
bool ShortestRoot::isDestination(Coordinates coordinate)
{
	return coordinate.x == m_jerry.x && coordinate.y == m_jerry.y;
}

void ShortestRoot::makeRoom(Coordinates coordinates)
{
	this->m_closedList = new bool*[coordinates.x];
	for (size_t i = 0; i < coordinates.x; ++i)
	{
		m_closedList[i] = new bool[coordinates.y];
	}
	for (size_t i = 0; i < coordinates.x; ++i)
	{
		for (size_t j = 0; j < coordinates.y; ++j)
		{
			m_closedList[i][j] = false;
		}
	}
}

bool ShortestRoot::isValid(Coordinates coordinates)
{
	return (coordinates.x >= 0) && (coordinates.x < m_roomSize.x) && (coordinates.y >= 0) && (coordinates.y < m_roomSize.y);
}

bool ShortestRoot::isNotFurniture(Cell* cell)
{
	return cell->special != 'c';
}

double ShortestRoot::calculateHValue(Coordinates coordinates)
{
	return sqrt((coordinates.x - m_jerry.x)*(coordinates.x - m_jerry.x) + (coordinates.y - m_jerry.y)*(coordinates.y - m_jerry.y));
}

//public functions
void ShortestRoot::findPath()
{
	CoordinatesWithPath startCoordinates(m_tom, "");
	m_openList.push(startCoordinates);
	tree.insert("start");

	//starts
	Coordinates currentCoordinates;
	while (!m_openList.empty())
	{
		currentCoordinates = m_openList.top().coordinates;
		string path = m_openList.top().path;

		m_openList.pop();

		m_closedList[currentCoordinates.x][currentCoordinates.y] = true;

		Coordinates forwardCoordinate(currentCoordinates.x - 1, currentCoordinates.y),
			backwardCoordinate(currentCoordinates.x + 1, currentCoordinates.y),
			leftCoordinate(currentCoordinates.x, currentCoordinates.y + 1),
			rightCoordinate(currentCoordinates.x, currentCoordinates.y - 1);

		Cell *forwardCell = m_room->getCell(forwardCoordinate),
			*currentCell = m_room->getCell(currentCoordinates),
			*backwardCell = m_room->getCell(backwardCoordinate),
			*leftCell = m_room->getCell(leftCoordinate),
			*rightCell = m_room->getCell(rightCoordinate);

		if (currentCell->special == 'p')
		{
			path += "p";
			tree.insert(path.c_str());
		}

		//----------- (Forward) ------------
		if (checkDirection(forwardCoordinate, forwardCell, currentCell, "f", tree, path))
		{
			continue;
		}
		//----------- (Backward) ------------
		if (checkDirection(backwardCoordinate, backwardCell, currentCell, "b", tree, path))
		{
			continue;
		}
		//----------- (Left) ------------
		if (checkDirection(leftCoordinate, leftCell, currentCell, "l", tree, path))
		{
			continue;
		}
		//----------- (Right) ------------
		if (checkDirection(rightCoordinate, rightCell, currentCell, "r", tree, path))
		{
			continue;
		}

	}
	//tree.print();
}

bool ShortestRoot::checkDirection(Coordinates& coordinate, Cell*& cell, Cell*& currentCell, string charAddToPath, TreeShortRoot& tree, string& path)
{
	if (isValid(coordinate) && isNotFurniture(cell))
	{
		if (isDestination(coordinate))
		{
			cell->parent = currentCell;
			path += charAddToPath;
			tree.insert(path.c_str());
			return true;
		}
		else if (!m_closedList[coordinate.x][coordinate.y])
		{
			double gNew = currentCell->g + 1.0;
			double hNew = calculateHValue(coordinate);
			double fNew = gNew + hNew;

			if (currentCell->f == FLT_MAX || currentCell->f >= fNew || coordinate.x != currentCell->parent->coordinates.x || coordinate.y != currentCell->parent->coordinates.y)
			{
				path += charAddToPath;
				tree.insert(path.c_str());
				CoordinatesWithPath cwp(coordinate, path);
				m_openList.push(cwp);
				cell->update(hNew, gNew, fNew, currentCell);
			}
		}
	}
	return false;
}