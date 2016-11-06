#include "Inventory.h"
//#include <iostream>

using namespace std;

IInventory::ContainerMap IInventory::_CONTAINER_MAP;

bool IInventory::ContainerMap::contains_item(const Item* item) const {
	return _ITEM_TO_CONTAINER_MAP.find(const_cast<Item*>(item)) != _ITEM_TO_CONTAINER_MAP.end();
}
bool IInventory::ContainerMap::contains_container(const IHasInventory* container) const {
	return _CONTAINER_TO_ITEM_MAP.find(const_cast<IHasInventory*>(container)) != _CONTAINER_TO_ITEM_MAP.end();
}
IInventory::ContainerMap::ContainerMap() {
}
IInventory::ContainerMap::~ContainerMap() {
	clear();
}
string IInventory::ContainerMap::type_name() const {
	return "IInventory::ContainerMap";
}
void IInventory::ContainerMap::register_container(IHasInventory* container) {
	//cout << &(container->inventory()) << endl;
	_CONTAINER_TO_ITEM_MAP[container] = vector<Item*>();
}
void IInventory::ContainerMap::update(Item* item,IHasInventory* container) {
	if (contains_item(item)) {
		bool found = false;
		for (map<IHasInventory*,vector<Item*>>::iterator i = _CONTAINER_TO_ITEM_MAP.begin(); !found && i != _CONTAINER_TO_ITEM_MAP.end(); ++i) {
			vector<Item*>& v = i->second;
			for (vector<Item*>::iterator j = v.begin(); j != v.end(); ++j) {
				if (*j == item) {
					v.erase(j);
					found = true;
					break;
				}
			}
		}
	}
	_ITEM_TO_CONTAINER_MAP[item] = container;
	if (!contains_container(container)) {
		register_container(container);
	}
	_CONTAINER_TO_ITEM_MAP[container].push_back(item);
}
vector<Item*> IInventory::ContainerMap::query(string name, IInventory* container) {
	vector<Item*> res;
	vector<Item*>* possibilities = (*this)[container];
	if (possibilities != NULL) {
		Item* ptr;
		for (vector<Item*>::iterator i = possibilities->begin(); i != possibilities->end(); ++i) {
			ptr = *i;
			if (ptr->name() == name) {
				res.push_back(ptr);
			}
		}
	}
	return res;
}
void IInventory::ContainerMap::clear() {
	_CONTAINER_TO_ITEM_MAP.clear();
	_ITEM_TO_CONTAINER_MAP.clear();
}
const IHasInventory* IInventory::ContainerMap::operator [](const Item* item) const {
	return contains_item(item) ? _ITEM_TO_CONTAINER_MAP.at(const_cast<Item*>(item)) : NULL;
}
const vector<Item*>* IInventory::ContainerMap::operator [](const IInventory* container) const {
	for (map<IHasInventory*,vector<Item*>>::const_iterator i = _CONTAINER_TO_ITEM_MAP.cbegin(); i != _CONTAINER_TO_ITEM_MAP.cend(); ++i) {
		if (&(i->first->inventory()) == container) {
			return &(i->second);
		}
	}
	return NULL;
}
IHasInventory* IInventory::ContainerMap::operator [](Item* item) {
	return contains_item(item) ? _ITEM_TO_CONTAINER_MAP.at(item) : NULL;
}
vector<Item*>* IInventory::ContainerMap::operator [](IInventory* container) {
	for (map<IHasInventory*,vector<Item*>>::iterator i = _CONTAINER_TO_ITEM_MAP.begin(); i != _CONTAINER_TO_ITEM_MAP.end(); ++i) {
		//cout << "stored = " << &(i->first->inventory()) << ", input = " << container << endl;
		if (&(i->first->inventory()) == container) {
			return &(i->second);
		}
	}
	return NULL;
}

IInventory::~IInventory() {
}
void IInventory::clear_references() {
	_CONTAINER_MAP.clear();
}

