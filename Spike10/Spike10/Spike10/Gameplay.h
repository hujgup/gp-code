#pragma once

#include "GameEnvironment.h"
#include "Player.h"
#include "BasicCommand.h"
#include "World.h"

// Represents the gameplay segment
class Gameplay : public GameEnvironment {
private:
	std::string _worldName; // The name of the world the player is in
	bool _firstEnter;
	Player _player; // The player
	World* _world;
	BasicCommand _exit;
	BasicCommand _scores;
	BasicCommand _inventory;
	BasicCommand _examine;
	Command _go;
	GameState* cmd_exit();
	GameState* cmd_scores();
	GameState* cmd_view_inventory();
	GameState* cmd_examine();
	GameState* cmd_go(const std::vector<std::string>& args);
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
	virtual std::string type_name() const override;
	// Prints the world the player is in and clears the player's inventory
	virtual void on_enter() override;
	const World& world() const;
	Player& player();
};