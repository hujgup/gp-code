#include "Object.h"

using namespace std;

Object::~Object() {
}
string Object::to_string() const {
	return "<" + type_name() + ">";
}
string Object::to_string(int value) const {
	return std::to_string(value);
}
string Object::to_string(unsigned int value) const {
	return std::to_string(value);
}
string Object::to_string(long value) const {
	return std::to_string(value);
}
string Object::to_string(unsigned long value) const {
	return std::to_string(value);
}
string Object::to_string(long long value) const {
	return std::to_string(value);
}
string Object::to_string(unsigned long long value) const {
	return std::to_string(value);
}
string Object::to_string(float value) const {
	return std::to_string(value);
}
string Object::to_string(double value) const {
	return std::to_string(value);
}
string Object::to_string(long double value) const {
	return std::to_string(value);
}