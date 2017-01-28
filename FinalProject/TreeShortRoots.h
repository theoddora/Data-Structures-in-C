#pragma once
#include <string>
#include <iostream>
#include <cstring>
using namespace std;
struct Node
{
	char* data;
	Node* children[5];

	Node(const char* input) : data(nullptr)
	{
		data = new char[strlen(input) + 1];
		strcpy_s(data, strlen(input) + 1, input);
		for (size_t i = 0; i < 5; ++i)
		{
			children[i] = nullptr;
		}
	}
	Node& operator= (const Node& rhs)
	{
		data = new char[strlen(rhs.data) + 1];
		strcpy_s(data, strlen(rhs.data) + 1, rhs.data);
		for (size_t i = 0; i < 5; ++i)
		{
			children[i] = rhs.children[i];
		}
		return *this;
	}
};
class TreeShortRoot
{
private:
	Node* root;
	void insert(Node* root, const char*);
	void print(Node* root);
public:
	TreeShortRoot();
	void insert(const char* path);
	void print();
};