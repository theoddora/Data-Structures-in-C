#include <iostream>
#include <cassert>
#include <queue>
#include "Person.h"

int findNumberOfCalls(Person*&, int, int, int);
bool contains(int, int*&, int);

int main()
{
	int numberOfPeople = 0;
	int numberOfPhoneNumbers = 0;
	int index = 0;
	int idCaller = 0;
	int idReciever = 0;
	std::cout << "Number of people: ";
	std::cin >> numberOfPeople;
	assert(numberOfPeople > 0);
	Person* people = new Person[numberOfPeople];
	for (int i = 0; i < numberOfPeople; ++i)
	{
		index = i;
		std::cout << "Number of phone numbers of person " << index << " : ";
		std::cin >> numberOfPhoneNumbers;
		assert(numberOfPhoneNumbers > 0 && numberOfPhoneNumbers < numberOfPeople);
		Person* p = new Person(index, numberOfPhoneNumbers);
		people[index] = *p;
		delete p;
		int inputID = 0;
		for (int i = 0; i < numberOfPhoneNumbers; i++)
		{
			std::cout << "id: ";
			std::cin >> inputID;
			assert(inputID != index && inputID < numberOfPeople);
			people[index].addNumber(inputID);
		}
	}
	std::cout << std::endl << std::endl;
	for (int i = 0; i < numberOfPeople; i++)
	{
		people[i].print();
	}
	std::cout << std::endl << std::endl;

	std::cout << "Number of caller: ";
	std::cin >> idCaller;
	assert(idCaller >= 0 && idCaller < numberOfPeople);
	std::cout << "Number of reciever: ";
	std::cin >> idReciever;
	assert(idReciever >= 0 && idReciever < numberOfPeople && idReciever != idCaller);

	int hasPath = findNumberOfCalls(people, idCaller, idReciever, numberOfPeople);
	std::cout << std::endl << "Number of calls: " << hasPath << std::endl;

	return 0;
}


int findNumberOfCalls(Person*& people, int idCaller, int idReciever, int numberOfPeople)
{
	std::queue<int> currentPeople;
	//helper array for all used ids in queue
	int* usedIDs = new int[numberOfPeople];
	int indexUsedIDs = 0;

	currentPeople.push(idCaller);
	people[idCaller].setConnections(0);
	usedIDs[indexUsedIDs++] = idCaller;

	while (true)
	{
		for (int i = 0; i < people[currentPeople.front()].getCapacity(); ++i)
		{
			if (!contains(people[currentPeople.front()].getPhoneNumber(i), usedIDs, indexUsedIDs))
			{
				if (people[currentPeople.front()].getPhoneNumber(i) == idReciever)
				{
					return 1 + people[currentPeople.front()].getConnections();
				}
				currentPeople.push(people[currentPeople.front()].getPhoneNumber(i));
				usedIDs[indexUsedIDs++] = people[currentPeople.front()].getPhoneNumber(i);
				people[people[currentPeople.front()].getPhoneNumber(i)].setConnections(people[currentPeople.front()].getConnections() + 1);
			}
		}
		currentPeople.pop();
		if (currentPeople.empty())
		{
			return -1;
		}
	}
}

bool contains(int id, int*& usedIDs, int indexUsedIDs)
{
	for (int i = 0; i < indexUsedIDs; ++i) {
		if (id == usedIDs[i])
		{
			return true;
		}
	}
	return false;
}