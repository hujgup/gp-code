#include "Player.h"
#include "BasicInventory.h"

Player::Player() : _inv(new BasicInventory()), _locationId(0) {
}
Player::~Player() {
	delete _inv;
}
IInventory& Player::inventory() {
	return *_inv;
}
unsigned long Player::location_id() const {
	return _locationId;
}
void Player::location_id(unsigned long value) {
	_locationId = value;
}