#include "StateController.h"
//#include "CommandReader.h"
#include "World.h"
#include "WorldReader.h"
#include "WorldCreator.h"

/*
TODO:
	Populate world with more items
	Test that things still work with those items
	Put an item inside an item
	Add commands for doing this (look in x, take x from y, put x in y)
		This means command regex support for "skip some args"
	Test that that works
	Write spike report
TESTS:
	Verify item on floor
	Pick up item
	Verify item in inv
	Drop item
	Veryfy item on floor
	Pick up item
	Move to another room
	Drop item
	Verify item in correct room and not duplicated
	Pick up two items at once
	Verify items in inv
	Drop one item
	Verify item on floor
	Move to another room
	Drop other item
	Verify item on floor
	Pick up 2 items
	Clear inventory
	Verify both items on floor
*/

using namespace std;

int main() {
//	/*
	StateController controller;
	controller();
	return 0;
//	*/
	/*
	WorldReader r("default - Copy.world");
	World* w = r.read();
	WorldCreator c("default2");
	c.load(*w);
//	Item& i = Item::create(0,"test item","test desc",const_cast<Room&>(w->room(0)));
//	c.push_item(i);
	Item& i1 = Item::create(0,"Plush 4","A little plush toy shaped like the number 4.",const_cast<Room&>(w->room(2)));
	Item& i2 = Item::create(1,"Discarded Cigarette","The remains of a once-great cigarette, now burned down to a mere husk of its former self.\nThat's a lie. It was never that great to begin with.",const_cast<Room&>(w->room(5)));
	Item& i3 = Item::create(2,"Rocket Science for Dummies","A textbook claiming to be able to teach you rocket science in only 300 pages.\nThe book's font is too small to read.",const_cast<Room&>(w->room(5)));
	Item& i4 = Item::create(3,"Handbag","Allows you to hold lots of things at once by abstracting away their shapes.",const_cast<Room&>(w->room(0)));
	Item& i5 = Item::create(4,"Tiny Man","Eh??? Why do I have a tiny man?",i4);
	c.push_item(i1);
	c.push_item(i2);
	c.push_item(i3);
	c.push_item(i4);
	c.push_item(i5);
	c.flush();
	cin.ignore();
	*/
	/*
	CommandReader r;
	set<string> ids;
	ids.insert("look");
	ids.insert("go");
	ids.insert("quit");
	ids.insert("inv");
	ids.insert("invAdd");
	ids.insert("invRemove");
	ids.insert("invRemoveAll");
	ids.insert("invCount");
	ids.insert("invList");
	ids.insert("invClear");
	ids.insert("invBack");
	ids.insert("hiscore");
	list<string> l = r.read("aliases.txt",ids);
	cout << "size -> " << l.size() << endl;
	int line = 0;
	for (list<string>::const_iterator i = l.cbegin(); i != l.cend(); ++i) {
		cout << "line " << ++line << " -> " << *i << endl;
	}
	cin.ignore();
	return 0;
	*/
}