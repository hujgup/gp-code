#include "Player.h"
#include "BasicInventory.h"

using namespace std;

Player::Player() : _locationId(0) {
}
Player::~Player() {
}
string Player::type_name() const {
	return "Player";
}
unsigned char Player::type_id() const {
	return 2;
}
unsigned long Player::id() const {
	return 0;
}
IInventory& Player::inventory() {
	return _inv;
}
unsigned long Player::location_id() const {
	return _locationId;
}
void Player::location_id(unsigned long value) {
	_locationId = value;
}