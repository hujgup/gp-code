#include "MovementCommand.h"

using namespace std;

// Creates a new MovementCommand
// xMotion = The amount of x movement that should occur when this command is invoked
// yMotion = The amount of y movement that should occur when this command is invoked
MovementCommand::MovementCommand(int xMotion,int yMotion) {
	_xMotion = xMotion;
	_yMotion = yMotion;
}
// Executes this command
// output = The output stream to write messages to
// state = The current game state
bool MovementCommand::operator ()(ostream& output,GameState& state) {
	try {
		Cell& location = state.player_location();
		Cell& newLocation = state.playspace().cell_at(location.x() + _xMotion,location.y() + _yMotion);
		if (newLocation.has_occupier()) {
			CellOccupier& occupier = newLocation.occupier();
			if (occupier.is_impassable()) {
				output << "An obstacle blocks the way!" << endl << occupier << endl;
			} else {
				state.set_player_location(newLocation);
			}
		} else {
			state.set_player_location(newLocation);
		}
	} catch (logic_error) {
		output << "Cannot move out of bounds." << endl;
	}
	return false;
}

