#pragma once

#include "GameSplash.h"

// Represents the credits screen
class Credits : public GameSplash {
protected:
	// Outputs the creator of the game
	virtual void output_content() const override;
	// Progresses to the main menu
	virtual GameState* next_state() const override;
public:
	// Creates a new Credits
	// output = The output stream to write to
	// input = The input stream to read from
	// storage = The StateStorage this instance belongs to
	Credits(std::ostream& output,std::istream& input,StateStorage* storage);
	// Creates a new Credits
	// storage = The StateStorage this instance belongs to
	Credits(StateStorage* storage);
	// Required for inheritance, does nothing in this class
	virtual ~Credits();
	virtual std::string type_name() const override;
};