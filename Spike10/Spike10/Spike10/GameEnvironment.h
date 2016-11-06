#pragma once

#include <unordered_map>
#include "Command.h"
#include "InsertionOrderedMap.h"

// Represents a state where complex commands are possible
class GameEnvironment : public GameState {
private:
	InsertionOrderedMap<std::string,Command> _commands;
	std::unordered_map<std::string,std::string> _aliases;
	bool contains(const std::string& id) const;
	bool contains_alias(const std::string& alias) const;
	//void split(const std::string& command);
	// Adds a command alias
	bool add_alias(std::string id,std::string regex);
	std::vector<std::string> create_args(std::string command,const std::string& aRegex);
protected:
	// Adds a command to the _commands map
	// id = The command key to add
	// cmd = The command executable to add
	bool add_command(std::string id,Command cmd);
	// Loads command aliases from a file
	void load_aliases(std::string file);
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
	virtual std::string type_name() const override;
	// When the user inputs a command, checks if the _commands map contains said command and executes it if it does
	// command = The command key to attempt to execute
	virtual GameState* parse_command(std::string command) override final;
};