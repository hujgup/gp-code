#pragma once

#include "GameState.h"

// Controls the swapping of game states and what happens when states swap
class StateController : public Object {
private:
	StateStorage _storage; // Stores and manages all the GameState pointers
	std::ostream& _output; // The output stream to write to
	std::istream& _input; // The inout stream to read from
	GameState* _currentState; // The current game state
public:
	// Creates a new StateController
	// output = The output stream to write to
	// input = The input stream to write to
	StateController(std::ostream& output, std::istream& input);
	// Creates a new StateController
	// Overload of the previous constructor, passing in std::cout and std::cin as arguments
	StateController();
	virtual ~StateController();
	virtual std::string type_name() const override;
	// Runs the state controller
	void operator ()();
};