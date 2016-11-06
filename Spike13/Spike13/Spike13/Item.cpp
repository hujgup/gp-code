#include "Inventory.h"
#include <stdexcept>

using namespace std;

map<unsigned long,shared_ptr<Item>> Item::_REFERENCES;

Item::Item(unsigned long id,string name,string desc,IHasInventory& container) : _id(id),_name(name),_desc(desc) {
	add(new ItemComponent());
	IInventory::_CONTAINER_MAP.update(this, &container);
}
Item::Item() {
	add(new ItemComponent());
}
Item::~Item() {
}
void Item::clear_references() {
	_REFERENCES.clear();
}
bool Item::exists(unsigned long id) {
	return _REFERENCES.find(id) != _REFERENCES.end();
}
Item& Item::create(unsigned long id,string name,string desc,IHasInventory& container) {
	if (exists(id)) {
		throw runtime_error("An item with id " + std::to_string(id) + " already exists.");
	} else {
		_REFERENCES.insert(make_pair(id,shared_ptr<Item>(new Item(id,name,desc,container))));
		return get(id);
	}
}
Item& Item::get(unsigned long id,const IHasInventory& container) {
	Item& res = get(id);
	if (res.container() != container) {
		throw runtime_error("Item with id " + std::to_string(id) + " does not occur in the specified room.");
	}
	return res;
}
Item& Item::get(unsigned long id) {
	if (exists(id)) {
		return *_REFERENCES[id];
	} else {
		throw runtime_error("Cannot get an item with id " + std::to_string(id) + " because no item with that id exists.");
	}
}
unsigned long Item::get_id_by_name(string name) {
	for (std::map<unsigned long,shared_ptr<Item>>::const_iterator i = _REFERENCES.cbegin(); i != _REFERENCES.cend(); ++i) {
		if (i->second->name() == name) {
			return i->first;
		}
	}
	throw range_error("No item with name '" + name + "' exists.");
}
vector<Item> Item::all_items() {
	vector<Item> res;
	for (std::map<unsigned long,shared_ptr<Item>>::const_iterator i = _REFERENCES.cbegin(); i != _REFERENCES.cend(); ++i) {
		res.push_back(*(i->second));
	}
	return res;
}
string Item::type_name() const {
	return "Item";
}
IInventory& Item::inventory() {
	return _inv;
}
unsigned char Item::type_id() const {
	return 1;
}
unsigned long Item::id() const {
	return _id;
}
string Item::name() const {
	return _name;
}
string Item::desc() const {
	return _desc;
}
bool Item::has_container() const {
	return IInventory::_CONTAINER_MAP.contains_item(this);
}
IHasInventory& Item::container() {
	if (has_container()) {
		return *(IInventory::_CONTAINER_MAP[this]);
	} else {
		throw runtime_error("Cannot get this item's container because it does not have a container.");
	}
}
void Item::container(const IHasInventory& newContainer) {
	IInventory::_CONTAINER_MAP.update(this, const_cast<IHasInventory*>(&newContainer));
}
bool Item::operator ==(const Item& other) const {
	return _id == other._id;
}
bool Item::operator !=(const Item& other) const {
	return !(*this == other);
}


