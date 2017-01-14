#pragma once
#include <float.h>
#include <string>
#include <iostream>
using namespace std;

//a pair of coordinates
struct Coordinates
{
	int x, y;
	Coordinates(int i = 0, int j = 0) : x(i), y(j) {}
	Coordinates(const Coordinates& coordinates) : x(coordinates.x), y(coordinates.y) {}
};

//a pair of coordinates with path - we need this for the open-list
struct CoordinatesWithPath
{
	Coordinates coordinates;
	string path;
	CoordinatesWithPath(Coordinates& coordinates, string m_path = "") : coordinates(coordinates), path(m_path) {}
};

//a cell in the room
struct Cell
{
	char special = '_';
	double h = FLT_MAX, g = FLT_MAX, f = FLT_MAX;
	Cell* parent = nullptr;
	Coordinates coordinates;

	void update(double h, double g, double f, Cell* parent);

	~Cell()
	{
		delete parent;
	}
};

class Room
{
private:
	Cell** m_room;
	Coordinates m_roomSize, m_tom, m_jerry;
	void makeRoom(Coordinates);
	Coordinates getCoordinates(char*);
	void placeJerryAndTom(Coordinates, Coordinates);

public:
	Room(const char* textFile);
	~Room();

	//getters
	Coordinates getTomCoordinate() const;
	Coordinates getJerryCoordinates() const;
	Coordinates getRoomCoordinates() const;
	Cell* getCell(Coordinates coordinates);

	void loadRoom(const char* textFile);
	void print();
};