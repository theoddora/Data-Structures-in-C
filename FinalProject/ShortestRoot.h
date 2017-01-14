#pragma once
#include "Room.h"
#include <stack>
#include <float.h>
#include "TreeShortRoots.h"

class ShortestRoot
{
private:
	Room* m_room;

	Coordinates m_tom;
	Coordinates m_jerry;
	Coordinates m_roomSize;

	bool** m_closedList;
	stack<CoordinatesWithPath> m_openList;
	TreeShortRoot tree;

	bool isDestination(Coordinates);
	void makeRoom(Coordinates);
	bool isValid(Coordinates);
	bool isNotFurniture(Cell*);
	double calculateHValue(Coordinates);

	bool ShortestRoot::checkDirection(Coordinates& coordinate, Cell*& cell, Cell*& currentCell, string charAddToPath, TreeShortRoot& tree, string& path);

public:

	ShortestRoot(Room* room);
	~ShortestRoot();

	void findPath();
};