#pragma once

#include "GameEnvironment.h"

// Represents the gameplay segment
class Gameplay : public GameEnvironment {
private:
	std::string _worldName; // The name of the world the player is in
	// The executable command that quits gameplay
	GameState* cmd_exit();
	// The executable command that displays the hall of fame
	GameState* cmd_scores();
	// Construction helper method: Adds all the commands to the GameEnvironment
	void add_commands();
public:
	// Creates a new Gameplay
	// output = The output stream to write to
	// input = The input stream to read from
	// storage = The StateStorage this instance belongs to
	Gameplay(std::ostream& output,std::istream& input,StateStorage* storage);
	// Creates a new Gameplay
	// storage = The StateStorage this instance belongs to
	Gameplay(StateStorage* storage);
	// Required for inheritance, does nothing in this class
	virtual ~Gameplay();
	// Prints the world the player is in
	virtual void on_enter() override;
	std::string world_name() const;
	void world_name(std::string value);
};