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