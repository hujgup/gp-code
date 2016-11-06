#include <iostream>
#include "Spike1Loop.h"
#include "Spike1State.h"
#include "MovementCommand.h"

using namespace std;

// Controls reactions to player input
bool loop_output(ostream& output,GameState& inState) {
	Spike1State& state = (Spike1State&)inState;
	bool hasObjective = state.location_has_objective();
	bool res = hasObjective || state.location_has_death();
	if (res) {
		if (hasObjective) {
			output << "You found the gold!" << endl;
		} else {
			output << "You walked straight into a bottomless pit. You will have much time to contemplate your inattentiveness during the infinitely long drop." << endl;
		}
	} else {
		Grid& playspace = state.playspace();
		GridIterator iEnd = playspace.end();
		for (GridIterator i = playspace.begin(); i != iEnd; ++i) {
			Cell& cell = *i;
			if (cell.x() == 0 && cell.y() != 0) {
				output << endl;
			}
			if (cell == state.player_location()) {
				output << "P";
			} else if (cell.has_occupier()) { //  && cell.occupier().is_impassable()
				CellOccupier occupier = cell.occupier();
				if (occupier.is_impassable()) {
					output << "#";
				} else if (occupier == state.death()) {
					output << "D";
				} else if (occupier == state.objective()) {
					output << "G";
				} else {
					output << "?";
				}
			} else {
				output << " ";
			}
		}
		output << endl << "Q to quit." << endl;
	}
	return res;
}
// Causes the game to terminate
bool cmd_quit(ostream& output,GameState& state) {
	return true;
}

int main(int argc,char* argv) {
	/*
	Game map:

	# = Wall
	G = Objective
	D = Death
	P = Player start location

	Dimensions = 8x8

	########
	#G D#D #
	#   #  #
	### # D#
	#   #  #
	# #### #
	#      #
	##P#####
	*/

	Spike1Loop coreLoop(&loop_output, 8, 8);
	coreLoop.create_game_state(2, 7);
	coreLoop.add_command("q", &cmd_quit);

	MovementCommand north(0, -1);
	MovementCommand south(0, 1);
	MovementCommand west(-1, 0);
	MovementCommand east(1, 0);
	coreLoop.add_command("n", north);
	coreLoop.add_command("s", south);
	coreLoop.add_command("w", west);
	coreLoop.add_command("e", east);

	Spike1State& state = (Spike1State&)coreLoop.state();

	state.cell_give_wall(0, 0);
	state.cell_give_wall(1, 0);
	state.cell_give_wall(2, 0);
	state.cell_give_wall(3, 0);
	state.cell_give_wall(4, 0);
	state.cell_give_wall(5, 0);
	state.cell_give_wall(6, 0);
	state.cell_give_wall(7, 0);
	state.cell_give_wall(0, 1);
	state.cell_give_wall(4, 1);
	state.cell_give_wall(7, 1);
	state.cell_give_wall(0, 2);
	state.cell_give_wall(4, 2);
	state.cell_give_wall(7, 2);
	state.cell_give_wall(0, 3);
	state.cell_give_wall(1, 3);
	state.cell_give_wall(2, 3);
	state.cell_give_wall(4, 3);
	state.cell_give_wall(7, 3);
	state.cell_give_wall(0, 4);
	state.cell_give_wall(4, 4);
	state.cell_give_wall(7, 4);
	state.cell_give_wall(0, 5);
	state.cell_give_wall(2, 5);
	state.cell_give_wall(3, 5);
	state.cell_give_wall(4, 5);
	state.cell_give_wall(5, 5);
	state.cell_give_wall(7, 5);
	state.cell_give_wall(0, 6);
	state.cell_give_wall(7, 6);
	state.cell_give_wall(0, 7);
	state.cell_give_wall(1, 7);
	state.cell_give_wall(3, 7);
	state.cell_give_wall(4, 7);
	state.cell_give_wall(5, 7);
	state.cell_give_wall(6, 7);
	state.cell_give_wall(7, 7);

	state.cell_give_objective(1, 1);

	state.cell_give_death(3, 1);
	state.cell_give_death(5, 1);
	state.cell_give_death(6, 3);

	coreLoop(cout, cin);

	cout << endl << "Thanks for playing!" << endl;
	cin.ignore();
	cin.ignore();
	terminate(); // Stops an access violation exception

	return 0;
}