#include "GameState.h"
#include <stdexcept>

using namespace std;

// Creates a new GameState
// playspace = The grid that defines the game's playspace
// startX = The player's initial x position
// startY = The player's initial y position
GameState::GameState(Grid* playspace,unsigned int startX,unsigned int startY) : _playspace(playspace) {
	if (playspace->cell_at(startX,startY).has_occupier()) {
		throw logic_error("Player cannot start on a cell that has a blocker.");
	}
	_playspace = playspace;
	_locationX = startX;
	_locationY = startY;
}
// Destroys this GameState
GameState::~GameState() {
	delete _playspace;
}
// Gets the current playspace
Grid& GameState::playspace() const {
	return *_playspace;
}
// Gets the player's current location
Cell& GameState::player_location() const {
	return _playspace->cell_at(_locationX,_locationY);
}
// Updates the player's current location
// x = The x position to change to
// y = The y position to change to
void GameState::set_player_location(unsigned int x,unsigned int y) {
	_locationX = x;
	_locationY = y;
}
// Updates the player's current location
// location = The cell to change to
void GameState::set_player_location(const Cell& location) {
	set_player_location(location.x(),location.y());
}