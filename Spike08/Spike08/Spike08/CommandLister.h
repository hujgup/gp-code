#pragma once

#include "GameSplash.h"

// Lists all the commands available during gameplay
class CommandLister : public GameSplash {
protected:
	// Lists all the commands available during gameplay
	virtual void output_content() const override;
	// Progresses to the main menu
	virtual GameState* next_state() const override;
public:
	// Creates a new CommandLister
	// output = The output stream to write to
	// input = The input stream to read from
	// storage = The StateStorage this instance belongs to
	CommandLister(std::ostream& output,std::istream& input,StateStorage* storage);
	// Creates a new CommandLister
	// storage = The StateStorage this instance belongs to
	CommandLister(StateStorage* storage);
	// Required for inheritance, does nothing in this class
	virtual ~CommandLister();
	virtual std::string type_name() const override;
};