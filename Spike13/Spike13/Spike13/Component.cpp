#include "Component.h"

using namespace std;

unsigned long Component::_next = 0;

unsigned long Component::acquire_id() {
	return _next++;
}
Component::~Component() {
}
void Component::exec(BinaryWriter& output,map<unsigned long,void*> input) {
	output << cmp_id();
	do_this(output,input);
}
void Component::exec(BinaryWriter& output) {
	exec(output,map<unsigned long,void*>());
}
bool Component::operator ==(const Component& other) const {
	return cmp_id() == other.cmp_id();
}
bool Component::operator !=(const Component& other) const {
	return !(*this == other);
}

const unsigned long HealthComponent::id = Component::acquire_id();

HealthComponent::HealthComponent(unsigned long init) : _hp(init) {
}
unsigned long HealthComponent::cmp_id() const {
	return id;
}
void HealthComponent::do_this(BinaryWriter& output,map<unsigned long,void*> input) {
	if (input.find(cmp_id()) != input.end()) {
		_hp = *(unsigned long*)input.at(cmp_id());
	}
	output << _hp;
}
unsigned long HealthComponent::hp() const {
	return _hp;
}
void HealthComponent::hp(unsigned long value) {
	_hp = value;
}

const unsigned long DamageComponent::id = acquire_id();

void DamageComponent::do_this(BinaryWriter& output,map<unsigned long,void*> input) {
	if (input.find(cmp_id()) != input.end()) {
		_dmg = *(unsigned long*)input.at(cmp_id());
	}
	output << _dmg;
}
DamageComponent::DamageComponent(unsigned long init) : _dmg(init) {
}
unsigned long DamageComponent::cmp_id() const {
	return id;
}
unsigned long DamageComponent::dmg() const {
	return _dmg;
}
void DamageComponent::dmg(unsigned long value) {
	_dmg = value;
}


const unsigned long ItemComponent::id = acquire_id();

unsigned long ItemComponent::cmp_id() const {
	return id;
}
void ItemComponent::do_this(BinaryWriter& output,map<unsigned long,void*> input) {
}
