#pragma once

#include <vector>
#include <unordered_map>
#include "Command.h"

// Represents a state where complex commands are possible
class GameEnvironment : public GameState {
private:
	std::unordered_map<std::string,Command> _commands;
	std::vector<std::string> _args;
	bool contains(const std::string& id) const;
	std::string split(const std::string& command);
protected:
	// Adds a command to the _commands map
	// id = The command key to add
	// cmd = The command executable to add
	bool add_command(std::string id,Command cmd);
public:
	// Creates a new GameEnvironment
	// output = The output stream to write to
	// input = The input stream to read from
	// storage = The StateStorage this instance belongs to
	GameEnvironment(std::ostream& output, std::istream& input,StateStorage* storage);
	// Creates a new GameEnvironment
	// storage = The StateStorage this instance belongs to
	GameEnvironment(StateStorage* storage);
	// Required for inheritance, does nothing in this class
	virtual ~GameEnvironment();
	// When the user inputs a command, checks if the _commands map contains said command and executes it if it does
	// command = The command key to attempt to execute
	virtual GameState* parse_command(std::string command) override final;
};