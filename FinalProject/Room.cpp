#include "Room.h"
#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

//cell
void Cell::update(double h, double g, double f, Cell* parent)
{
	this->h = h;
	this->g = g;
	this->f = f;
	this->parent = parent;
}

//constructor and destructor
Room::Room(const char* textFile)
{
	m_roomSize.x = 0;
	m_roomSize.y = 0;
	m_room = nullptr;
	loadRoom(textFile);
}

Room::~Room()
{
	delete[] m_room;
}

//getters
Coordinates Room::getRoomCoordinates() const
{
	return m_roomSize;
}

Coordinates Room::getTomCoordinate() const
{
	return m_tom;
}

Coordinates Room::getJerryCoordinates() const
{
	return m_jerry;
}

Cell* Room::getCell(Coordinates coordinates)
{
	return &m_room[coordinates.x][coordinates.y];
}

//public functions
void Room::loadRoom(const char * textFile)
{
	char* line = new char[1024];
	ifstream file;

	file.open(textFile);
	file.getline(line, 1024);

	Coordinates coordinatesRoom = getCoordinates(line);
	file.getline(line, 1024);
	Coordinates coordinatesJerry = getCoordinates(line);
	file.getline(line, 1024);
	Coordinates coordinatesTom = getCoordinates(line);
	file.getline(line, 1024);
	Coordinates misc = getCoordinates(line);

	makeRoom(coordinatesRoom);
	placeJerryAndTom(coordinatesTom, coordinatesJerry);

	//place furniture
	Coordinates coordinatesFurniture;
	for (size_t i = 0; i < misc.x; ++i)
	{
		//'c' = cupboard
		file.getline(line, 1024);
		coordinatesFurniture = getCoordinates(line);
		int startingPointOfFurnitureX = coordinatesFurniture.x, startingPointOfFurnitureY = coordinatesFurniture.y;

		while (true)
		{
			file.getline(line, 1024);
			if (strcmp(line, "===") == 0)
				break;
			for (int i = 0; line[i] == '1' || line[i] == ' '; ++i)
			{
				if (line[i] == '1')
				{
					m_room[startingPointOfFurnitureX][startingPointOfFurnitureY].special = 'c';
				}
				startingPointOfFurnitureY++;
			}
			startingPointOfFurnitureX++;
			startingPointOfFurnitureY = coordinatesFurniture.y;
		}
	}

	Coordinates coordinatesPaint;
	for (size_t i = 0; i < misc.y; ++i)
	{
		file.getline(line, 1024);
		coordinatesPaint = getCoordinates(line);
		m_room[coordinatesPaint.x][coordinatesPaint.y].special = 'p';
	}
	file.close();
	delete[] line;
}

void Room::print()
{
	for (size_t i = 0; i < m_roomSize.x; i++)
	{
		for (size_t j = 0; j < m_roomSize.y; j++)
		{
			cout << m_room[i][j].special << " ";
		}
		cout << endl;
	}
}

//private functions
void Room::makeRoom(Coordinates coordinates)
{
	this->m_roomSize = coordinates;

	this->m_room = new Cell*[m_roomSize.x];
	for (size_t i = 0; i < m_roomSize.x; ++i)
	{
		m_room[i] = new Cell[m_roomSize.y];
	}

	for (size_t i = 0; i < m_roomSize.x; i++)
	{
		for (size_t j = 0; j < m_roomSize.y; j++)
		{
			Coordinates coord(i, j);
			m_room[i][j].coordinates = coord;
		}
	}
}

Coordinates Room::getCoordinates(char* line)
{
	char* token, *otherPart;
	Coordinates coordinates;
	token = strtok_s(line, " ", &otherPart);
	coordinates.x = atoi(token);
	token = strtok_s(nullptr, " ", &otherPart);
	coordinates.y = atoi(token);
	return coordinates;
}

void Room::placeJerryAndTom(Coordinates tom, Coordinates jerry)
{
	//tom
	m_tom = tom;
	m_room[tom.x][tom.y].special = 't';
	m_room[tom.x][tom.y].update(0.0, 0.0, 0.0, &m_room[tom.x][tom.y]);

	//jerry
	m_jerry = jerry;
	m_room[jerry.x][jerry.y].special = 'j';
}