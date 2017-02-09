#pragma once
#include <stack>
using namespace std;

template <class T>
class BTree
{
private:
	//Възел на дървото
	struct Node
	{
		Node *left, *right;
		T data;
		Node(const T& d, Node *l, Node *r);
		Node();
		int getID() const;
	private:
		int id;
		void makeID();
	};

private:
	Node *root;
	bool add(const T& data, const char *trace, Node*&);
	void deleteAll(Node *subTreeRoot);
	void dottyPrint(Node *subTreeRoot, ostream& out) const;
	static Node* copyTree(const Node *subTreeRoot);
	void insertBOT(Node*&subTreeRoot, const T& x);
	void deleteElement(Node *&subTreeRoot, const T&x);
	T minelement(Node *subTreeRoot) const;
	bool member(const T& x, BTree<T>::Node *subTreeRoot) const;

public:
	BTree();
	BTree(const BTree<T> &other);

	BTree<T>& operator = (const BTree<T> &other);

	BTree<T>& add(const T& data, const char *trace);

	void deleteElement(const T&x);

	void dottyPrint(ostream&);

	bool member(const T&) const;

	BTree<T>& insertBOT(const T& x);

	T minelement()const;

	~BTree();

	//homework

	bool find(const T&);

};