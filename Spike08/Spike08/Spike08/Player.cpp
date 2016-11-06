#include "Player.h"
#include "BasicInventory.h"

using namespace std;

Player::Player() : _inv(new BasicInventory()), _locationId(0) {
}
Player::~Player() {
	delete _inv;
}
string Player::type_name() const {
	return "Player";
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