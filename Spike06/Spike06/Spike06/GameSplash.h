#pragma once

#include "GameState.h"

// Represents a splash screen
class GameSplash : public GameState {
protected:
	// Outputs the contents of the splash screen
	virtual void output_content() const = 0;
	// Returns the GameState that should be progressed to once the user is finished looking at this splash screen
	virtual GameState* next_state() const = 0;
public:
	// Creates a new GameSplash
	// output = The output stream to write to
	// input = The input stream to read from
	// storage = The StateStorage this instance belongs to
	GameSplash(std::ostream& output,std::istream& input,StateStorage* storage);
	// Creates a new GameSplash
	// storage = The StateStorage this instance belongs to
	GameSplash(StateStorage* storage);
	// Required for inheritance, does nothing in this class
	virtual ~GameSplash();
	// Calls output_content and informs the user about how to continue once they are finished
	virtual void on_enter() override final;
	// Causes progression to the next state regardless of what the use inputs
	virtual GameState* parse_command(std::string command) override final;
	// Returns an empty string, as there are no valid commands on a splash screen
	virtual std::string input_indicator() const override final;
};