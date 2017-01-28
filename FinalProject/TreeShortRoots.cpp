#include "TreeShortRoots.h"
#include <string>
#include <iostream>
#include <cstring>
using namespace std;
TreeShortRoot::TreeShortRoot()
{
	root = nullptr;
}

void TreeShortRoot::insert(const char* path)
{
	if (strcmp(path, "start") == 0)
	{
		Node* node = new Node("start");
		root = node;
		return;
	}

	Node* currentRoot = root;
	char character = path[0];
	switch (character)
	{
	case 'f':insert(currentRoot->children[0], path); break;
	case 'b':currentRoot = currentRoot->children[1]; break;
	case 'l':currentRoot = currentRoot->children[2]; break;
	case 'r':currentRoot = currentRoot->children[3]; break;
	case 'p':currentRoot = currentRoot->children[4]; break;
	}
}

void TreeShortRoot::print()
{
	print(root);
}

void TreeShortRoot::print(Node* currentRoot)
{
	if (currentRoot == nullptr)
	{
		return;
	}
	cout << currentRoot->data << endl;
	for (size_t i = 0; i < 5; ++i)
	{
		print(currentRoot->children[i]);
	}
}

void TreeShortRoot::insert(Node* currentRoot, const char* path)
{
	if (currentRoot == NULL)
	{
		currentRoot = new Node(path);
		return;
	}
	int size = strlen(path) + 1, index = 0;
	for (size_t i = 1; i < size; ++i)
	{
		char character = path[i];
		switch (character)
		{
		case 'f':currentRoot = currentRoot->children[0]; index = 0; break;
		case 'b':currentRoot = currentRoot->children[1]; index = 1; break;
		case 'l':currentRoot = currentRoot->children[2]; index = 2; break;
		case 'r':currentRoot = currentRoot->children[3]; index = 3; break;
		case 'p':currentRoot = currentRoot->children[4]; index = 4; break;
		}
	}
	char character = path[0];
	Node* node = new Node(path);
	currentRoot = node;
}
