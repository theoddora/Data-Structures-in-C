#include <iostream>
#include <assert.h>
#include <string.h>
#include <fstream>
#include <algorithm>
#include <stack>
#include <queue>
using namespace std;

template <class T>
struct Node
{
	Node<T> *left, *right;
	T data;
	Node(const T& d, Node<T> *l, Node<T> *r) : left(l), right(r), data(d) {}
	Node() :left(NULL), right(NULL) {}
};

template <class T>
class BTree
{
private:
	Node<T>* root;
	void simplePrint(Node<T> *subTreeRoot) const;
	bool add(const T& data, const char *trace, Node<T>*&);
	void deleteAll(Node<T> *subTreeRoot);

	//homework
	int height(Node<T>*);
	int max(int, int);
	int diameter(Node<T>*);


	//EXAM
	void isMirrorRLR(stack<T>& stack, Node<T>* currentRoot);
	void isMirrorRRL(stack<T>& stack, Node<T>* currentRoot);
	void rotateBTree(Node<T>* currentRoot);


public:
	BTree();
	BTree<T>& add(const T& data, const char* trace);
	void simplePrint() const;
	~BTree();

	//Homework
	bool find(const T& x);
	bool deleteElement(const T& x);
	Node<T>* minElement(Node<T>*);
	void insertBOT(const T& x);
	int diameter();
	void printColumns() const;
	bool isMirror();

	BTree<T>& rotateBTree();
};

template<class T>
void BTree<T>::deleteAll(Node<T> *subTreeRoot)
{
	if (subTreeRoot == NULL)
		return;
	deleteAll(subTreeRoot->left);
	deleteAll(subTreeRoot->right);
	delete subTreeRoot;
}

template <class T>
BTree<T>::~BTree()
{
	deleteAll(root);
	root = NULL;
}


template <class T>
BTree<T>& BTree<T>::add(const T& x, const char *trace)
{
	add(x, trace, root);
	return *this;
}

template <class T>
bool BTree<T>::add(const T& x, const char *trace, Node<T>* &subTreeRoot)
{
	if (subTreeRoot == NULL)
	{
		assert(strlen(trace) == 0);
		subTreeRoot = new Node<T>(x, NULL, NULL);
		return true;
	}
	assert(strlen(trace) > 0);
	if (trace[0] == 'L')
		return add(x, trace + 1, subTreeRoot->left);
	assert(trace[0] == 'R');
	return add(x, trace + 1, subTreeRoot->right);
	return true;
}

template <class T>
BTree<T>::BTree() :root(NULL) {}

template <class T>
void BTree<T>::simplePrint() const
{
	simplePrint(root);
	cout << endl;
}

template <class T>
void BTree<T>::simplePrint(Node<T> *subTreeRoot) const
{
	if (subTreeRoot == NULL)
		return;
	simplePrint(subTreeRoot->left);
	cout << subTreeRoot->data << " ";
	simplePrint(subTreeRoot->right);
}

//homework
template<class T>
bool BTree<T>::find(const T & x)
{
	Node<T>* currentRoot = root;
	bool found = false;
	while (currentRoot != NULL && !found)
	{
		if (currentRoot->data == x)
		{
			found = true;
			break;
		}
		if (currentRoot->data > x)
		{
			currentRoot = currentRoot->left;
		}
		if (currentRoot->data < x)
		{
			currentRoot = currentRoot->right;
		}
	}
	return found;
}

template<class T>
Node<T>* BTree<T>::minElement(Node<T>* current)
{
	while (current->left != NULL)
	{
		current = current->left;
	}
	return current;
}

template<class T>
bool BTree<T>::deleteElement(const T& x)
{
	Node<T>* parent = NULL;
	Node<T>* currentRoot = root;
	bool foundElement = false;

	while (currentRoot != NULL)
	{
		if (x < currentRoot->data)
		{
			parent = currentRoot;
			currentRoot = currentRoot->left;
			continue;
		}
		if (x > currentRoot->data)
		{
			parent = currentRoot;
			currentRoot = currentRoot->right;
			continue;
		}

		foundElement = true;
		//leaf
		if (currentRoot->right == NULL && currentRoot->left == NULL)
		{
			if (parent->left == currentRoot)
			{
				parent->left = NULL;
			}
			else
			{
				parent->right = NULL;
			}
			delete currentRoot;
			return foundElement;
		}

		//middle
		if (currentRoot != NULL && currentRoot->right == NULL)
		{
			Node<T>* temp = currentRoot;
			if (parent->left == currentRoot)
			{
				parent->left = currentRoot->left;
			}
			else
			{
				parent->right = currentRoot->left;
			}
			delete temp;
			return foundElement;
		}
		if (currentRoot != NULL && currentRoot->left == NULL)
		{
			Node<T>* temp = currentRoot;
			if (parent->left == currentRoot)
			{
				parent->left = currentRoot->right;
			}
			else
			{
				parent->right = currentRoot->right;
			}
			delete temp;
			return foundElement;
		}
		if (currentRoot == NULL)
		{
			break;
		}
		Node<T>* minElem = minElement(currentRoot->right);
		currentRoot->data = minElem->data;
	}
	return foundElement;
}


template<class T>
void BTree<T>::insertBOT(const T& x)
{
	if (root == NULL)
	{
		root = new Node<T>(x, NULL, NULL);
		return;
	}
	Node<T>* currentRoot = root;
	while (currentRoot != NULL)
	{
		if (x <= currentRoot->data)
		{
			if (currentRoot->left == NULL)
			{
				currentRoot->left = new Node<T>(x, NULL, NULL);
				return;
			}
			currentRoot = currentRoot->left;
		}
		else if (x > currentRoot->data)
		{
			if (currentRoot->right == NULL)
			{
				currentRoot->right = new Node<T>(x, NULL, NULL);
				return;
			}
			currentRoot = currentRoot->right;
		}
	}
}

template<class T>
int BTree<T>::diameter()
{
	return diameter(root);
}

//sorry for big complexity :(
template<class T>
void BTree<T>::printColumns() const
{
	Node<T>* currentRoot = root;
	if (root == NULL)
	{
		return;
	}
	// stack with only left elements from looking at root (not all left elements of each node but only left of root element)
	stack<Node<T>*> left;
	// queue with only right elements from looking at root (not all right elements of each node but only right of root element)
	queue<Node<T>*> right;
	cout << "stack push" << endl;
	while (currentRoot != NULL)
	{
		left.push(currentRoot);
		currentRoot = currentRoot->left;
	}
	currentRoot = root->right;
	cout << "queue push" << endl;
	while (currentRoot != NULL)
	{
		right.push(currentRoot);
		currentRoot = currentRoot->right;
	}

	while (!left.empty())
	{
		//get element from stack of left elements
		Node<T>* element = left.top();
		cout << element->data << " ";
		int counter = 1;
		//logic for left
		Node<T>* elementLeft = element->left;
		//logic for right
		Node<T>* elemRight = element->right;
		while (elementLeft != NULL || elemRight != NULL)
		{
			//left logic
			Node<T>* elementRight = elementLeft;
			//right logic
			Node<T>* elemLeft = elemRight;
			for (size_t i = 0; elementRight != NULL && i < counter; i++)
			{
				elementRight = elementRight->right;
				//logic is for existing nodes of type left->right, left->left->right->right, left->left->left->right->right->right etc
			}
			for (size_t i = 0; elemLeft != NULL && i < counter; i++)
			{
				elemLeft = elemLeft->left;
				//logic is for existing nodes of type right->left, right->right->left->left, right->right->right->left->left->left etc
			}
			if (elementRight != NULL)
			{
				cout << elementRight->data << " ";
			}
			if (elemLeft != NULL)
			{
				cout << elemLeft->data << " ";
			}
			counter++;
			if (elementLeft != NULL)
			{
				elementLeft = elementLeft->left;
			}
			if (elemRight != NULL)
			{
				elemRight = elemRight->right;
			}
		}
		left.pop();
		cout << endl;
		counter = 1; // for the next element the for() to start again
	}

	//sorry for repeating code :(
	while (!right.empty())
	{
		Node<T>* element = right.front();
		cout << element->data << " ";
		int counter = 1;
		//logic for left
		Node<T>* elementLeft = element->left;
		//logic for right
		Node<T>* elemRight = element->right;
		while (elementLeft != NULL || elemRight != NULL)
		{
			//left logic
			Node<T>* elementRight = elementLeft;
			//right logic
			Node<T>* elemLeft = elemRight;
			for (size_t i = 0; elementRight != NULL && i < counter; i++)
			{
				elementRight = elementRight->right;
			}
			for (size_t i = 0; elemLeft != NULL && i < counter; i++)
			{
				elemLeft = elemLeft->left;
			}
			if (elemLeft != NULL)
			{
				cout << elemLeft->data << " ";
			}
			counter++;
			if (elementLeft != NULL)
			{
				elementLeft = elementLeft->left;
			}
			if (elemRight != NULL)
			{
				elemRight = elemRight->right;
			}
		}
		right.pop();
		cout << endl;
		counter = 1;
	}
}



template<class T>
int BTree<T>::height(Node<T>* currentRoot)
{
	if (currentRoot == NULL)
	{
		return 0;
	}
	int leftHeight = 1 + height(currentRoot->left);
	int rightHeight = 1 + height(currentRoot->right);
	return 1 + max(height(currentRoot->left), height(currentRoot->right));
}

template<class T>
int BTree<T>::max(int a, int b)
{
	return a > b ? a : b;
}

template<class T>
int BTree<T>::diameter(Node<T>* currentRoot)
{
	if (currentRoot == NULL)
	{
		return 0;
	}
	int leftHeight = height(currentRoot->left);
	int rightHeight = height(currentRoot->right);
	int leftDiameter = diameter(currentRoot->left);
	int rightDiameter = diameter(currentRoot->right);
	return max((leftHeight + rightHeight + 1), max(leftDiameter, rightDiameter));
}




//EXAM
//problem1
template<class T>
void BTree<T>::isMirrorRLR(stack<T>& stack, Node<T>* currentRoot)
{
	if (currentRoot == NULL)
	{
		return;
	}
	if (currentRoot == root)
	{
		return;
	}
	stack.push(currentRoot->data);
	isMirrorRLR(stack, currentRoot->left);
	isMirrorRLR(stack, currentRoot->right);
}

template<class T>
void BTree<T>::isMirrorRRL(stack<T>& stack, Node<T>* currentRoot)
{
	if (currentRoot == NULL)
	{
		return;
	}
	if (currentRoot == root)
	{
		return;
	}
	stack.push(currentRoot->data);
	isMirrorRRL(stack, currentRoot->right);
	isMirrorRRL(stack, currentRoot->left);
}

template<class T>
bool BTree<T>::isMirror()
{
	if (root == NULL)
	{
		return false;
	}
	stack<T> leftSubTree;
	stack<T> rightSubTree;

	isMirrorRLR(leftSubTree, root->left);
	isMirrorRRL(rightSubTree, root->right);

	while (!leftSubTree.empty())
	{
		if (leftSubTree.top() != rightSubTree.top())
		{
			return false;
		}
		leftSubTree.pop();
		rightSubTree.pop();
	}
	return rightSubTree.empty();
}

//bonus
template<class T>
BTree<T>& BTree<T>::rotateBTree()
{
	if (root == NULL)
	{
		return *this;
	}
	rotateBTree(root);
	return *this;
}

template<class T>
void BTree<T>::rotateBTree(Node<T>* currentRoot)
{
	if (currentRoot == NULL)
	{
		return;
	}
	Node<T>* temp = currentRoot->left;
	currentRoot->left = currentRoot->right;
	currentRoot->right = temp;

	rotateBTree(currentRoot->left);
	rotateBTree(currentRoot->right);
}

//problem 2
struct Nodee {
	int data;
	Nodee* next;
};

Nodee* rotate(Nodee* node, int pivot)
{
	Nodee* startNode = node; // <- not to lose it
	//before pivot
	queue<int> before;
	//after pivot
	queue<int> after;
	bool pivotFound = false; //if they give us a wrong pivot
	
	while (node->next != nullptr)
	{
		if (node->next->data == pivot)
		{
			pivotFound = true;
			break;
		}
		before.push(node->next->data);
		node = node->next;
	}
	while (node->next != nullptr)
	{
		after.push(node->next->data);
		node = node->next;
	}
	
	Nodee* start = startNode;
	//now rotate
	while (!before.empty())
	{
		startNode->next->data = before.front();
		startNode = startNode->next;
		before.pop();
	}
	if (pivotFound)
	{
		//assert would be good here :D
		startNode->next->data = pivot;
		startNode = startNode->next;
	}
	while (!after.empty())
	{
		startNode->next->data = after.front();
		startNode = startNode->next;
		after.pop();
	}
	return start;
}


//problem 0
#define MAX 10
class Circular_Queue
{
private:
	int* cqueue_arr;
	int currentNumber;
public:
	Circular_Queue(int currentNumber)
	{
		cqueue_arr = new int[MAX];
		for (int i = 0, digit = 9; i < MAX; i++, digit--)
		{
			cqueue_arr[i] = digit;
		}
	}
	int prevDigit()
	{
		return (this->currentNumber - 1) % 10;
	}

	int nextDigit()
	{
		return (this->currentNumber + 1) % 10;
	}
	int currentDigit()
	{
		return this->currentNumber;
	}
};

int calcSecondsToOpenSafe(int input[5], int output[5], int n, int** forbiddenCombinations)
{
	int seconds = 0;
	Circular_Queue digitOne(*input);
	Circular_Queue digitTwo(*(input + 1));
	Circular_Queue digitThee(*(input + 2));
	Circular_Queue digitFour(*(input + 3));
	Circular_Queue digitFive(*(input + 4));

	while (digitOne.currentDigit() != *output)
	{
		if (digitOne.currentDigit() < *output)
		{
			digitOne.nextDigit();
		}
		else
		{
			digitOne.prevDigit();
		}
		seconds++;
	}


	while (digitTwo.currentDigit() != *(output+1))
	{
		if (digitTwo.currentDigit() < *output)
		{
			digitTwo.nextDigit();
		}
		else
		{
			digitTwo.prevDigit();
		}
		seconds++;
	}

	while (digitThee.currentDigit() != *(output + 2))
	{
		if (digitThee.currentDigit() < *output)
		{
			digitThee.nextDigit();
		}
		else
		{
			digitThee.prevDigit();
		}
		seconds++;
	}

	while (digitFour.currentDigit() != *(output + 3))
	{
		if (digitFour.currentDigit() < *output)
		{
			digitFour.nextDigit();
		}
		else
		{
			digitFour.prevDigit();
		}
		seconds++;
	}

	while (digitFive.currentDigit() != *(output + 4))
	{
		if (digitFive.currentDigit() < *output)
		{
			digitFive.nextDigit();
			//check forbidden
		}
		else
		{
			digitFive.prevDigit();
		}
		seconds++;
	}

	return seconds;
}

bool forbiddenCombinations(int numberToCheck, int n, int** forbiddenCombinations)
{
	return true;
}


int main()
{
	BTree<int> t;

	t.add(20, "")
		.add(15, "L")
		.add(13, "LL")
		.add(12, "LLL")
		.add(14, "LLR")
		.add(17, "LR")
		.add(16, "LRL")
		.add(18, "LRR")
		.add(21, "R")
		.add(22, "RR")
		.add(23, "RRR")
		.add(24, "RRRR");
	t.simplePrint();
	cout << "****************" << endl;
	cout << "Test diameter: " << boolalpha << t.find(16) << endl;
	cout << "diameter():" << endl;
	cout << t.diameter() << endl;
	cout << "find            " << boolalpha << t.find(16) << endl;
	cout << "****************" << endl;
	cout << "delete leaf     " << boolalpha << t.deleteElement(12) << endl;
	cout << "delete leaf     " << boolalpha << t.deleteElement(24) << endl;
	cout << "delete not leaf " << boolalpha << t.deleteElement(21) << endl;
	t.simplePrint();
	cout << "****************" << endl;
	BTree<int> tree;
	tree.insertBOT(20);
	tree.insertBOT(15);
	tree.insertBOT(13);
	tree.insertBOT(14);
	tree.insertBOT(17);
	tree.insertBOT(16);
	tree.insertBOT(18);
	tree.insertBOT(22);
	tree.insertBOT(23);
	cout << "test insertBOT():" << endl;
	t.simplePrint();
	tree.simplePrint();
	cout << "****************" << endl;
	cout << "diameter():" << endl;
	cout << t.diameter() << endl;
	cout << tree.diameter() << endl;
	cout << "****************" << endl;
	tree.printColumns();
	

	cout << "****************" << endl;
	BTree<int> tr;

	tr.add(3, "")
		.add(1, "L")
		.add(0, "LL")
		.add(3, "LLL")
		.add(2, "LR")
		.add(4, "LRR")
		.add(1, "R")
		.add(0, "RR")
		.add(3, "RRR")
		.add(2, "RL")
		.add(4, "RLL");
	cout << "****************" << endl;
	cout << boolalpha << tr.isMirror() << endl;
	cout << "****************" << endl;
	t.simplePrint();
	t.rotateBTree().simplePrint();

	system("pause");
	return 0;
}