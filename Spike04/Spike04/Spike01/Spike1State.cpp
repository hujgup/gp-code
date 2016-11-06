#include "Spike1State.h"

// Creates a new Spike1State
// playspace = The grid that defines the game's playspace
// startX = The player's initial x position
// startY = The player's initial y position
// allowMultipleObjectives = Controls whether a game may have more than 1 objective cell
Spike1State::Spike1State(Grid* playspace,unsigned int startX,unsigned int startY,bool allowMultipleObjectives) : GameState(playspace,startX,startY) {
	_wall = new CellOccupier("Wall","You cannot climb it.",true);
	_objective = new CellOccupier("Chest of Gold","Too heavy to carry.");
	_death = new CellOccupier("Bottomless Pit","It does not end.");
	_allowMultipleObjectives = allowMultipleObjectives;
	_objectivesPresent = 0;
}
// Creates a new Spike1State with a unique objective
// playspace = The grid that defines the game's playspace
// startX = The player's initial x position
// startY = The player's initial y position
Spike1State::Spike1State(Grid* playspace,unsigned int startX,unsigned int startY) : Spike1State(playspace,startX,startY,false) {
}
// Destroys this Spike1State
Spike1State::~Spike1State() {
	delete _wall;
	delete _objective;
	delete _death;
}
// Gets the Wall cell occupier
CellOccupier& Spike1State::wall() const {
	return *_wall;
}
// Gets the Objective cell occupier
CellOccupier& Spike1State::objective() const {
	return *_objective;
}
// Gets the Death cell occupier
CellOccupier& Spike1State::death() const {
	return *_death;
}
// Gets the number of objectives in the playspace
unsigned int Spike1State::objectives_present() const {
	return _objectivesPresent;
}
// Returns true if at least 1 objective exists
bool Spike1State::has_objective() const {
	return _objectivesPresent > 0;
}
// Returns true if the player's location contains an objective
bool Spike1State::location_has_objective() const {
	return player_location().occupier() == *_objective;
}
// Returns true if the player's location contains death
bool Spike1State::location_has_death() const {
	return player_location().occupier() == *_death;
}
// Sets the occupier of the cell at the specified position to be Wall
void Spike1State::cell_give_wall(unsigned int x,unsigned int y) {
	Cell& cell = playspace().cell_at(x,y);
	if (cell.occupier() == *_objective) {
		--_objectivesPresent;
	}
	playspace().cell_at(x,y).set_occupier(*_wall);
}
// Sets the occupier of the cell at the specified position to be Objective
bool Spike1State::cell_give_objective(unsigned int x,unsigned int y) {
	bool res = _allowMultipleObjectives || _objectivesPresent == 0;
	if (res) {
		Cell& cell = playspace().cell_at(x,y);
		if (cell.occupier() != *_objective) {
			playspace().cell_at(x,y).set_occupier(*_objective);
			++_objectivesPresent;
		}
	}
	return res;
}
// Sets the occupier of the cell at the specified position to be Death
void Spike1State::cell_give_death(unsigned int x,unsigned int y) {
	Cell& cell = playspace().cell_at(x,y);
	cell.set_occupier(*_death);
}
