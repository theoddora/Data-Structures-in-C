#pragma once
class Person {
public:
	Person(int = 0, int = 0);
	~Person();
	Person(const Person&);
	Person& operator = (const Person&);
	void addNumber(int);

	//getters
	int getID() const;
	int getIndex() const;
	int getCapacity() const;
	int getPhoneNumber(const int) const;
	int* getPhoneNumbers();
	int getConnections();

	//setters
	void setConnections(int connections);

	void print() const;

private:
	int index;
	int capacity;
	int m_id;
	int* phoneNumbers;
	int connections;

	void copy(const Person&);
	void deletePerson();
};