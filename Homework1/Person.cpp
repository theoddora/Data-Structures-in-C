#include <iostream>
#include <cassert>
#include "Person.h"

//big 4
Person::Person(int id, int numberOfPhoneNumbers) : index(0), capacity(numberOfPhoneNumbers), m_id(id), connections(0)
{
	phoneNumbers = nullptr;
	phoneNumbers = new int[capacity];
}

Person::~Person()
{
	deletePerson();
}

Person::Person(const Person& other)
{
	copy(other);
}

Person& Person::operator=(const Person& other)
{
	if (this != &other)
	{
		deletePerson();
		copy(other);
	}
	return *this;
}

//add
void Person::addNumber(int idOfPerson)
{
	phoneNumbers[index++] = idOfPerson;
}

//getters
int Person::getID() const
{
	return this->m_id;
}

int Person::getIndex() const
{
	return this->index;
}

int Person::getCapacity() const
{
	return this->capacity;
}

int Person::getPhoneNumber(int i) const
{
	assert(i >= 0 && i < capacity);
	return phoneNumbers[i];
}

int* Person::getPhoneNumbers()
{
	return phoneNumbers;
}

int Person::getConnections()
{
	return this->connections;
}

//helper methods
void Person::copy(const Person& other)
{
	capacity = other.getCapacity();
	m_id = other.getID();
	phoneNumbers = nullptr;
	phoneNumbers = new int[capacity];
	for (int i = 0; i < other.getIndex(); ++i, ++index)
	{
		addNumber(other.getPhoneNumber(i));
	}
}

void Person::deletePerson()
{
	delete[] phoneNumbers;
}

void Person::setConnections(int connections)
{
	this->connections = connections;
}

void Person::print() const
{
	std::cout << "id " << this->getID() << std::endl;
	std::cout << "telephone numbers of people: " << std::endl;
	for (int i = 0; i < index; i++)
	{
		std::cout << "\t" << this->phoneNumbers[i] << ", ";
	}
	std::cout << std::endl;
}