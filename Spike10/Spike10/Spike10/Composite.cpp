#include "Composite.h"
#include <algorithm>

using namespace std;

const unsigned long Composite::id = Composite::acquire_id();

bool by_ids(Component* a,Component* b) {
	return a->cmp_id() < b->cmp_id();
}

unsigned long Composite::cmp_id() const {
	return id;
}
Composite::~Composite() {
	for (vector<Component*>::iterator i = _components.begin(); i != _components.end(); ++i) {
		delete *i;
	}
}
void Composite::do_this(BinaryWriter& output,map<unsigned long,void*> input) {
	for (vector<Component*>::iterator i = _components.begin(); i != _components.end(); ++i) {
		(*i)->exec(output,input);
	}
}
void Composite::add(Component* c) {
	if (!contains(c)) {
		_components.push_back(c);
		sort(_components.begin(),_components.end(),&by_ids);
	}
}
bool Composite::contains(Component* c) {
	return get(c) != NULL;
}
Component* Composite::get(Component* c) {
	Component* res = NULL;
	for (vector<Component*>::iterator i = _components.begin(); res == NULL && i != _components.end(); ++i) {
		if (**i == *c) {
			res = *i;
		}
	}
	return res;
}
bool Composite::remove(Component* c) {
	bool res = false;
	for (vector<Component*>::iterator i = _components.begin(); i != _components.end(); ++i) {
		if (**i == *c) {
			Component* c = *i;
			_components.erase(i);
			delete c;
			res = true;
			break;
		}
	}
	return res;
}

