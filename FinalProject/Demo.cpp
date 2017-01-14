#include <iostream>
#include "Room.h"
#include "ShortestRoot.h"
using namespace std;

int main()
{
	/** legend:
	f = forward
	b = backward
	l = left
	r = right
	c = cupboard  (furniture)
	p = paint
	*/


	char* document = "document.txt";
	Room room(document);
	room.print();
	// ShortestRoot shortestRoot(&room);
	// shortestRoot.findPath();
	TreeShortRoot tree;
	tree.insert("start");
	tree.insert("f");
	tree.print();
	system("pause");
	return 0;
}