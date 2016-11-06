#include "Item.h"

using namespace std;

Item::Item(string name, string desc) : _name(name), _desc(desc) {
}
Item::Item(string name) : Item(name, "") {
}
Item::Item() : Item("") {
}
string Item::name() const {
	return _name;
}
string Item::desc() const {
	return _desc;
}
bool Item::operator ==(const Item& other) const {
	return _name == other._name;
}
bool Item::operator !=(const Item& other) const {
	return !(*this == other);
}


