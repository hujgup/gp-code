#include "Player.h"
#include "BasicInventory.h"

Player::Player() {
	_inv = new BasicInventory();
}
Player::~Player() {
	delete _inv;
}
IInventory& Player::inventory() {
	return *_inv;
}