#include "StateController.h"
//#include "CommandReader.h"

using namespace std;

int main() {
	StateController controller;
	controller();
	return 0;
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